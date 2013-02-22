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

void print_matrix(int * a, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("%d ",a[i*n+j]);
		}
		cout<<endl;
	}

	cout<<endl;
	cout<<endl;

}



int mod (int a, int b){
   if(b < 0) //you can check for b == 0 separately and do what you want
     return mod(-a, -b);   
   int ret = a % b;
   if(ret < 0)
     ret+=b;
   return ret;
}

//Life function
void life(int *a, unsigned int n, unsigned int iter){
	int nbr;
	int lcnt=0;
	int *a_temp;
	int nbr_arr[8];
	a_temp = (int *)malloc(sizeof(int)*(n*n));
	for(int iters=0;iters<iter;iters++){
		for(int i=0;i<n*n;i++){
			a_temp[i]=a[i];	
		}		
		
		for(int i=0;i<n;i++){	
			for(int j=0;j<n;j++){
				nbr=0;
				nbr+=a_temp[n*i+mod((j-1) , n)];  				//west
				nbr+=a_temp[n*i+mod((j+1) , n)];  				//east
				nbr+=a_temp[n*mod((i+1) , n) +j ]; 			//south
				nbr+=a_temp[n*mod((i-1) , n) +j ]; 			//north
				nbr+=a_temp[n*mod((i+1) , n) +mod((j+1) , n)];	//south east
				nbr+=a_temp[n*mod((i+1) , n) +mod((j-1) , n)];	//south west 
				nbr+=a_temp[n*mod((i-1) , n) +mod((j+1) , n)];	//north east
				nbr+=a_temp[n*mod((i-1) , n) +mod((j-1) , n)];	//north west
				if(((a_temp[i*n+j]==1) && (nbr==2)) || (nbr==3)){
					a[i*n+j]=1;
				}else{
					a[i*n+j]=0;
			 	}
			}
		}
		#if DEBUG == 1
			if(( (iters+1) % (iter/10))==0 && iters !=0){
				livecount[lcnt++]= countlive(a,n);
			}
		#endif
	}
}
