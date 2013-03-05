#ifndef _COMPUTE_FREE_WS_
#define _COMPUTE_FREE_WS_

#include "my_type_defs.h"

/* Computes the free workspace based on samples from "sample_list", returns "freeconfigSpace"
 * which are all set of angles (on a 3-Torus) which dosnt cause the manipulator to crash into
 * obstacles 																				*/
void compute3LinkFreeConfigSpace(unsigned int sample_list_length,double **sample_list,unsigned int *free_cs_size,double **freeconfigSpacer,
								struct point link1BaseRef,struct point link2BaseRef,struct point link3BaseRef,
								struct polygon link1Poly, struct polygon link2Poly, struct polygon link3Poly,
								struct polygon *obstacleList,  int numberOfObstacles);

// prints text of points in the free configuration space
void printFreeWorkSpace(unsigned int free_cs_size,double **freeconfigSpace);



#endif
