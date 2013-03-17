#include "computeAdjTableForFreeCSpacePoints.h"

double min(double a, double b){
	if(a < b){
		return a;
	}else{
		return b;
	}
}

int computeAdjTableForFreeCSpacePoints(struct Status *s, double maxAdjRadius){

	// Return number of points in adjTable
	//printf("compute adjTable %d\n", free_cs_size);
	//printf("max r = %f\n",maxAdjRadius);
	int i,j,k,sizeTempAdjTable;
	int numPoints = 0;
	int offset=s->offsets[s->myrank];
	double xi,yi,zi,xj,yj,zj,distx,disty,distz,distTot;
	sizeTempAdjTable = 15;
	int tempTable [sizeTempAdjTable];

	
	for(i=0;i < s->cs_size_partition ;i++){
		
		k=0;
		for(j=0;j<sizeTempAdjTable;j++){
			tempTable[j] = -1;
		}
		
		xi = s->cs_partition[i][0];
		yi = s->cs_partition[i][1];
		zi = s->cs_partition[i][2];

		for(j=0;j<s->cs_size_total;j++){

			//printf("i,j %d %d \n",i,j);	
			xj = s->cs_total[j][0];
			yj = s->cs_total[j][1];
			zj = s->cs_total[j][2];
			
			// distance in x, y and z direction
			distx = fabs(xj - xi);
			disty = fabs(yj - yi);
			distz = fabs(zj - zi);

			if(distx > PI){
				distx = min(fabs(PI - xj),fabs(-PI-xj))   +   min(fabs(PI - xi),fabs(-PI-xi)); 
			}
			if(disty > PI){
				disty = min(fabs(PI - yj),fabs(-PI-yj))   +   min(fabs(PI - yi),fabs(-PI-yi)); 
			}
			if(distz > PI){
				distz = min(fabs(PI - zj),fabs(-PI-zj))   +   min(fabs(PI - zi),fabs(-PI-zi)); 
			}
		
			// Calculate total distance
			distTot = sqrt((distx*distx) + (disty*disty) + (distz*distz));

			if (distTot < maxAdjRadius && (i + offset)!=j){
				// Add to temp adjTable
				tempTable[k] = j;
				k++;
				numPoints++;
			}
		}

		// Add temp to adjTable
		s->adjTable[i+offset] = (unsigned int*)malloc(sizeof(unsigned int) * k);
		for(j=0;j<k;j++){
			s->adjTable[i + offset][j] = tempTable[j];
		}
		
		//Store the number of neighbors for the current vertex 
		s->adjTableElementSize[i + offset] = k;
	}
	return numPoints;
}

void print_adjTable_total(struct Status s){
	int i,j;
	printf("------Free ConfigSpace: proc %d -------------\n", s.myrank);
	for(i=0 ;i< s.cs_size_total;i++){
		printf("\n%d: ", i);	
		for(j=0; j<s.adjTableElementSize[i];j++){
			printf("%d,",s.adjTable[i][j]);
		}
	}
	printf("\n------End Free ConfigSpace: proc %d -------------\n", s.myrank);


}


void print_adjTable(struct Status s){
	int i,j;
	printf("------Free ConfigSpace: proc %d -------------\n", s.myrank);
	for(i=s.offsets[s.myrank] ;i<s.offsets[s.myrank] + s.cs_size_partition ;i++){
		printf("\n%d: ", i);	
		for(j=0; j<s.adjTableElementSize[i];j++){
			printf("%d,",s.adjTable[i][j]);
		}
	}
	printf("\n------End Free ConfigSpace: proc %d -------------\n", s.myrank);
}
