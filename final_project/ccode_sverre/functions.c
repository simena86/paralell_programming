#include "functions.h"

// Create a grid (qube) of sample points
// Number of totale sample points = NUM_SAMPLES^3
void createSampeList(double **sampleList,unsigned int n,unsigned int size_per_proc){
	int myrank, nprocs;
	int i,j,k,iter;
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
	int proc0extra_term = 0;
	int n_p = floor(n/nprocs);
	if(myrank!=0){
		proc0extra_term = n*n*n % nprocs;	
	}else{
		n_p+= n % nprocs;
	}
	
	double temp[n];
	double interval = 2*PI/n;
	for(i=0;i<n;i++){
		temp[i] =-PI + i*interval; 
	}	
	int number = proc0extra_term + myrank*(size_per_proc) ;
	k = number % n;
	number/=n;
	j= number % n;
	number/=n;
	i= number % n;
	number = proc0extra_term + myrank*(size_per_proc) ;
	for(iter=0;iter<size_per_proc;iter++){
		sampleList[iter][0] = temp[i]; 
		sampleList[iter][1] = temp[j]; 
		sampleList[iter][2] = temp[k];
		k++;
		if((iter + number +1 ) % n == 0){
			j++;
			k=0;	
		}if((iter +  number +1) % (n*n) == 0){
			i++;
			j=0;	
		}
	}
}

void printSampleList(double **sampleList, int n){
	int i;
	for(i=0;i<n;i++){
		printf("%f  %f  %f  \n", sampleList[i][0],sampleList[i][1],sampleList[i][2]);
	}
}

