#include "headers.h"

void gather_free_cs(unsigned int* free_cs_size_total,double** free_configSpace_total,unsigned int* free_cs_size, double** free_configSpace){
	int i,j;
	int myrank, nprocs;
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
	MPI_Reduce(free_cs_size,free_cs_size_total,1,MPI_INT,MPI_SUM ,0,MPI_COMM_WORLD);
	/* allocate memory for total config space on proc 0 */
	if(myrank==0){
		free_configSpace_total=(double **)malloc(*free_cs_size_total*sizeof(double *));
		for(i=0;i<*free_cs_size_total;i++){
			free_configSpace_total[i]=(double *)malloc(3*sizeof(double *));
		}
	}
	/* prepare a send and receive buffer*/
	double **cs_send_bfr, *cs_rcv_bfr;
	int* displacement,*rcvcount;
	displacement=(int *)malloc(nprocs*sizeof(int));
	rcvcount=(int *)malloc(nprocs*sizeof(int));

	if(myrank==0){
		for(i=0;i<nprocs;i++){
			displacement[i]=0;
			printf("displacement %d\n", displacement[i]);
		}
	}
	int size_i=0,temp_size;
	MPI_Gather(free_cs_size,1,MPI_INT,displacement,1,MPI_INT,0,MPI_COMM_WORLD);
//	if(myrank==0){	
		for(i=0;i<nprocs;i++){
			rcvcount[i]=displacement[i];
			displacement[i]=size_i;
			size_i+=rcvcount[i];
			if(myrank==0)	
				printf("rcvcount %d, displ %d \n", rcvcount[i], displacement[i]);;
		}
//	}
	cs_send_bfr=(double** )malloc(3*sizeof(double* ));
	cs_rcv_bfr=(double*)malloc(*free_cs_size_total*sizeof(double* ));
	for(i=0;i<3;i++){
		cs_send_bfr[i]=(double* )malloc(*free_cs_size*sizeof(double));
		for(j=0;j<*free_cs_size;j++){
			cs_send_bfr[i][j]=free_configSpace[j][i];
		}
	}
	if(myrank==5){
		for(j=0;j<*free_cs_size;j++){
			for(i=0;i<3;i++){
				printf(" %2.2f", cs_send_bfr[i][j]);
		}
		puts("\n");
	}
		
	
	}
	for(i=0;i<3;i++){
		MPI_Gatherv(cs_send_bfr[i],*free_cs_size,MPI_DOUBLE,cs_rcv_bfr,rcvcount,displacement,MPI_DOUBLE,0,MPI_COMM_WORLD);
		if(myrank==0){
			for(j=0;j<*free_cs_size_total;j++){
				free_configSpace_total[j][i]=cs_rcv_bfr[j];
			}
		}
	}
	
	if(myrank==0){
		for(i=0;i<*free_cs_size_total;i++){
			for(j=0;j<3;j++){
				printf(" %2.2f ", free_configSpace_total[i][j]);
			}
			puts(" ");
		}
	}
	
}
	


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
	n = 10 ;
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
	createSampeList(sampleList,n,size_per_proc);

	/* -------- compute free config space --------- */
	compute3LinkFreeConfigSpace(size_per_proc,sampleList,&free_cs_size,free_configSpace,base1,base2,base3,link1,link2,link3,obstacle_list, number_of_obstacles);
	unsigned int free_cs_size_total;
	double** free_configSpace_total;
	
	gather_free_cs(&free_cs_size_total, free_configSpace_total,&free_cs_size, free_configSpace);
	if(myrank==0){
		printf("size %d \n", free_cs_size_total);
		print_help
	//		printf("size free cs = %d \n",free_cs_size_total);
	}	
	

	// ------------ adjacency table --------//
//	double connectRadius=2.2*PI/(n-1);
//	int ** adjTable = (int **)malloc(sizeof(int*)* free_cs_size);
//	int * adjTableElementSize = (int*)malloc(sizeof(int)* free_cs_size);
//	computeAdjTableForFreeCSpacePoints(free_cs_size, sampleList, adjTable, adjTableElementSize, connectRadius);
//	print_adjTable(free_cs_size,adjTable, adjTableElementSize);
	
	
	
	
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
