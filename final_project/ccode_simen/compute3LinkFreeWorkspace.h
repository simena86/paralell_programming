#ifndef _COMPUTE_FREE_WS_
#define _COMPUTE_FREE_WS_

gnuplot_ctrl *h;

/* Computes the free workspace based on samples from "sample_list", returns "free_workspace"
 * which are all set of angles (on a 3-Torus) which dosnt cause the manipulator to crash into
 * obstacles 																				*/
void compute3LinkFreeWorkspace(unsigned int sample_list_length,double **sample_list,unsigned int *free_workspace_size,double **free_workspace,
								struct point link1BaseRef,struct point link2BaseRef,struct point link3BaseRef,
								struct polygon link1Poly, struct polygon link2Poly, struct polygon link3Poly,
								struct polygon *obstacleList,  int numberOfObstacles);

void printFreeWorkSpace(unsigned int free_workspace_size,double **free_workspace);



#endif
