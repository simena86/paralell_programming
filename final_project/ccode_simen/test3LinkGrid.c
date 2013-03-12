#include "headers.h"


int main(int argc, char *argv[]) {

	h=0; 
	double start,stop, stop1,start1;
	int i,j;
	struct Status s;
	s.cs_size_partition=0;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&s.myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&s.nprocs);
	if(s.myrank==0)
		start = MPI_Wtime();

	// polygons
	struct polygon obstacle1, obstacle2, link1, link2,link3;
	struct point base1, base2, base3;
	generate_obstacles_and_links(&obstacle1, &obstacle2, &link1, &link2, &link3 , &base1 , &base2 , &base3);
	int number_of_obstacles=2;
	struct polygon *obstacle_list;
	obstacle_list=(struct polygon*)malloc(number_of_obstacles*sizeof(struct polygon));
	obstacle_list[0]=obstacle1;
	obstacle_list[1]=obstacle2;
	
	// sample list . modules: function.c
	s.sample_size_per_dim = 40;
	s.sample_size_all_dims = pow(s.sample_size_per_dim,3);
	s.sample_size_per_proc = floor( s.sample_size_all_dims /s.nprocs);
	if(s.myrank==0){
		s.sample_size_per_proc+= s.sample_size_all_dims % s.nprocs;
	}


	s.sample_list = (double **)malloc(sizeof(double*)* s.sample_size_per_proc);
	s.cs_partition = (double **)malloc(sizeof(double*)* s.sample_size_per_proc);
	for(i=0;i<s.sample_size_per_proc ; i++){
		s.sample_list[i] = (double*)malloc(sizeof(double) * 3);
		s.cs_partition[i] = (double*)malloc(sizeof(double) * 3);
		for(j=0;j<3;j++){
		    s.sample_list[i][j] = 0;
			s.cs_partition[i][j] = 0;
		}
	}
	createSampeList(s.sample_list,s.sample_size_per_dim,s.sample_size_per_proc);


	// get free configSpace (cs)  - modules:  freeConfigSpace_mpi.c
	compute3LinkFreeConfigSpace(&s ,base1,base2,base3,link1,link2,link3,obstacle_list,number_of_obstacles);	
	free(obstacle_list);
	get_total_cs_size(&s);
	
	// allocate memory for total config space on proc 0 
	s.cs_total=(double **)malloc(s.cs_size_total*sizeof(double *));
	for(i=0;i<s.cs_size_total;i++){
		s.cs_total[i]=(double *)malloc(3*sizeof(double));
		for(j=0;j<3;j++){
			s.cs_total[i][j]=0;
		}
	}
	
	// distribute free cs - modules: communication.c
	s.offsets=(int*)malloc(sizeof(int)*s.nprocs);
	s.cs_size_per_partition=(int*)malloc(sizeof(int)*s.nprocs);
	for(i=0;i<s.nprocs;i++){
		s.offsets[i]=0;
		s.cs_size_per_partition[i]=0;
	}
	
	get_size_partition_and_offsets(s.cs_size_partition, s.cs_size_per_partition,s.offsets,s.nprocs,s.myrank);
	distribute_total_free_cs(&s);
	
	
	// adjacency table - modules - computeAdjTableForFreeCSpacePoints.c, communication.c	
	double connectRadius=2.2*PI/(s.sample_size_per_dim-1);
	s.adjTable = (unsigned int **)malloc(sizeof(unsigned int*)* s.cs_size_total);
	s.adjTableElementSize = (int*)malloc(sizeof(int)* s.cs_size_total);
	for(i=0;i<s.cs_size_total;i++){
		s.adjTableElementSize[i]=0;
	}
	s.numberOfPoints_adjTab=computeAdjTableForFreeCSpacePoints(&s,connectRadius);
	get_total_elementSize(&s);	
	distribute_total_adjTab(&s);
	

	
	// Shortest Path 
	// int numInSPath = computeBFSPath(3, 60, adjTable, free_cs_size, adjTableElementSize, numPointsAdjTable);

	if(h!=NULL)
		gnuplot_close(h);
	if(s.myrank==0){
		stop = MPI_Wtime();
		printf("run time: %2.5f \n ", stop-start);
	}

	MPI_Finalize();
	return 0;
}
