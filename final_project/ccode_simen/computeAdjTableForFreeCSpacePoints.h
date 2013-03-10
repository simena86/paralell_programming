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

// computes partition of adjacency table for index "offset" to "offset + free_cs_size_total"
int computeAdjTableForFreeCSpacePoints(unsigned int offset, unsigned int free_cs_size_total, double **free_configSpace_total,
						unsigned int free_cs_size,double **free_configSpace, int ** adjTable, int * adjTableElementSize, double maxAdjRadius);


// prints the partition of the total adjcency table, beginning from "offset"
void print_adjTable(unsigned int offset,unsigned int free_cs_size, int **adjTable, int * adjTableElementSize);

#endif
