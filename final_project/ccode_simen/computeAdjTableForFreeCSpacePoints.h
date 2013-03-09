#include <stdio.h>
#include <math.h>

// Should be in main
/*
	int ** adjTable = (int **)malloc(sizeof(int*)* free_cs_size);
	int * adjTableElementSize = (int*)malloc(sizeof(int)* free_cs_size);
	computeAdjTableForFreeCSpacePoints(free_cs_size, free_configSpace, adjTable, adjTableElementSize, connectRadius);
	print_adjTable(free_cs_size,adjTable, adjTableElementSize);
*/

void computeAdjTableForFreeCSpacePoints(unsigned int free_cs_size,double **free_configSpace, int ** adjTable, int * adjTableElementSize, double maxAdjRadius);
void print_adjTable(unsigned int free_cs_size, int **adjTable, int * adjTableElementSize);
