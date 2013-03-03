#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "collision_detection.h"
#include "functions.h"

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

void initTempPolys(struct polygon link1Poly, struct polygon link2Poly, struct polygon link3Poly,
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
void compute3LinkFreeWorkspace(unsigned int sample_list_length,double **sample_list,unsigned int* free_workspace_size,double **free_workspace,
								struct point link1BaseRef,struct point link2BaseRef,struct point link3BaseRef,
								struct polygon link1Poly, struct polygon link2Poly, struct polygon link3Poly,
								struct polygon *obstacleList,  int numberOfObstacles){
//	print_polygon_data(obstacleList[0],obstacleList[1],link1Poly,link2Poly,link3Poly,link1BaseRef,link2BaseRef,link3BaseRef);
	int i,j,collision;
	int k=0;
	struct point displacedLinkEnd1, displacedLinkEnd2, displacedLinkEnd3;
	struct polygon displacedLink1, displacedLink2, displacedLink3;
	initTempPolys(link1Poly,link2Poly,link2Poly, &displacedLink1 , &displacedLink2 , &displacedLink3  );
	for(i=0;i<sample_list_length;i++){
		displaceLinkPoly(sample_list[i][0], &displacedLink1, &displacedLinkEnd1, link1BaseRef, link1Poly, link2BaseRef);	
		displaceLinkPoly(sample_list[i][0]+sample_list[i][1], &displacedLink2, &displacedLinkEnd2, displacedLinkEnd1, link2Poly, link3BaseRef);	
		displaceLinkPoly(sample_list[i][0]+sample_list[i][1]+sample_list[i][2], &displacedLink3, &displacedLinkEnd3, displacedLinkEnd2, 
						link3Poly, link3BaseRef);	
//		print_polygon_data(obstacleList[0],obstacleList[1],displacedLink1,displacedLink2,displacedLink3,displacedLinkEnd1,displacedLinkEnd2, 
//					displacedLinkEnd3);
		collision=FALSE;	
		for(j=0; j < numberOfObstacles;j++){
			if(check_collision(displacedLink1,obstacleList[j])){
				print_polygon(displacedLink1);
				return;
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
		if(collision == FALSE){
			for(j = 0; j<3 ; j++){
				free_workspace[k][j]=sample_list[i][j];
				k++;
			} 
		}
	}
	*free_workspace_size=k;
}

void print_free_workspace(unsigned int free_workspace_size,double **free_workspace){
	int i;
	puts("------Free workspace: -------------\n");
	for(i=0;i<free_workspace_size;i++){
		printf("%1.3f, %1.3f, %1.3f \n",free_workspace[i][0], free_workspace[i][1],free_workspace[i][2]);
	}

}

int main(){
	unsigned int free_workspace_size;
	struct polygon obstacle1, obstacle2;
	struct polygon link1, link2,link3;
	struct point base1, base2, base3;
	generate_obstacles_and_links(&obstacle1, &obstacle2, &link1, &link2, &link3 , &base1 , &base2 , &base3);
	int number_of_obstacles=2;
	struct polygon *obstacle_list;
	obstacle_list=(struct polygon*)malloc(number_of_obstacles*sizeof(struct polygon));
	obstacle_list[0]=obstacle1;
	obstacle_list[1]=obstacle2;
	// ------------ sample list ------------------//
	int n,i,j;
	double ** sampleList;
	double ** free_workspace;
	n = NUM_SAMPLES*NUM_SAMPLES*NUM_SAMPLES;
	sampleList = (double **)malloc(sizeof(double*)* n);
	free_workspace = (double **)malloc(sizeof(double*)* n);
	for (i=0;i<n;i++){
		sampleList[i] = (double*)malloc(sizeof(double) * 3);
		free_workspace[i] = (double*)malloc(sizeof(double) * 3);
		for(j=0;j<3;j++){
			sampleList[i][j] = 0;
			free_workspace[i][j] = -1;
		}
	}
	createSampeList(sampleList);
	compute3LinkFreeWorkspace(n,sampleList,&free_workspace_size,free_workspace,base1,base2,base3,
							  link1,link2,link3,obstacle_list,number_of_obstacles);	
//	print_free_workspace(free_workspace_size, free_workspace);
//	printf("free ws space %d\n ", free_workspace_size);
	return 0;
}
