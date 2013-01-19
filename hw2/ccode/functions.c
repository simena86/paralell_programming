/* CS 140
 * Assignment 1 : Matrix Vector Multiplication and the Power Method 
 * Group members : <Team-member-1> , <Team-member-2>
 * */

/* This file provides the placeholder function definitions, where you will be
 * implementing the assignment algorithms. You will be required to turn in 
 * only this file during the submission, where it will be compiled together
 * with our main function and tested. It is therefore required that you keep the 
 * function declaration formats unchanged.
 */

#include "powermethod.h"

// Subroutine for generating the input matrix
void generatematrix(double * mat, int size){
	int rank, nprocs;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	int i, j;
	for (i=0 ; i < size/nprocs; i++){
		for ( j=0; j<size; j++){
			if ( j<=rank*size/nprocs+i){
				mat[i*size + j ] =rank*size/nprocs+i+1;
			}else{
				mat[i*size + j ] = 0;
			}
		}
	}	
}

// Subroutine to generate a random vector
void generatevec(double * x,int size){
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int i;
	for (i=0;i<size;i++){
		x[i]=1;	
	}
}

// Subroutine for the power method, to return the spectral radius
double powerMethod(double * mat, double * x, int size, int iter){
	return 1.618;
}


double norm2(double *  x, int size){
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	double r=0;	
	int i;
	for(i=0; i<size;i++ ){
		r=r + x[i]*x[i];
	}
	return sqrt(r);	
}
