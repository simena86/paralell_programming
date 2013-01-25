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
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	double** a_v;
	double size=n/nprocs;

	a_v = (double **)malloc(sizeof(double *) * size);
	for (i = 0; i < size; i++) {
		a_v[i] = (double*)malloc(sizeof(double) * 3);
		for(j = 0; j < 3; j++) {
			a_v[i][j] = 0;
		}
	}

	

	for(I=0; I<iter ; I++){
		for(i=0; i<nprocs; i++){

		}
	}

	//DEBUG
	if (myrank == 0) {
		for (i = 0; i < n / nprocs; i++) {
			fprintf(stderr, OUTPUT_BODY, s[i][0], s[i][1], s[i][2], v[i][0], v[i][1], v[i][2], m[i]);
		}
	}
}


void compute_acceleration(double ** a, double ** s, double* m) {
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
					r_v[l]=s[j][l]-s[k][l];
				}
				r=sqrt( pow(r_v[0],2) + pow(r_v[1],2)+ pow(r_v[2],2));
			    f=G*m[j]*m[k]/pow(r,2);
				for(l=0;l<3;l++){
					f_v[l] = f*r_v[l]/r;
					a_v[j][l] =a_v[j][l] - f_v[l]/m[j];
				}
			}
		}
	}
}

