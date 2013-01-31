/*
Assignment 3 
Team Member 1 : Sverre Kvamme
Team Member 2 :	Simen Andresen
*/

#include "nBody.h"
#define OUT_VARS (all[i*size*7+j], all[i*size*7+j+size], all[i*size*7+j+2*size],all[i*size+j+3*size],all[i*size+j+4*size],all[i*size+j+5*size],all[i*size+j+6*size])


void readnbody(double** s, double** v, double* m, int n) {
	int myrank;
	int nprocs;
	int i;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	
	// This is an example of reading the body parameters from the input file. 
	if (myrank == 0) {
		for (i = 0; i < n; i++) {
			double x, y, z, vx, vy, vz, m;

			int result = scanf(INPUT_BODY, &x, &y, &z, &vx, &vy, &vz, &m);
			if (result != 7) {
				fprintf(stderr, "error reading body %d. Check if the number of bodies is correct.\n", i);
				exit(0);
			}
		}
	}
}

void gennbody(double** s, double** v, double* m, int n) {
	int myrank;
	int nprocs;
	int i, j;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	// generating pseudo random positions and masses.
	// their values are deterministic for ease debugging
	for(i=0; i<n/nprocs; i++){
		m[i] = 1e30+1e20*myrank*pow(-1,j);
		for(j=0; j<3; j++){
			s[i][j]= (myrank*1000 + i*j  + 10*j*j + 10*i)*10e10;
			v[i][j]= 0;
		}
		// DEBUG
		if(myrank==0){
			fprintf(stderr, OUTPUT_BODY, s[i][0], s[i][1], s[i][2], v[i][0], v[i][1], v[i][2], m[i]);
		}
	}
}


/* Communication ----------------------------------
/ all processors with even rank have two buffers
/ one for receive and one for send. The even processors 
/ also switches which of the buffers to send and receive to 
/ avoid having to copy the buffers						     */	
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

// computes the acceleration vector excerted on planets with  s distance  and mass m due to gravity from s_bf and m_bf
void compute_acceleration(double ** a_v, double ** s, double* m, double *bf, int n, int nMrg) {
	double f_v[3];
	double G = 6.674e-11;
	double r;
	double r_v[3];
	double f;
	int myrank;
	int nprocs;
	int j;
	int k;
	int l;
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
			    f=G*m[j]*bf[3*size+k]/pow(r,2);							// get the total scalar force between two planets
				for(l=0;l<3;l++){
					f_v[l] = f*r_v[l]/r;								// get the force as a vector
					a_v[j][l] += - f_v[l]/m[j];							// get the acceleration due to force
				}
			}
		}
	}
}

// collect distance s and velocity v from all procs to proc 0
// and print to file final_states.txt
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
	// collect data
	MPI_Gather(sendarray,size*7,MPI_DOUBLE,all,size*7,MPI_DOUBLE, 0,MPI_COMM_WORLD);
	// write data to file
	if(myrank==0){
		FILE * out;
		char filename[]="final_states.txt";
		out=fopen(filename,"w");
		for(i=0;i<nprocs;i++){
			for(j=0;j<size;j++){
				fprintf(out,"Proc nr %d\n",i);
				fprintf(out,OUTPUT_BODY,
				all[i*size*7+j], all[i*size*7+j+size], all[i*size*7+j+2*size],all[i*size*7+j+3*size],all[i*size*7+j+4*size],all[i*size*7+j+5*size],all[i*size*7+j+6*size]);
			}
		}	
		fclose(out);	
	}
} 

void nbody(double** s, double** v, double* m, int n, int iter, int timestep) {
	int myrank;
	int nprocs;
	int i;
	int I;
	int nMrg;
	int j;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	double** a_v;
	int size=n/nprocs;
	
	// allocate space for a
	a_v = (double **)malloc(sizeof(double *) * size);
	for (i = 0; i < size; i++) {
		a_v[i] = (double*)malloc(sizeof(double) * 3);
		for(j = 0; j < 3; j++) {
			a_v[i][j] = 0;
		}
	}
	
	// BUFFERS to make it easier to send and revceive, each 
	// buffer is an 1 D array. 
	//  each buffers holds all three position components + mass.
	//  element 0 to size -1 is x position, size - 2*size-1 is y position,
	//  2*size - 3*size-1 is y position, 3*size - 4*size-1 is mass
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
			bf1[i*size+j] = s[i][j];
		}
	}

	// main loop
	for(I=0; I<iter ; I++){
		for(i=0;i<size;i++){
			for(j=0;j<size;j++){
				a_v[i][j]=0;
			}
		}
		for(nMrg=0; nMrg<nprocs; nMrg++){
			if(nMrg % 2==0 || myrank % 2!=0 ){
				compute_acceleration(a_v,s,m,bf1, n,nMrg);
			}else{
				compute_acceleration(a_v,s,m,bf2, n,nMrg);
			}
			mary_go_round(myrank, bf1, bf2, size,nprocs,nMrg);
		}
		update_states(a_v,s,v,size,timestep);
		if(myrank==0){
			fprintf(stderr, OUTPUT_BODY, s[0][0], s[0][1], s[0][2], v[0][0], v[0][1], v[0][2], m[0]);
		}
	}
	// end main loop

	collect_data_from_all(s, v,m, size, myrank, nprocs);
	free(bf1);
	for(i=0;i<size;i++){
		free(a_v[i]);
	}
	if(myrank %2==0){
		free(bf2);
	}

}




