#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "collision_detection.h"

/* Rotates a vector counter clockwise by angle "linkAngle" */
void rotateVector(double linkAngle, double* x, double* y){
	double x_temp=*x;
	double y_temp=*y;
	*x=x_temp*cos(linkAngle) - y_temp*sin(linkAngle); 
	*y=x_temp*sin(linkAngle) + y_temp*cos(linkAngle);
}


/* Displace a polygon by angle "linkAngel" and translation by "linkBase". 
 * Returns
 *  -displaced polygon
 *  -displaced linkEnd where other links use as a linkBase              */
void displaceLinkPoly(double linkAngle,struct polygon* displacedLink, struct point* displacedLinkEnd, struct point linkBase,
					struct polygon linkReference, struct point linkEndPointReference ){
	int i;
	double xtemp,ytemp;
	// translate and rotate all vertices of polygon	
	for(i=0;i<linkReference.numberOfVertices;i++){
		xtemp=linkReference.x_list[i];
		ytemp=linkReference.y_list[i];
		rotateVector(linkAngle,&xtemp,&ytemp );
		displacedLink->x_list[i]=xtemp + linkBase.x;
		displacedLink->y_list[i]=ytemp + linkBase.y;
	}
	// rotate and displace linkEnd
	xtemp=linkEndPointReference.x;
	ytemp=linkEndPointReference.y;
	rotateVector(linkAngle,&xtemp,&ytemp);
	displacedLinkEnd->x=xtemp + linkBase.x;
	displacedLinkEnd->y=ytemp + linkBase.y;
}

initTempPolys(struct polygon link1Poly, struct polygon link2Poly, struct polygon link3Poly,
			struct polygon* displacedLink1 , struct polygon* displacedLink2, struct polygon* displacedLink3  ){
	displacedLink1->numberOfVertices=link1Poly.numberOfVertices;
	displacedLink1->x_list=(double*)malloc(link1Poly.numberOfVertices*sizeof(double));
	displacedLink1->y_list=(double*)malloc(link1Poly.numberOfVertices*sizeof(double));
	displacedLink2->numberOfVertices=link1Poly.numberOfVertices;
	displacedLink2->x_list=(double*)malloc(link1Poly.numberOfVertices*sizeof(double));
	displacedLink2->y_list=(double*)malloc(link1Poly.numberOfVertices*sizeof(double));
	displacedLink3->numberOfVertices=link1Poly.numberOfVertices;
	displacedLink3->x_list=(double*)malloc(link1Poly.numberOfVertices*sizeof(double));
	displacedLink3->y_list=(double*)malloc(link1Poly.numberOfVertices*sizeof(double));
}



/* Computes the free workspace based on samples from "sample_list", returns "free_workspace"
 * which are all set of angles (on a 3-Torus) which dosnt cause the manipulator to crash into
 * obstacles 																				*/
void compute3LinkFreeWorkspace(unsigned int sample_list_length,double **sample_list,double **free_workspace,
								struct point link1BaseRef,struct point link2BaseRef,struct point link3BaseRef,
								struct polygon link1Poly, struct polygon link2Poly, struct polygon link3Poly,
								struct polygon *obstacleList,  int numberOfObstacles){
	int i,j,collision;
	int k=0;
	struct point displacedLinkEnd1, displacedLinkEnd2, displacedLinkEnd3;
	struct polygon displacedLink1, displacedLink2, displacedLink3;
	initTempPolys(link1Poly,link2Poly,link2Poly, &displacedLink1 , &displacedLink2 , &displacedLink3  );;
	for(i=0;i<sample_list_length;i++){
		displaceLinkPoly(sample_list[i][0], &displacedLink1, &displacedLinkEnd1, link1BaseRef, link1Poly, link1BaseRef);	
		displaceLinkPoly(sample_list[i][1], &displacedLink2, &displacedLinkEnd2, displacedLinkEnd1, link2Poly, link2BaseRef);	
		displaceLinkPoly(sample_list[i][2], &displacedLink3, &displacedLinkEnd3, displacedLinkEnd2, link3Poly, link3BaseRef);	
		for(j=0; j = numberOfObstacles;j++){
			if(check_collision(displacedLink1,obstacleList[j])){
				collision=TRUE;
				break;
			}else if(check_collision(displacedLink2,obstacleList[j])){
				collision=TRUE;
				break;
			}else if(check_collision(displacedLink3,obstacleList[j])){
				collision=TRUE;
				break;
			}
		}
		if(collision = = FALSE){
			for(j = 0; j<3 ; j++){
				free_workspace[k][j]=sample_list[i][j];
				k++;
			} 
		}
	}
}




int main(){
	return 0;


}
