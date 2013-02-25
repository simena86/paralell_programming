/*
Homework 5 : The Game of Life.
Team member 1 : Sverre Kvamme 
Team member 2 : Simen Andresen
*/

#include "life.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;

extern int * livecount;

//Generate the life matrix any way you want. We would highly recommend that you print the generated
//matrix into a file, so that you can share it with other teams for checking correctness.
void genlife(int *a, unsigned int n)
{
	//The glider
	int i,j,k,p;
	for(i=0;i<n;i++){
		for (j=0;j<n;j++){
			a[i*n + j]=0;	
		}
	}

	k = round(n/3);
	p = round(n/5);
	
	a[k*n + p] 	= 1; 		
	a[k*n + p+1] 	= 1; 		
	a[k*n + p+2] 	= 1; 		

	a[(k+1)*n + p] 	 = 1; 		
	a[(k+1)*n + p+1] = 0; 		
	a[(k+1)*n + p+2] = 0; 		

	a[(k+2)*n + p]	 = 0; 		
	a[(k+2)*n + p+1] = 1;
	a[(k+2)*n + p+2] = 0;
	
}

//Read the life matrix from a file
void readlife(int *a, unsigned int n){
	int zeros;	
	string filename;		
	if (!(n==10 || n==20 || n==100 || n==200)){
		printf("n must be 10, 20 , 100 or 200 in readlife\n");
		// set to -1 for debugging
		a[0]=-1; 
		return;
	}

	// read from file
	int val;
	string line;
	for(int i = 0;i<n;i++){
 	 	getline(cin,line);
		istringstream iss(line);
		for(int j=0;j<n;j++){
			iss >> val;
			a[i*n+j]=val;
		}
	}
}


/*	count all the neighbours 
 *	around cell in row i column j of a
 *  return number of neighbours		*/
int count_nbr(char *a, int n, int i, int j){
	char nbr=0;
	int i_south, i_north,j_west,j_east;
	if(i==0){
		i_north=n-1;
		i_south=1;
	}else if(i==n-1){
		i_south=0;
		i_north=n-2;
	}else{
		i_south=i+1;
		i_north=i-1;
	}if(j==0){
		j_west=n-1;
		j_east=1;
	}else if(j==n-1){
		j_east=0;
		j_west=n-2;
	}else{
		j_east=j+1;
		j_west=j-1;
	}
	nbr+=a[i*n + j_east];
	nbr+=a[i*n + j_west];
	nbr+=a[i_south*n + j];
	nbr+=a[i_north*n + j ];
	nbr+=a[i_north*n + j_west];
	nbr+=a[i_north*n + j_east];
	nbr+=a[i_south*n + j_west];
	nbr+=a[i_south*n + j_east];
	return nbr;
}

/*  go through all rows in a and check for 1-entries
 * 	save true or false in row_has_ones which are 
 *	a lookuptable used later to check if one can 
 *  skip processing a line
 *                                               */
void check_ones(char *a, int n,bool* row_has_ones){
	cilk_for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(a[i*n+j]==1){
				row_has_ones[i]=true;
				break;
			}	
		}
	}
}

//Life function
void life(int *old_a, unsigned int n, unsigned int iter){
	bool prev, current, next;
	int lcnt=0;
	int nbr_arr[8];
	char * temp;
	// make a temporary a_temp to read
	// current cells from to avoid race conditions
	char *a_temp;
	a_temp = (char*)malloc(sizeof(char)*(n*n));
	char *a;
	a = (char *)malloc(sizeof(char)*(n*n));
	bool* row_has_ones;
	row_has_ones = (bool *)malloc(sizeof(bool)*(n));
	
	// copy over to temp buffer a_temp
	for(unsigned int i=0;i<n*n;i++){
		a_temp[i]=old_a[i];	
		a[i]=old_a[i];
	}
	// check all rows for 1-entries 
	check_ones(a,n,row_has_ones);	
	for(int iters=0;iters<iter;iters++){
			// swap the pointers to always read
			// from the updated a. 
			temp=a;
			a=a_temp;
			a_temp=temp;
			// iterate through rows
			cilk_for(int i=0;i<n;i++){	
				int nbr;
				bool any_ones=false;
				if(i==0 || i==n-1 || row_has_ones[i] || row_has_ones[i-1] || row_has_ones[i+1]   ){
					// iterate through columns only if there's any ones in the current, previous or next row	
					for(int j=0;j<n;j++){
						nbr=count_nbr(a_temp,n,i,j);		
						if(((a_temp[i*n+j]==1) && (nbr==2)) || (nbr==3)){
							a[i*n+j]=1;
							any_ones=true;
						}else{
							a[i*n+j]=0;
					 	}
						if(a[i*n+j]==1)
						row_has_ones[i]=any_ones; 
					}
				}
		}
		#if DEBUG == 1
		if(( (iters+1) % (iter/10))==0 && iters !=0){
			for(unsigned int l=0;l<n*n;l++){
				old_a[l]=a[l];
			}	
			livecount[lcnt++]= countlive(old_a,n);
		}
		#endif
	}
}
