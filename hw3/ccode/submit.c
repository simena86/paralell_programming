/*
Assignment 3 
Team Member 1 :
Team Member 2 :
*/

#include "nBody.h"

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
	if(myrank==0){
		printf("\nGenerating bodies\n");
	}
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
	int j;
	int src, dest;	
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	double** a_v;
	double size=n/nprocs;
	
	// allocate space for a
	a_v = (double **)malloc(sizeof(double *) * size);
	for (i = 0; i < size; i++) {
		a_v[i] = (double*)malloc(sizeof(double) * 3);
		for(j = 0; j < 3; j++) {
			a_v[i][j] = 0;
		}
	}
	
	// buffers
	double *m_bf1;
	double** s_bf1;
	m_bf1 = (double *)malloc(sizeof(double) * size);
	for(i = 0; i < size; i++) {
		m_bf1[i] = 0;
	}
	
	s_bf1 = (double **)malloc(sizeof(double *) * size);
	for (i = 0; i < size; i++) {
		s_bf1[i] = (double*)malloc(sizeof(double) * 3);
		for(j = 0; j < 3; j++) {
			s_bf1[i][j] = 0;
		}
	}

	double *m_bf2;
	double** s_bf2;
	// extra buffer for every second processor
	if(myrank % 2 ==0){
		m_bf2 = (double *)malloc(sizeof(double) * size);
		for(i = 0; i < size; i++) {
			m_bf2[i] = 0;
		}
	
		s_bf2 = (double **)malloc(sizeof(double *) * size);
		for (i = 0; i < size; i++) {
			s_bf2[i] = (double*)malloc(sizeof(double) * 3);
			for(j = 0; j < 3; j++) {
				s_bf2[i][j] = 0;
			}
		}
	}
	// copy to buffers
	for(i=0;i<size;i++){
		m_bf1[i]=m[i];
		s_bf1[i][0] = s[i][0];
		s_bf1[i][1] = s[i][1];
		s_bf1[i][2] = s[i][2];
	}
	
	double mrg[3]={myrank, myrank, myrank};
	double  mrg_bf1[3]={0};

	// main loop
	for(I=0; I<iter ; I++){
		// zero out acceleration after each step
		for(i=0; i<nprocs; i++){
			if(i % 2==0 || myrank % 2!=0 ){
				compute_acceleration(a_v,s,m,s_bf1,m_bf1, n);
			}else{
				compute_acceleration(a_v,s,m,s_bf2,m_bf2, n);
			}
			// MARY GO ROUND
			//  check for processor 0 or nrpoc
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
				if(i % 2==0){
					MPI_Recv(mrg_bf1, 3, MPI_DOUBLE, src,i, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
					MPI_Send(mrg, 3, MPI_DOUBLE,dest,i,MPI_COMM_WORLD);
				}else{
					MPI_Recv(mrg, 3, MPI_DOUBLE, src,i, MPI_COMM_WORLD, MPI_STATUS_IGNORE  );
					MPI_Send(mrg_bf1, 3, MPI_DOUBLE,dest,i,MPI_COMM_WORLD);
				}
			}else{
				MPI_Send(mrg, 3, MPI_DOUBLE,dest,i,MPI_COMM_WORLD);
				MPI_Recv(mrg, 3, MPI_DOUBLE, src,i, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
			}
			if(myrank == 1){
				printf("mrgs rank: %f, %f, %f\n", mrg[0], mrg[1], mrg[2]);
			}
		}
	}

	//DEBUG
	if (myrank == 0) {
		for (i = 0; i < n / nprocs; i++) {
			fprintf(stderr, OUTPUT_BODY, s[i][0], s[i][1], s[i][2], v[i][0], v[i][1], v[i][2], m[i]);
		}
	}
}


void compute_acceleration(double ** a_v, double ** s, double* m, double **s_bf, double* m_bf, int n) {
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
	
	for(j=0;j<n/nprocs;j++){
		for (k=0;k<n/nprocs;k++){
			if(j==k){
				f_v[0]=0;	f_v[1]=0;	f_v[2]=0;		
			}else {
				for(l=0;l<3;l++){
					r_v[l]=s[j][l]-s_bf[k][l];
				}
				r=sqrt( pow(r_v[0],2) + pow(r_v[1],2)+ pow(r_v[2],2));
			    f=G*m[j]*m_bf[k]/pow(r,2);
				for(l=0;l<3;l++){
					f_v[l] = f*r_v[l]/r;
					a_v[j][l] += - f_v[l]/m[j];
				}
			}
		}
	}
}

