#include "headers.h"


/* Get the index of each processors start position in the total configuration space and put in an array <- offsets
 * and get the size of each processors cs partition <- size_per_partition 
 * used both for adjacency table and configuration space */
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


/* Allocate memory for the total adjTab, based on total adjTableElementSize. */
void allocate_total_adjTab(struct Status* s){
	int i,j;
	for(i=0 ; i < s->offsets[s->myrank] ; i++){
		s->adjTable[i]=(int *)malloc(sizeof(int)*s->adjTableElementSize[i]);
	}
	for(j=i+s->cs_size_partition ; j < s->cs_size_total ; j++){
		s->adjTable[j]=(int *)malloc(sizeof(int)*s->adjTableElementSize[j]);
	}
}


/* gather and distribute total adjTableElementSize, and allocate 
 * memory in the total adjTable accordingly                   */
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
	allocate_total_adjTab(s);
}

/* get total size of configuration space (cs) */
void get_total_cs_size(struct Status* s){
	MPI_Reduce(&s->cs_size_partition,&s->cs_size_total,1,MPI_INT,MPI_SUM ,0,MPI_COMM_WORLD);
	MPI_Bcast(&s->cs_size_total,1,MPI_INT,0,MPI_COMM_WORLD);
}

/* get toatal number entries in the adjacency table and broadcast to all processors */
void get_total_numberOfPoints(struct Status* s){
	MPI_Reduce(&s->numberOfPoints_adjTab,&s->numberOfPoints_adjTab_total,1,MPI_UNSIGNED,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Bcast(&s->numberOfPoints_adjTab_total,1,MPI_INT,0,MPI_COMM_WORLD);
}


/* convert 2 dimensional array to a 1 dimensional array */
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

/*  convert 1 dimensional array to a 2 dimensional array */
void adjTab1d_to_2d(struct Status *s,unsigned int* adjTab1d){
	int i,j,k,l,m;
	l=0;

	for(i=0;i<s->cs_size_total;i++){
		for(j=0;j<s->adjTableElementSize[i];j++){
			s->adjTable[i][j]=adjTab1d[l];
			l++;
		}
	}
}

/* gather all local adjTable to node 0, and distribute
 * the total to all processors */
void distribute_total_adjTab(struct Status *s){
	int i,j;
	get_total_numberOfPoints(s);
	unsigned int* adjTab1d,*adjTab1d_total, *rcv_cnt_arr,*displacements;
	rcv_cnt_arr=(int*)malloc(sizeof(int)*s->nprocs);
	displacements=(int*)malloc(sizeof(int)*s->nprocs);
	adjTab1d =(unsigned int*)malloc(sizeof(int)*s->numberOfPoints_adjTab);
	adjTab1d_total =(unsigned int*)malloc(sizeof(int)*s->numberOfPoints_adjTab_total);
	for(i=0;i< s->numberOfPoints_adjTab_total ; i++){
		adjTab1d_total[i]=0;
	}
	adjTab_to_1d(s,adjTab1d);	
	get_size_partition_and_offsets(s->numberOfPoints_adjTab,rcv_cnt_arr,displacements,s->nprocs,s->myrank);
	
	// gather all 1d arrays in total 1d array	
	MPI_Gatherv(adjTab1d,s->numberOfPoints_adjTab,MPI_UNSIGNED,
				adjTab1d_total,rcv_cnt_arr,displacements,MPI_UNSIGNED,0,MPI_COMM_WORLD);

	MPI_Bcast(adjTab1d_total,s->numberOfPoints_adjTab_total,MPI_UNSIGNED,0,MPI_COMM_WORLD);
	adjTab1d_to_2d(s,adjTab1d_total);
	free(adjTab1d);
	free(adjTab1d_total);
	free(rcv_cnt_arr);
	free(displacements);

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
	
