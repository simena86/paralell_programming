#include "functions.h"
#include <stdio.h>

int coars = 4;

int rec_cilkified(int *a,int *b,unsigned int n){
	int sum1=0;
	int sum2=0;
	if(n > coars){
		sum1 = cilk_spawn rec_cilkified(a,b,n/2);
		sum2 = rec_cilkified(a+n/2, b+n/2, n-n/2);
		cilk_sync;
		return (sum1 + sum2);
	}
	for(int i=0;i<n;i++){
		sum1+=a[i]*b[i];	
	}
	return sum1;
}

int loop_cilkified(int *a,int *b,unsigned int n){
	int sum[n/coars];
	for(int i=0;i<n/coars;i++){
		sum[i]=0;
	}
	cilk_for(int i=0;i<n/coars;i++){
		for(int j=0;j<coars;j++){
			sum[i]+=a[i*coars + j]*b[i*coars +j];
		}
	}
	int rest_sum=0;
	int fsum=0;
	printf("modulo %d\n",n-(n%coars));
	for(int k=n-(n % coars); k<n;k++){
		rest_sum+=a[k]*b[k];
	}
	for(int i=0;i<n/coars;i++){
		fsum+=sum[i];
	}
	printf("total = %d, fsum =%d, rest_sum=%d\n",fsum+rest_sum, fsum,rest_sum);
	return fsum + rest_sum;
	
}

int hyperobject_cilkified(int *a,int *b,unsigned int n){
}

