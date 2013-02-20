/*
Homework 5 : The Game of Life.
Team member 1 : Sverre Kvamme 
Team member 2 : Simen Andresen
*/

#include "header.h"
#include <string.h>
using namespace std;

//Generate the life matrix any way you want. We would highly recommend that you print the generated
//matrix into a file, so that you can share it with other teams for checking correctness.
void genlife(int *a, unsigned int n){
			
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
	switch(n){
		case 10:
			filename="./input/input-0";
		case 20:
			filename="./input/input-1.2";
		case 100:
			filename="./input/input-1.3";
		case 200:
			filename="./input/input-1.4";
	}
	for(int i=0; i<n;i++){
		for(int j=0;j<n;j++){
				
		}
	}
}

//Life function
void life(int *a, unsigned int n, unsigned int iter)
{
	// You need to store the total number of livecounts for every 1/0th of the total iterations into the livecount array. 
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


