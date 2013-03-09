#include "computeAdjTableForFreeCSpacePoints.h"

double min(double a, double b){
	if(a < b){
		return a;
	}else{
		return b;
	}
}

void computeAdjTableForFreeCSpacePoints(unsigned int free_cs_size,double **free_configSpace, int ** adjTable, int * adjTableElementSize, double maxAdjRadius){
	//printf("compute adjTable %d\n", free_cs_size);
	//printf("max r = %f\n",maxAdjRadius);
	int i,j,k,sizeTempAdjTable;
	double xi,yi,zi,xj,yj,zj,distx,disty,distz,distTot;
	sizeTempAdjTable = 10;
	int tempTable [sizeTempAdjTable];

	for(i=0;i<free_cs_size;i++){
		
		k=0;
		for(j=0;j<sizeTempAdjTable;j++){
			tempTable[j] = -1;
		}

		xi = free_configSpace[i][0];
		yi = free_configSpace[i][1];
		zi = free_configSpace[i][2];

		for(j=0;j<free_cs_size;j++){
		
			xj = free_configSpace[j][0];
			yj = free_configSpace[j][1];
			zj = free_configSpace[j][2];
			
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

			if (distTot < maxAdjRadius && i!=j){
				// Add to temp adjTable
				tempTable[k] = j;
				k++;
			}
		}

		// Add temp to adjTable
		adjTable[i] = (int*)malloc(sizeof(int) * k);
		for(j=0;j<k;j++){
			adjTable[i][j] = tempTable[j];
		}
		
		//Store the number of neighbors for the current vertex 
		adjTableElementSize[i] = k;
	}
}

void print_adjTable(unsigned int free_cs_size, int **adjTable, int * adjTableElementSize){
	int i,j;
	puts("------Free ConfigSpace: -------------\n");
	for(i=0;i<free_cs_size;i++){
		printf("\n%d: ", i);	
		for(j=0; j<adjTableElementSize[i];j++){
			printf("%d,",adjTable[i][j]);
		}
	}
}
