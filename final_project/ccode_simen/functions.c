#include "functions.h"


// Create a grid (qube) of sample points
// Number of totale sample points = NUM_SAMPLES^3
void createSampeList(double **sampleList){
	int i,j,k,iter;
	double sampleInterval = 2*PI / NUM_SAMPLES;
	double temp[NUM_SAMPLES];

	for(i=0;i<NUM_SAMPLES;i++){
		temp[i] = -PI + sampleInterval*i;
	}
	
	iter=0;
	for(i=0;i<NUM_SAMPLES;i++){
		for(j=0;j<NUM_SAMPLES;j++){
			for(k=0;k<NUM_SAMPLES;k++){
				sampleList[iter][0] = temp[i%NUM_SAMPLES]; 
				sampleList[iter][1] = temp[j]; 
				sampleList[iter][2] = temp[k%NUM_SAMPLES];
				iter++;
			}
		}
	}
}

void printSampleList(double **sampleList, int n){
	int i;
	for(i=0;i<n;i++){
		printf("%f  %f  %f  \n", sampleList[i][0],sampleList[i][1],sampleList[i][2]);
	}
}

