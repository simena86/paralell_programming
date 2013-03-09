#ifndef _compAdj_
#define _compAdj_

#include "headers.h"

// Should be in main
/*
	double connectRadius=2.2*PI/(n-1);
    int ** adjTable = (int **)malloc(sizeof(int*)* free_cs_size);
	int * adjTableElementSize = (int*)malloc(sizeof(int)* free_cs_size);
	computeAdjTableForFreeCSpacePoints(free_cs_size, free_configSpace, adjTable, adjTableElementSize, connectRadius);
	print_adjTable(free_cs_size,adjTable, adjTableElementSize);
*/

void computeAdjTableForFreeCSpacePoints(unsigned int free_cs_size_total, double **free_configSpace_total,
										unsigned int free_cs_size,double **free_configSpace, int ** adjTable, int * adjTableElementSize, double maxAdjRadius);
void print_adjTable(unsigned int free_cs_size, int **adjTable, int * adjTableElementSize);

#endif
