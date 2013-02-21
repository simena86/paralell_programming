#include "life.h"

int main(int argc, char **argv){
	int *a;
	int n;
	n = (unsigned int)atoi(argv[1]);
	a = (int *)malloc(sizeof(int)*(n*n));
	readlife(a,n);
	if(a[0]==-1){
		return -1; // error
	}
	for(int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			printf("%i ",a[i*n+j]);
		}
		printf("\n");
	}
}
