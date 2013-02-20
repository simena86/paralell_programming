#include "header.h"

int main(){
	int *a;
	int n=110;
	a = (int *)malloc(sizeof(int)*(n*n));
	readlife(a,n);
	if(a[0]==-1){
		return -1; // error
	}
	for(int i=0;i<n;i++){
		for (int j=0;j<n;j++)
			printf("%i",a[i*n+n]);
	}
}
