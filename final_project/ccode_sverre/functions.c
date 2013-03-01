#include <stdio.h>
#define PI 3.14159265359 
#define NUM_SAMPLES 10 
	

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
				sampleList[iter][1] = temp[j%NUM_SAMPLES]; 
				sampleList[iter][2] = temp[k%NUM_SAMPLES];
				iter++;
			}
		}
	}
}




int main(){
	
	int i,j,n;
	double ** sampleList;	//Contains all the samplepoints (x,y,z)
	
	//Allocate sampleList
	n = NUM_SAMPLES*NUM_SAMPLES*NUM_SAMPLES;
	sampleList = (double **)malloc(sizeof(double*)* n);
	for (i=0;i<n;i++){
		sampleList[i] = (double*)malloc(sizeof(double) * 3);
		for(j=0;j<3;j++){
			sampleList[i][j] = 0;
		}
	}
	
	createSampeList(sampleList);
	

	return 0;
}