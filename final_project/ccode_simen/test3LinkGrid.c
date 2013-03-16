#include "headers.h"



int main(int argc, char *argv[]) {
	unsigned int free_cs_size=0;
	h=0; 
	unsigned int numPointsAdjTable;	
	double start,stop, stop1,start1;

	MPI_Init(&argc,&argv);
	int myrank, nprocs;
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
	if(myrank==0)
		start = MPI_Wtime();


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
	n = 20;
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
			sampleList[i][j] = 0;
			free_configSpace[i][j] = 0;
		}
	}

	if(myrank==1)
		start1 = MPI_Wtime();
	createSampeList(sampleList,n,size_per_proc);
	if(myrank==1){
		stop1 = MPI_Wtime();
		printf("create sampleList took %2.5f seconds \n", stop1-start1);
	}



	// -------- compute free config space --------- //
	if(myrank==0)
		start1 = MPI_Wtime();

	compute3LinkFreeConfigSpace(size_per_proc,sampleList,&free_cs_size,free_configSpace,base1,base2,base3,link1,link2,link3,obstacle_list, 
					number_of_obstacles);	

	if(myrank==0){
		stop1 = MPI_Wtime();
		printf("compute3link took %2.5f seconds \n", stop1-start1);
	}
	
	// free memory for sampleList 
	free(obstacle_list);
	for(i=0;i<size_per_proc;i++){
		free(sampleList[i]);
	}
	free(sampleList);
	
	// allocate memory for total config space on proc 0 
	unsigned int free_cs_size_total;
	double** free_configSpace_total;
	MPI_Reduce(&free_cs_size,&free_cs_size_total,1,MPI_INT,MPI_SUM ,0,MPI_COMM_WORLD);
	if(myrank==0){
		free_configSpace_total=(double **)malloc(free_cs_size_total*sizeof(double *));
		for(i=0;i<free_cs_size_total;i++){
			free_configSpace_total[i]=(double *)malloc(3*sizeof(double));
			for(j=0;j<3;j++){
				free_configSpace_total[i][j]=0;
			}
		}
	}

	
	
	if(myrank==0)
		start1 = MPI_Wtime();
	gather_free_cs(&free_cs_size_total, free_configSpace_total,&free_cs_size, free_configSpace);
	if(myrank==0){
		stop1 = MPI_Wtime();
		printf(" gather free cs took %2.5f seconds \n", stop1-start1);
		//	print_free_configSpace(free_cs_size_total,free_configSpace_total);
	}

	// adjacency table	
	if(myrank==0){	
		double connectRadius=2.2*PI/(n-1);
		int ** adjTable = (int **)malloc(sizeof(int*)* free_cs_size);
		int * adjTableElementSize = (int*)malloc(sizeof(int)* free_cs_size);
		numPointsAdjTable = computeAdjTableForFreeCSpacePoints(free_cs_size, sampleList, adjTable, adjTableElementSize, connectRadius);
		//print_adjTable(free_cs_size,adjTable, adjTableElementSize);
		//printf("numPoints: %d\n", numPointsAdjTable);
		//draw_adjTable(free_cs_size_total,free_configSpace_total,adjTableElementSize,adjTable,1000000000);	
	
		//------- Shortest Path ----------------------
	
		int * pathTable= (int*)malloc(sizeof(int));
		int pathSize;
	//	pathTable = (int*)malloc(sizeof(int) * 2);
	

		computeBFSPath(3, 60, adjTable, free_cs_size, adjTableElementSize, numPointsAdjTable, pathTable, &pathSize);
		printf("length: %d \n", pathSize);
		for(i=0;i<pathSize;i++){
			printf("%d\n", pathTable[i]);
		} 

	}



	if(h!=NULL)
		gnuplot_close(h);
/*
	if(myrank==0){
		stop = MPI_Wtime();
		printf("run time: %2.5f \n ", stop-start);
	}
*/	
	MPI_Finalize();
	return 0;
}
