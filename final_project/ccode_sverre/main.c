#include "functions.h"


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
	printSampleList(sampleList,n);	


	struct point p[3];
	p[1]->x=2;
	p[1]->y=3;
	p[1]->z=4;
	
	computeAdjTableForFreeCSpacePoints(p,3);


	return 0;
}
