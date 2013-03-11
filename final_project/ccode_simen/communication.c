#include "headers.h"


void get_total_cs_size(struct Status* s){
	MPI_Reduce(&s->cs_size_partition,&s->cs_size_total,1,MPI_INT,MPI_SUM ,0,MPI_COMM_WORLD);
	MPI_Bcast(&s->cs_size_total,1,MPI_INT,0,MPI_COMM_WORLD);
}

void get_offsets(struct Status *s){
	int i,temp_size,size_i;
	size_i=0;
	
	MPI_Gather(&s->cs_size_partition,1,MPI_INT,s->offsets,1,MPI_INT,0,MPI_COMM_WORLD);
	if(s->myrank==0){	
		for(i=0;i<s->nprocs;i++){
			s->cs_size_per_partition[i]=s->offsets[i];
			s->offsets[i]=size_i;
			size_i+=s->cs_size_per_partition[i];
		}
	}
	MPI_Bcast(s->offsets,s->nprocs,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(s->cs_size_per_partition,s->nprocs,MPI_INT,0,MPI_COMM_WORLD);
}


void gather_free_cs(struct Status* s){
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
	 * distribute total free config  to all processors 								
	 */


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
	
