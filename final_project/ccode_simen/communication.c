#include "headers.h"

void gather_free_cs(unsigned int* free_cs_size_total,double** free_configSpace_total,unsigned int* free_cs_size, double** free_configSpace){
	int i,j;
	int myrank, nprocs;
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
	
	/* prepare a send and receive buffer*/
	double **cs_send_bfr, *cs_rcv_bfr;
	int* displacement,*rcvcount;
	displacement=(int *)malloc(nprocs*sizeof(int));
	rcvcount=(int *)malloc(nprocs*sizeof(int));

	
	int size_i=0,temp_size;
	MPI_Gather(free_cs_size,1,MPI_INT,displacement,1,MPI_INT,0,MPI_COMM_WORLD);

	if(myrank==0){	
		for(i=0;i<nprocs;i++){
			rcvcount[i]=displacement[i];
			displacement[i]=size_i;
			size_i+=rcvcount[i];
		}
	}

	cs_send_bfr=(double** )malloc(3*sizeof(double* ));
	cs_rcv_bfr=(double*)malloc(*free_cs_size_total*sizeof(double));
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
	free(displacement);
	free(rcvcount);
	free(cs_rcv_bfr);
	for(i=0;i<3;i++){
		free(cs_send_bfr[i]);
	}
	free(cs_send_bfr);
	
}
	
