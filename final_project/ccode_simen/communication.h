#ifndef _COMMUN_
#define _COMMUN_



unsigned int get_cs_offset(int myrank, int nprocs,unsigned int free_cs_size);

void gather_free_cs(unsigned int* free_cs_size_total,double** free_configSpace_total,unsigned int* free_cs_size,
				    double** free_configSpace);

void sum_numPoints_allProcs(unsigned int* numPointsAdjTable);

#endif
