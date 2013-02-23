/*
Homework 4 : Cilkified Inner Products.
Team member 1 : Sverre Kvamme
Team member 2 : Simen Andresen
*/

#include<cilk.h>
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<numeric>

#include "functions.h"
#include <cilkview.h>
#include <cilk.h>
// Function declarations
void fill_arrays(int *a, int *b, int n);

using namespace std;

cilk::cilkview cv;
// String to display results
char result[][15] = {"matched","did not match"};

int cilk_main(int argc, char **argv)
{

	unsigned int n;

	// Size calculation
	n = (unsigned int)atoi(argv[1]);
	
	// Array allocation	
	int *a,*b;
	a = (int *)malloc(sizeof(int)*n);
	b = (int *)malloc(sizeof(int)*n);

	int loop_result, rec_result, hyper_result, ref_result; 
	
	// Initialize arrays
	fill_arrays(a,b,n);
	
	// Compute inner product for each method
	int coarsnesses[7]= {20,40,60,80,100,120,140};
	int coars;
for(int i=0;i<7;i++){
	coars=coarsnesses[i];
	// recursive
	char buffer [50];
	int ns;
	ns=sprintf(buffer,"recursive, coars= %d",coars);
	cv.start();	
	rec_result = rec_cilkified(a,b,n,coars);
	cv.stop();
	cv.dump(buffer);
	// Loop
	ns=sprintf(buffer,"Loop, coars= %d",coars);
	loop_result = loop_cilkified(a,b,n,coars);
	cv.stop();
	cv.dump(buffer);
	// Hyperobject
	ns=sprintf(buffer,"Hyperobject, coars= %d",coars);
	cv.start();	
	hyper_result = hyperobject_cilkified(a,b,n,coars);
	
	cv.stop();
	cv.dump(buffer);
}
	// Compute inner product using library function	
	ref_result = std::inner_product(a,a+n,b,0);

	printf("Result from standard library function : %d\n",ref_result);
	printf("Recursive result %s\n",result[rec_result != ref_result]);
	printf("Loop result %s\n",result[loop_result != ref_result]);
	printf("Hyperobject result %s\n",result[hyper_result != ref_result]);


	return 0;

}

void fill_arrays(int *a, int *b, int n)
{
	int i;
	for(i = 0 ; i < n; i++)
	{
		a[i] = 1;	
		b[i] = 3;
	}
}

