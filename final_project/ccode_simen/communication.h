#ifndef _COMMUN_
#define _COMMUN_




void get_total_elementSize(struct Status *s);
void get_size_partition_and_offsets(unsigned int size_partition,  unsigned int* size_per_partition,unsigned int* offsets, int nprocs,int myrank);

void distribute_total_free_cs(struct Status* s);

void sum_numPoints_allProcs(unsigned int* numPointsAdjTable);


void distribute_total_adjTab(struct Status *s);
#endif
