#ifndef _MY_TYPES_
#define _MY_TYPES_

#ifndef FALSE 
	#define FALSE 0
#endif 
#ifndef TRUE
	#define TRUE 1
#endif

struct Status {
	
	int sample_size_per_dim;
	int sample_size_all_dims;
	int sample_size_per_proc;
	double** sample_list;
	double** cs_partition;
	double** cs_total;
	int** adjTable;
	int* adjTableElementSize;
	int cs_size_partition;
	int cs_size_total;
	int* offsets;
	int* cs_size_per_partition;
	int myrank;
	int nprocs;
	unsigned int numberOfPoints_adjTab;
};


struct polygon{
	double *x_list;
	double *y_list;	
	int	numberOfVertices;
};
	
struct point{
	double x;
	double y;
};	

#endif
