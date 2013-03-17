#include "headers.h"

double halton(int i, int base){
	double x=0;
	double f=(double)1/base;
	double itmp=(double)i;
	while(i>0){
		x=x+f*(i % base);
		i=floor(i/base);
		f=f/base;	
	}
	return x;
}

void createSampeList(struct Status s){
	int i,j,iter;
	int n;
	int extraTerm=0;
	n=s.sample_size_per_dim;
	if(s.myrank!=0){
		extraTerm=(n*n*n) % s.nprocs;
	}
	unsigned int offset;
	double x,y,z;
	unsigned int k;
	k=s.myrank*s.sample_size_per_proc+extraTerm;
	for(iter=0;iter<s.sample_size_per_proc;iter++){
		x=halton(k,2);	
		y=halton(k,3);	
		z=halton(k,5);
		s.sample_list[iter][0] =2*PI*x-PI; 
		s.sample_list[iter][1] =2*PI*y-PI; 
		s.sample_list[iter][2] = 2*PI*z-PI;
		k++;
	}
}

void printSampleList(double **sampleList, int n){
	int i;
	for(i=0;i<n;i++){
		printf("%f  %f  %f  \n", sampleList[i][0],sampleList[i][1],sampleList[i][2]);
	}
}

