#include <stdio.h>

#define PI 3.14159265359 
#define NUM_SAMPLES 10 


struct point{
	double x;
	double y;
	double z;
};

void createSampeList(double **sampleList);
void printSampleList(double **sampleList, int n);
void computeAdjTableForFreeCSpacePoints(double ** p, int n, double maxAdjRadius);


