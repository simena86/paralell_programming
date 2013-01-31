/*
Assignment 3 
Team Member 1 : Sverre Kvamme
Team Member 2 :	Simen Andresen
*/

#include "nBody.h"


// prototypes
void update_states(double ** a_v, double ** s, double ** v, int size, double dt );
void mary_go_round(int myrank, double *bf1,double *bf2, int size, int nprocs, int nMrg );
void compute_acceleration(double ** a_v, double ** s, double* m, double *bf, int n); 

void print_msg(char* s, int proc, int myrank){
	if(myrank==proc){
		fprintf(stderr,"%s \n",s);
	}
}

void print_msg_w_arg(char* s, int proc, int myrank, int arg){
	if(myrank==proc){
		fprintf(stderr,"%s , arg: %d\n",s,arg );
	}
}

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
	
	print_msg("Generating bodies\n",0,myrank);
	for(i=0; i<n/nprocs; i++){
		m[i] = 1000;
		for(j=0; j<3; j++){
			s[i][j]= myrank*1000 + i*j  + 10*j + 10*i;
			v[i][j]= 0;
		}
			// DEBUG
			if(myrank==0){
			fprintf(stderr, OUTPUT_BODY, s[i][0], s[i][1], s[i][2], v[i][0], v[i][1], v[i][2], m[i]);
			}
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

	// copy to buffers
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
				compute_acceleration(a_v,s,m,bf1, n);
			}else{
				compute_acceleration(a_v,s,m,bf2, n);
			}
			mary_go_round(myrank, bf1, bf2, size,nprocs,nMrg);
		}
		update_states(a_v,s,v,size,timestep);
	}
	
	free(bf1);
	free(a_v);
	if(myrank %2==0){
		free(bf2);
	}

}

/* Communication ----------------------------------
/ all processors with even rank have two buffers
/ one for receive and one for send. The even processors 
/ also switches which of the buffers to send and receive to 
/ avoid having to copy the buffers						     */	
void mary_go_round(int myrank, double *bf1,double *bf2, int size, int nprocs, int nMrg ){
	int i,j;
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

// computes the acceleration vector excerted on s an m due to gravity from s_bf and m_bf
void compute_acceleration(double ** a_v, double ** s, double* m, double *bf, int n) {
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
			if(j==k){
				f_v[0]=0;	f_v[1]=0;	f_v[2]=0;		
			}else {
				for(l=0;l<3;l++){
					r_v[l]=s[j][l]-bf[k+l*size];
				}
				r=sqrt( pow(r_v[0],2) + pow(r_v[1],2)+ pow(r_v[2],2));
			    f=G*m[j]*bf[3*size+k]/pow(r,2);
				for(l=0;l<3;l++){
					f_v[l] = f*r_v[l]/r;
					a_v[j][l] += - f_v[l]/m[j];
				}
			}
		}
	}
}

