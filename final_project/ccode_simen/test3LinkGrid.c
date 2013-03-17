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

	s.sample_size_per_dim = 20;
	if(argc==2){
		s.sample_size_per_dim = atoi(argv[1]);
	}

	// sample list . modules: function.c
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
	createSampeList(s);

	// get free configSpace (cs)  - modules:  freeConfigSpace_mpi.c
	compute3LinkFreeConfigSpace(&s);	
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
	double connectRadius=2.5*PI/(s.sample_size_per_dim-1);
	s.adjTable = (unsigned int **)malloc(sizeof(unsigned int*)* s.cs_size_total);
	s.adjTableElementSize = (int*)malloc(sizeof(int)* s.cs_size_total);
	for(i=0;i<s.cs_size_total;i++){
		s.adjTableElementSize[i]=0;
	}
	s.numberOfPoints_adjTab=computeAdjTableForFreeCSpacePoints(&s,connectRadius);
	
	get_total_elementSize(&s);	
	distribute_total_adjTab(&s);
	

	// Shortest Path 
	if(s.myrank==0){
		int bfsSize;
		int* bfsPath;
		bfsPath=(int*)malloc(sizeof(int));
		start1=MPI_Wtime();
		computeBFSPath(3,15,s.adjTable,s.cs_size_total,s.adjTableElementSize,s.numberOfPoints_adjTab_total,bfsPath,&bfsSize);	
		stop1=MPI_Wtime() - start1;
		printf("Bfs runtime %1.4f \n",stop1);
		printf("Bfs size %d edges size %d \n",bfsSize,s.numberOfPoints_adjTab_total);
		puts("\nNodes in shortest path: \n");
		draw_shortest_path(s,bfsSize,bfsPath);

		for(i=0;i<bfsSize;i++){
			//printf("node i %d, %d \n",i,bfsPath[i]);
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);	
	if(h!=NULL)
		gnuplot_close(h);
	if(s.myrank==0){
		stop = MPI_Wtime();
		printf("Total run time: %2.5f \n ", stop-start);
	}

	MPI_Finalize();
	return 0;
}
