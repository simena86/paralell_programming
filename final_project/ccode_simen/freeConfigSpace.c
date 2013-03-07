#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "collision_detection.h"
#include "functions.h"
#include "gnuplot_i.h"
#include "freeConfigSpace.h"
#include "generate_polygons.h"
#include "visualization.h"

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
	static double xtemp,ytemp;
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

/* Computes the free configspace based on samples from "sample_list", returns "free_configspace"
 * which are all set of angles (on a 3-Torus) which dosnt cause the manipulator to crash into
 * obstacles 																				*/
void compute3LinkFreeConfigSpace(unsigned int sample_list_length,double **sample_list,unsigned int* free_cs_size,double **free_configSpace,
								struct point link1BaseRef,struct point link2BaseRef,struct point link3BaseRef,
								struct polygon link1Poly, struct polygon link2Poly, struct polygon link3Poly,
								struct polygon *obstacleList,  int numberOfObstacles){
	static struct polygon* polygons;
	polygons=(struct polygon*)malloc(5*sizeof(struct polygon));
	int i,j,collision;
	int k=0;
	static struct point displacedLinkEnd1, displacedLinkEnd2, displacedLinkEnd3;
	static struct polygon displacedLink1, displacedLink2, displacedLink3;
	initTempPolys(link1Poly,link2Poly,link2Poly, &displacedLink1 , &displacedLink2 , &displacedLink3  );
	for(i=0;i<sample_list_length;i++){
		displaceLinkPoly(sample_list[i][0], &displacedLink1, &displacedLinkEnd1, link1BaseRef, link1Poly, link2BaseRef);	
		displaceLinkPoly(sample_list[i][0]+sample_list[i][1], &displacedLink2, &displacedLinkEnd2, displacedLinkEnd1, link2Poly, link3BaseRef);	
		displaceLinkPoly(sample_list[i][0]+sample_list[i][1]+sample_list[i][2], &displacedLink3, &displacedLinkEnd3, displacedLinkEnd2, 
						link3Poly, link3BaseRef);	
		polygons[0] = displacedLink1;
		polygons[1] = displacedLink2;
		polygons[2] = displacedLink3;
		polygons[3] = obstacleList[0];
		polygons[4] = obstacleList[1];
		collision=FALSE;
		draw_polys_configSpace(k,free_configSpace,5,polygons,0);
		for(j=0; j < numberOfObstacles;j++){
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
		if(collision == FALSE){
			k++;
			for(j = 0; j<3 ; j++){
				free_configSpace[k][j]=sample_list[i][j];
			} 
		}
	//	draw_configSpace(k,free_configSpace,20);
	}
	*free_cs_size=k;
	free(polygons);
	free(displacedLink1.x_list);
	free(displacedLink2.x_list);
	free(displacedLink3.x_list);
	free(displacedLink1.y_list);
	free(displacedLink2.y_list);
	free(displacedLink3.y_list);
}

void print_free_configSpace(unsigned int free_cs_size,double **free_configSpace){
	int i;
	puts("------Free ConfigSpace: -------------\n");
	for(i=0;i<free_cs_size;i++){
		printf("%1.3f, %1.3f, %1.3f \n",free_configSpace[i][0], free_configSpace[i][1],free_configSpace[i][2]);
	}
}

int main(){
	h=0;	
	unsigned int free_cs_size=0;
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
	double ** free_configSpace;
	n = NUM_SAMPLES*NUM_SAMPLES*NUM_SAMPLES;
	sampleList = (double **)malloc(sizeof(double*)* n);
	free_configSpace = (double **)malloc(sizeof(double*)* n);
	for (i=0;i<n;i++){
		sampleList[i] = (double*)malloc(sizeof(double) * 3);
		free_configSpace[i] = (double*)malloc(sizeof(double) * 3);
		for(j=0;j<3;j++){
			sampleList[i][j] = 0;
			free_configSpace[i][j] = -1;
		}
	}
	createSampeList(sampleList);
	compute3LinkFreeConfigSpace(n,sampleList,&free_cs_size,free_configSpace,base1,base2,base3,
							  link1,link2,link3,obstacle_list,number_of_obstacles);	
//	print_free_configSpace(free_cs_size, free_configSpace);
//	printf("free ws space %d\n ", free_cs_size);
	if(h!=NULL)
		gnuplot_close(h);
	return 0;
}
