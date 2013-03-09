#include "headers.h"

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
	int myrank, nprocs;
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
	static struct polygon* polygons;
	polygons=(struct polygon*)malloc(5*sizeof(struct polygon));
	int i;
	char j,collision;
	int k=0;
	static struct point displacedLinkEnd1, displacedLinkEnd2, displacedLinkEnd3;
	static struct polygon displacedLink1, displacedLink2, displacedLink3;
	// for timing 	
	struct timeval start, end;
	gettimeofday(&start,0);
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
		for(j=0; j < numberOfObstacles;j++){
			if(check_collision(displacedLink3,obstacleList[j])){
				collision=TRUE;
				break;
			}else if(check_collision(displacedLink2,obstacleList[j])){
				collision=TRUE;
				break;
			}else if(check_collision(displacedLink1,obstacleList[j])){
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
	}
	gettimeofday(&end, 0);
	double dif;
	dif=(end.tv_sec - start.tv_sec)*1000 + (end.tv_usec- start.tv_usec) / 1000;
	dif=dif;
	printf("timing of config sampling in milliseconds %2.2f \n",dif);
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



