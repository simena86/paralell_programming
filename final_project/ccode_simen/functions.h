#include <stdio.h>
#include <mpi.h>
#include <math.h>

#define PI 3.14159265359 
#define NUM_SAMPLES 10 


void createSampeList(double **sampleList,unsigned int n, unsigned int size_per_proc);
void printSampleList(double **sampleList, int n);


