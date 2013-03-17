#ifndef _HALTON_
#define _HALTON_
#include <stdio.h>
#include <mpi.h>
#include <math.h>

#define PI 3.14159265359 
#define NUM_SAMPLES 10 


void createSampeList(struct Status s);
void printSampleList(double **sampleList, int n);

#endif
