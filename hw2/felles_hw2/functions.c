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

double norm2(double * x, int size){
	int i;
	double the_norm = 0;
	for(i = 0; i < size; i++){
		the_norm = the_norm + (x[i] * x[i]);
	}
	return sqrt(the_norm);
}


void matVec(double * mat, double * x,double * out, int size){
	int debug=0;
	int i,j, nprocs, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	for(i = 0; i < size/nprocs; i++){
		out[i] = 0;
	}
	for(i = 0; i < size/nprocs; i++){
		for(j = 0; j < size; j++)
		{
			out[i] += mat[i*size + j] * x[j];	
		}
	}

	// gathering vectors from every processor to processor 0
	if (rank==0){
		MPI_Gather(out,size/nprocs,MPI_DOUBLE,x,size/nprocs,MPI_DOUBLE, 0,MPI_COMM_WORLD);
	}else{
			MPI_Gather(out,size/nprocs,MPI_DOUBLE,x,size/nprocs,MPI_DOUBLE, 0,MPI_COMM_WORLD);
	}
	// broadcasting vectors from processor 0
	MPI_Bcast(x,size,MPI_DOUBLE,0,MPI_COMM_WORLD);
}

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
			//mat[i*size +j]=i*j-i*i*3 +2*j;
			//printf(" %f ",mat[i*size+j]);
		}
		//printf("\n");
	}
}


// Subroutine to generate a random vector
void generatevec(double * x,int size)
{
	int i;
	for(i = 0; i < size; i++){
		x[i] = 1;
	}	
}

// Subroutine for the power method, to return the spectral radius
double powerMethod(double * mat, double * x, int size, int iter)
{
	int nprocs, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int i,j;
	double the_norm;
	double out[size/nprocs];	
	
	for(i = 0; i < iter; i++){
		the_norm = norm2(x, size);
		
		for(j = 0; j < size; j++){
			x[j] = x[j] / the_norm;
		}
		
		matVec(mat, x,out,size);
	}
		
	return norm2(x, size);
}






















