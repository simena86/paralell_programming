#include "headers.h"

int main(int argc, char *argv[]) {
	h=0; // handler for gnuplot	
	double start,stop;
	MPI_Init(&argc,&argv);
	int myrank, nprocs;
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
	start = MPI_Wtime();
	unsigned int free_cs_size=0;
	// ------------- polygons- ----------- //
	struct polygon obstacle1, obstacle2, link1, link2,link3;
	struct point base1, base2, base3;
	generate_obstacles_and_links(&obstacle1, &obstacle2, &link1, &link2, &link3 , &base1 , &base2 , &base3);
	int number_of_obstacles=2;
	struct polygon *obstacle_list;
	obstacle_list=(struct polygon*)malloc(number_of_obstacles*sizeof(struct polygon));
	obstacle_list[0]=obstacle1;
	obstacle_list[1]=obstacle2;
	// ------------ sample list ------------------//
	int i,j, size_per_proc, n,n_cube;
	n = 5;
	n_cube=n*n*n;
	size_per_proc = floor(n_cube/nprocs);
	if(myrank==0){
		size_per_proc+=n_cube % nprocs;
	}
	double ** sampleList;
	double ** free_configSpace;
	sampleList = (double **)malloc(sizeof(double*)* size_per_proc);
	free_configSpace = (double **)malloc(sizeof(double*)* size_per_proc);
	for(i=0;i<size_per_proc ; i++){
		sampleList[i] = (double*)malloc(sizeof(double) * 3);
		free_configSpace[i] = (double*)malloc(sizeof(double) * 3);
		for(j=0;j<3;j++){
			free_configSpace[i][j] = -1;
			sampleList[i][j] = 0;
		}
	}
	printf("myrank %d, size_per_proc %d \n", myrank, size_per_proc);
	createSampeList(sampleList,n,size_per_proc);
	compute3LinkFreeConfigSpace(size_per_proc,sampleList,&free_cs_size,free_configSpace,base1,base2,base3,link1,link2,link3,obstacle_list, number_of_obstacles);
	unsigned int free_cs_size_total;
	MPI_Reduce(&free_cs_size,&free_cs_size_total,1,MPI_INT,MPI_SUM ,0,MPI_COMM_WORLD);
	if(myrank==0){
		printf("\n total free config space %d \n ",free_cs_size_total);
	}

	// ------------ adjacency table --------//
	double connectRadius=2.2*PI/(n-1);
	int ** adjTable = (int **)malloc(sizeof(int*)* free_cs_size);
	int * adjTableElementSize = (int*)malloc(sizeof(int)* free_cs_size);
	computeAdjTableForFreeCSpacePoints(free_cs_size, sampleList, adjTable, adjTableElementSize, connectRadius);
	print_adjTable(free_cs_size,adjTable, adjTableElementSize);
	
	
	
	
	//	printf("free ws space %d\n ", free_cs_size);
//	if(h!=NULL)
//		gnuplot_close(h);
//	return 0;
	if(myrank==0){
		stop = MPI_Wtime();
		printf("run time: %2.5f \n ", stop-start);
	}
	MPI_Finalize();
}
