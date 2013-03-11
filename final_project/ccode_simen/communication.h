#ifndef _COMMUN_
#define _COMMUN_



unsigned int get_cs_offset(int myrank, int nprocs,unsigned int* free_cs_size);

void gather_free_cs(struct Status *s);

void sum_numPoints_allProcs(unsigned int* numPointsAdjTable);


void distribute_total_adjTable(unsigned int offset,unsigned int* free_cs_size, unsigned int* free_cs_size_total,
																	int** adjTable,int* adjTableElementSize,unsigned int numPointsAdjTable);
#endif
