#include"powermethod.h"

void mygeneratematrix(double *mat, int size, int mat_select)
{

	int myrank;
	int i,j;
	int nprocs;
	
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&nprocs);

	switch(mat_select){
		
	case 0:

		for(i = 0; i < size/nprocs; i++)
		{
			for(j = myrank*size/nprocs; j < size; j++)
			{
				if(i == j)
				{
					mat[i*size + j] = 2;		
				}	
				else
					mat[i*size + j] = 1;
			}
		}

		break;

	case 1:
			
		for(i = 0; i < size/nprocs; i++)
		{
			for(j = 0; j < i; j++)
			{
				mat[i*size + j] = myrank + i + 1;			
			}
		}

		break;
	
	case 2:

		
		for(i = 0; i < size/nprocs; i++)
		{
			for(j = 0; j < size; j++)
			{
				if(i == j)
				{
					mat[i*size + j] = 1;		
				}	
				else
					mat[i*size + j] = 1;
			}
		}

		break;
	}
}