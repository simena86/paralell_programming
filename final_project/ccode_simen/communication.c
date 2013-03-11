#include "headers.h"


void get_size_partition_and_offsets(unsigned int size_partition,  unsigned int* size_per_partition,unsigned int* offsets, int nprocs,int myrank){
	int i,temp;
	temp=0;
	MPI_Gather(&size_partition,1,MPI_UNSIGNED,size_per_partition,1,MPI_UNSIGNED,0,MPI_COMM_WORLD);	
	if(myrank==0){	
		for(i=0;i<nprocs;i++){
			offsets[i]=temp;
			temp+=size_per_partition[i];
		}
	}
	MPI_Bcast(offsets,nprocs,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(size_per_partition,nprocs,MPI_INT,0,MPI_COMM_WORLD);
}


void get_total_elementSize(struct Status *s){
	int i,j,k;
	k=0;
	unsigned int *elementSize_local;
	elementSize_local=(int*)malloc(sizeof(int)* s->cs_size_partition);
	for(i=s->offsets[s->myrank]; i < s->offsets[s->myrank] + s->cs_size_partition ; i++){
		elementSize_local[k]=s->adjTableElementSize[i];
		k++;	
	}
	MPI_Gatherv(elementSize_local,s->cs_size_partition,MPI_UNSIGNED,s->adjTableElementSize,
				s->cs_size_per_partition,s->offsets,MPI_UNSIGNED,0,MPI_COMM_WORLD);
	MPI_Bcast(s->adjTableElementSize,s->cs_size_total,MPI_UNSIGNED,0,MPI_COMM_WORLD);
	free(elementSize_local);
}

void get_total_cs_size(struct Status* s){
	MPI_Reduce(&s->cs_size_partition,&s->cs_size_total,1,MPI_INT,MPI_SUM ,0,MPI_COMM_WORLD);
	MPI_Bcast(&s->cs_size_total,1,MPI_INT,0,MPI_COMM_WORLD);
}


void get_total_numberOfPoints(struct Status* s){
	MPI_Reduce(&s->numberOfPoints_adjTab,&s->numberOfPoints_adjTab_total,1,MPI_UNSIGNED,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Bcast(&s->numberOfPoints_adjTab_total,1,MPI_INT,0,MPI_COMM_WORLD);
}

void adjTab_to_1d(struct Status *s,int* adjTab1d){
	int i,j,k;
	k=0;
	for(i=s->offsets[s->myrank] ;  i < s->offsets[s->myrank] + s->cs_size_partition ;i++){
		for(j=0; j < s->adjTableElementSize[i];j++){
			adjTab1d[k] = s->adjTable[i][j]; 
			k++;			
		}			
	}
}


void adjTab1d_to_2d(struct Status *s,int* adjTab1d){
	int i,j,k,l,m;
	l=0;
	m=0;
	for(i=0;i<s->nprocs;i++){
		for(j=0;j<s->cs_size_per_partition[i];j++){
			for(k=0;k < s->adjTableElementSize[m] ; k++){
				if(s->myrank==1)
					printf("m %d adjTab %d adjTableElementSize %d \n",m,adjTab1d[l],s->adjTableElementSize[m]);
				s->adjTable[m][k] = adjTab1d[l];
				l++;
			}
			m++;
		}
	}
	printf("rank %d, l %d totnyn %d \n",s->myrank,l, s->numberOfPoints_adjTab_total);
}

void distribute_total_adjTab(struct Status *s){
	int i,j;
	get_total_numberOfPoints(s);
	unsigned int* adjTab1d,*adjTab1d_total, *rcv_cnt_arr,*displacements;
	rcv_cnt_arr=(int*)malloc(sizeof(int)*s->nprocs);
	displacements=(int*)malloc(sizeof(int)*s->nprocs);
	adjTab1d =(unsigned int*)malloc(sizeof(int)*s->numberOfPoints_adjTab);
	adjTab1d_total =(unsigned int*)malloc(sizeof(int)*s->numberOfPoints_adjTab_total);
	adjTab_to_1d(s,adjTab1d);	
	get_size_partition_and_offsets(s->numberOfPoints_adjTab,rcv_cnt_arr,displacements,s->nprocs,s->myrank);
	
	// gather all 1d arrays in total 1d array	
	MPI_Gatherv(adjTab1d,s->numberOfPoints_adjTab,MPI_UNSIGNED,
				adjTab1d_total,rcv_cnt_arr,displacements,MPI_UNSIGNED,0,MPI_COMM_WORLD);

	MPI_Bcast(adjTab1d,s->numberOfPoints_adjTab_total,MPI_UNSIGNED,0,MPI_COMM_WORLD);
	adjTab1d_to_2d(s,adjTab1d_total);
}




void distribute_total_free_cs(struct Status* s){
	int i,j;
	/* prepare a send and receive buffer*/
	double **cs_send_bfr, *cs_rcv_bfr;
	cs_send_bfr=(double** )malloc(3*sizeof(double* ));
	cs_rcv_bfr=(double*)malloc(s->cs_size_total*sizeof(double));
	for(i=0;i<3;i++){
		cs_send_bfr[i]=(double* )malloc(s->cs_size_partition*sizeof(double));
		for(j=0;j<s->cs_size_partition;j++){
			cs_send_bfr[i][j]=s->cs_partition[j][i];
		}
	}
	/* gather all partitions of free config space  in proc 0, and then 
	 * distribute total free config  to all processors 		 */						
	for(i=0;i<3;i++){
		MPI_Gatherv(cs_send_bfr[i],s->cs_size_partition,MPI_DOUBLE,cs_rcv_bfr,s->cs_size_per_partition,s->offsets,MPI_DOUBLE,0,MPI_COMM_WORLD);
		MPI_Bcast(cs_rcv_bfr,s->cs_size_total,MPI_DOUBLE,0,MPI_COMM_WORLD);
		for(j=0;j<s->cs_size_total;j++){
			s->cs_total[j][i]=cs_rcv_bfr[j];
		}
	}
	free(cs_rcv_bfr);
	for(i=0;i<3;i++){
		free(cs_send_bfr[i]);
	}
	free(cs_send_bfr);
}
	
