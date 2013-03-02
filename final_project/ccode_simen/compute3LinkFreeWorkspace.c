#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void rotateVector(double linkAngle, double* x, double* y){
	double x_temp=*x;
	double y_temp=*y;
	*x=x*cos(linkAngle) - y*sin(linkAngle) 
	*y=x_temp*sin(linkAngle) + y_temp*cos(linkAngle);
}

void displaceLinkPoly(double linkAngle,struct polygon* displacedLink, struct point* displacedLinkEnd, struct point linkBase,
					struct polygon linkReference, struct linkEndPointReference ){
	int i;
	double xtemp,ytemp;
	// translate and rotate all vertices of polygon	
	for(i=0;i<linkReferece.numberOfVertices;i++){
		xtemp=linkReference.x[i];
		ytemp=linkReference.y[i];
		rotateVector(linkAngle,&xtemp,&ytemp );
		displacedLink->x[i]=xtemp + linkBase.x;
		displacedLink->y[i]=ytemp + linkBase.y;
	}
	// rotate and displace linkEnd
	tempx=linkEndPointReference.x;
	tempy=linkEndPointReference.y;
	rotateVector(


}

void compute3LinkFreeWorkspace(unsigned int sample_list_length,double **sample_list,double **free_workspace,
								double link1BaseRef,double link2BaseRef,double link2BaseRef,
								struct polygon link1Poly, struct polygon link2Poly, struct polygon link3Poly){
}

		
