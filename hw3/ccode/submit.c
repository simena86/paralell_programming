/*
Assignment 3 
Team Member 1 : Sverre Kvamme
Team Member 2 :	Simen Andresen
*/
#include <stdlib.h>
#include <time.h>
#include "nBody.h"
#include <math.h>
#ifndef PI
	#define PI 3.14
#endif

/* Read data from stdin using < input.txt. All data are saved in a buffer 
 * on processor 0 and distributed to all other processors, if any */
void readnbody(double** s, double** v, double* m, int n) {
	int myrank, nprocs;
	int i,j;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	int size=n/nprocs;
	double ** recv_bfr;
	double * recv_bfr2;
	// read data from input.txt to processor 0 
	if (myrank == 0) {
		recv_bfr= (double **)malloc(sizeof(double) * nprocs);
		for(i=0;i<nprocs;i++){
			recv_bfr[i]=(double *)malloc(sizeof(double) * size*7 );
			for(j=0;j<size*7;j++){
				recv_bfr[i][j]=0;
			}
		}
		for (i = 0; i < nprocs; i++) {
			for(j=0;j<size;j++){
			int result =scanf(INPUT_BODY, 
					&recv_bfr[i][j*7],&recv_bfr[i][j*7+1],&recv_bfr[i][j*7+2], 		// position
					&recv_bfr[i][j*7+3],&recv_bfr[i][j*7+4],&recv_bfr[i][j*7+5],	// velocity
					&recv_bfr[i][j*7+6]);											// mass
				if (result != 7) {
					fprintf(stderr, "error reading body %d. Check if the number of bodies is correct.\n", i);
					exit(0);
				}
			}
		}
		// copy data to processor 0's local buffer
		for(i=0;i<size;i++){
			m[i]=recv_bfr[0][i*7+6];
			for(j=0;j<3;j++){
				s[i][j]=recv_bfr[0][i*7+j];
				v[i][j]=recv_bfr[0][i*7+j+3];
			}
		}
		// send rest of data to other processors
		for(i=1;i<nprocs;i++){
			MPI_Send(recv_bfr[i],size*7,MPI_DOUBLE,i,i,MPI_COMM_WORLD);
		}
		for(i=0;i<nprocs;i++){
			free(recv_bfr[i]);
		}	
		free(recv_bfr);
	}else{ // myrank!=0 
		recv_bfr2=(double *)malloc(sizeof(double) * size*7 );
		for(i=0;i<size*7;i++){
			recv_bfr2[i]=0;
		}
		MPI_Recv(recv_bfr2,size*7,MPI_DOUBLE,0,myrank,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		for(i=0;i<size;i++){
			m[i]=recv_bfr2[i*7+6];
			for(j=0;j<3;j++){
				s[i][j]=recv_bfr2[i*7+j];
				v[i][j]=recv_bfr2[i*7+j+3];
			}
		}
		free(recv_bfr2);	
	}
}

double rand1(){
	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	double ran = (double)(rand())/(double)(RAND_MAX); 
	return ran;
}

void gennbody(double** s, double** v, double* m, int n) {
	int myrank;
	int nprocs;
	int i, j;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	// generate random values for each planet
	for(i=0; i<n/nprocs; i++){
		srand ( time(NULL)+myrank+i);
		m[i] =1e30*rand1()*0.00001;
		s[i][0]=0.5e13*rand1()*cos(2*PI*rand1())*0.000000001;
		s[i][1]=0.5e13*rand1()*sin(2*PI*rand1())*0.000000001;;
		s[i][2]=1e11*rand1()-0.5*0.0000001;
		for(j=0; j<3; j++){
			v[i][j]= 0;
		}
	}
}

/* Communication ----------------------------------
* all processors with even rank have two buffers
* one for receive and one for send. The even processors 
* also switches which of the buffers to send and receive 
* to avoid having to copy the buffers						     */	
void mary_go_round(int myrank, double *bf1,double *bf2, int size, int nprocs, int nMrg ){
	int src, dest;	
	//  check if first or last processor
	if(myrank==0){
	   	src = nprocs-1;
		dest=myrank+1;
	}else if(myrank==nprocs-1){ 
		dest = 0;
		src=myrank-1;
	}else{
		dest=myrank+1;
		src=myrank-1;
	}
	// start communication
	if(myrank % 2 == 0){
		if(nMrg % 2==0){
			MPI_Recv(bf2,4*size , MPI_DOUBLE, src,nMrg, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
			MPI_Send(bf1, 4*size, MPI_DOUBLE,dest,nMrg,MPI_COMM_WORLD);
		}else{
			MPI_Recv(bf1,4*size, MPI_DOUBLE, src,nMrg, MPI_COMM_WORLD, MPI_STATUS_IGNORE  );
			MPI_Send(bf2,4*size, MPI_DOUBLE,dest,nMrg,MPI_COMM_WORLD);
		}
	}else{
		MPI_Send(bf1, 4*size, MPI_DOUBLE,dest,nMrg,MPI_COMM_WORLD);
		MPI_Recv(bf1, 4*size, MPI_DOUBLE, src,nMrg, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
	}
}

// update the velocities and positions of the planets
void update_states(double ** a_v, double ** s, double ** v, int size, double dt ){
	int i,j;
	for(i=0;i<size;i++){
		for(j=0; j<3;j++){
			v[i][j]+= dt*a_v[i][j];
			s[i][j]+= dt*v[i][j];	
		}	
	}
}

// computes the acceleration vector excerted on planets with s distance  and mass m due to gravity from s_bf and m_bf
void compute_acceleration(double ** a_v, double ** s, double* m, double *bf, int n, int nMrg) {
	double f_v[3];
    double r_v[3];
	double G = 6.674e-11;
	double f,r;
	int myrank, nprocs;
   	int	j,k,l;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	int size = n/nprocs;	
	for(j=0;j<size;j++){
		for (k=0;k<size;k++){
			if(j==k && nMrg==0){
				f_v[0]=0;	f_v[1]=0;	f_v[2]=0;		
			}else {
				for(l=0;l<3;l++){
					r_v[l]=s[j][l]-bf[k+l*size];  						// get the distance vector between planets
				}
				r=sqrt( pow(r_v[0],2) + pow(r_v[1],2)+ pow(r_v[2],2));  // get the length of the distance vector
			   	if(r==0){												// avoid divide by zero
					r=0.0001;
				}
			   	f=G*m[j]*bf[3*size+k]/pow(r,2);							// get the total scalar force between two planets
				for(l=0;l<3;l++){
					f_v[l] = f*r_v[l]/r;								// get the force as a vector
					a_v[j][l] += - f_v[l]/m[j];							// get the acceleration due to force
				}
			}
		}
	}
}

/* collect distance s and velocity v from all procs 
 * to proc 0 and print to file final_states.txt    */
void collect_data_from_all(double ** s, double** v, double * m, int size, int myrank, int nprocs){
	double * all;
	double * sendarray;
	int i,j,k;
	// organize s v m data into 1 D array
	sendarray = (double *)malloc(sizeof(double) * size*7);
	for(i=0;i<size;i++){
		sendarray[size*6+i]=m[i];
		for(j=0;j<3;j++){
			sendarray[i+j*size] = s[i][j];
			sendarray[3*size + i+j*size] = v[i][j];		
		}
	}
	// allocate space for all data in proc 0
	if(myrank==0){
		all = (double *)malloc(sizeof(double) * nprocs*size*7);
		for(i=0;i<nprocs*7*size;i++){
			all[i]=0;
		}
	}
	MPI_Gather(sendarray,size*7,MPI_DOUBLE,all,size*7,MPI_DOUBLE, 0,MPI_COMM_WORLD);
	if(myrank==0){  // write data to file
		FILE * out;
		char filename[]="final_states.txt";
		out=fopen(filename,"w");
		for(i=0;i<nprocs;i++){
			for(j=0;j<size;j++){
				fprintf(out,"Proc nr %d\n",i);
				fprintf(out,OUTPUT_BODY,
						all[i*size*7+j], all[i*size*7+j+size], all[i*size*7+j+2*size], 			// position
						all[i*size*7+j+3*size],all[i*size*7+j+4*size],all[i*size*7+j+5*size],	// velocity
						all[i*size*7+j+6*size]);												// mass
			}
		}	
		fclose(out);	
	}
} 

void nbody(double** s, double** v, double* m, int n, int iter, int timestep) {
	int myrank,nprocs;
	int i, I, nMrg, j;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	int size=n/nprocs;
	// allocate space for acceleration a_v
	double** a_v;
	a_v = (double **)malloc(sizeof(double *) * size);
	for (i = 0; i < size; i++) {
		a_v[i] = (double*)malloc(sizeof(double) * 3);
		for(j = 0; j < 3; j++) {
			a_v[i][j] = 0;
		}
	}

	/* BUFFERS to make it easier to send and revceive, each  buffer is an 1 D array.  each buffers holds
	*  all three position components + mass.  element 0 to size-1   is x position, size to 2*size-1
	*   is y position, 2*size to 3*size-1 is y position, 3*size to 4*size-1 is mass   */
	double* bf1;
	double* bf2;
	bf1 = (double *)malloc(sizeof(double) * size*4);
	for(i=0;i<4*size;i++){
		bf1[i]=0;
	}
	if(myrank % 2 ==0){
		bf2 = (double *)malloc(sizeof(double) * size*4);
		for(i = 0; i < 4*size; i++) {
			bf2[i] = 0;
		}
	} 
	// copy local data to buffers
	for(i=0;i<size;i++){
		bf1[size*3+i]=m[i];
		for(j=0;j<3;j++){
			bf1[i+size*j] = s[i][j];
		}
	}
	// main calculation loop
	for(I=0; I<iter ; I++){
		for(i=0;i<size;i++){		// reset acceleration to 0	
			for(j=0;j<3;j++){		
				a_v[i][j]=0;
			}
		}
		for(nMrg=0; nMrg<nprocs; nMrg++){ 		// compute new states 
			if(nMrg % 2==0 || myrank % 2!=0 ){
				compute_acceleration(a_v,s,m,bf1, n,nMrg);
			}else{
				compute_acceleration(a_v,s,m,bf2, n,nMrg);
			}
			if(nprocs!=1){
				mary_go_round(myrank, bf1, bf2, size,nprocs,nMrg);	// 1 round of mary go round communication
			}
		}
		update_states(a_v,s,v,size,timestep);					// update states
	}
	free(bf1);
	if(myrank % 2 ==0){
		free(bf2);
	}
    //collect_data_from_all(s,v,m, size, myrank, nprocs); / used only for debugging. prints the final xyz vxys and mass to file 
}




