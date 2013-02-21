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
using namespace std;

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
	printf("%d , %d \n",k,p);
	
	a[k*n + p] 	= 1; 		
	a[k*n + p+1] 	= 1; 		
	a[k*n + p+2] 	= 1; 		

	a[(k+1)*n + p] 	 = 1; 		
	a[(k+1)*n + p+1] = 0; 		
	a[(k+1)*n + p+2] = 0; 		

	a[(k+2)*n + p]	 = 0; 		
	a[(k+2)*n + p+1] = 1;
	a[(k+2)*n + p+2] = 0;
	
	for(i=0;i<n;i++){
		for (j=0;j<n;j++){
			printf("%d ",a[i*n + j]);
		}
		printf("\n");
	}
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

	cout << "Reading from file : "<< filename << endl;
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

//Life function
void life(int *a, unsigned int n, unsigned int iter)
{
	// You need to store the total number of livecounts for every 1/10th of the total iterations into the livecount array. 
	// For example, if there are 50 iterations in your code, you need to store the livecount for iteration number 5 10 15 
	// 20 ... 50 starting from 1. The countlive function is defined in life.cpp, which you can use. Remember that you can
	// do the debugging if the number of iterations is a multiple of 10.
	// Furthermore, you will need to wrap your counting code inside the wrapper #if DEBUG == 1 .. #endif to remove
	// it during performance evaluation.
	// For example, your code in this function could look like - 
	//
	//
	//	for(each iteration)
	//      {
	//			
	//		Calculate_next_life();
	//		
	//		#if DEBUG == 1
	//		  if_current_iteration == debug_iteration
	//		  total_lives = countlive();
	//		  Store_into_livecount(total_lives);
	//		#ENDIF
	//		
	//	}
}


