#include "computeNearestPoint.h"

/*
double min(double a, double b){
	if(a < b){
		return a;
	}else{
		return b;
	}
}
*/
int computeNearestPoint(struct Status *s, double alpha, double beta, double gamma){

	int j,k,nearestPoint;
	int numPoints = 0;
	double xj,yj,zj,distx,disty,distz,distTot,minDist;
	minDist = 9999999;
	

	for(j=0;j<s->cs_size_total;j++){

			//printf("i,j %d %d \n",i,j);	
			xj = s->cs_total[j][0];
			yj = s->cs_total[j][1];
			zj = s->cs_total[j][2];
			
			// distance in x, y and z direction
			distx = fabs(xj - alpha);
			disty = fabs(yj - beta);
			distz = fabs(zj - gamma);

			if(distx > PI){
				distx = min(fabs(PI - xj),fabs(-PI-xj))   +   min(fabs(PI - alpha),fabs(-PI-alpha)); 
			}
			if(disty > PI){
				disty = min(fabs(PI - yj),fabs(-PI-yj))   +   min(fabs(PI - beta),fabs(-PI-beta)); 
			}
			if(distz > PI){
				distz = min(fabs(PI - zj),fabs(-PI-zj))   +   min(fabs(PI - gamma),fabs(-PI-gamma)); 
			}
		
			// Calculate total distance
			distTot = sqrt((distx*distx) + (disty*disty) + (distz*distz));

			if (distTot < minDist){
				// Add to temp adjTable
				minDist = distTot;
				nearestPoint = j;
				k++;
			}
	}
	return nearestPoint;
}

