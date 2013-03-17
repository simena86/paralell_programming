
#ifndef _VISUALIZATION_
#define _VISUALIZATION_

#include "my_type_defs.h"
#include "gnuplot_i.h"

/*
 *  global variable for handling gnuplot 
 */
gnuplot_ctrl *h;

/*
 * function uses gnuplot_ctrl handler h to plot to window or to animate a gif.
 * the main function should initialize h to zero and use gnuplot_close(h) before returning	
 */ 
void draw_polygons(struct polygon* polygons, int number_of_polygons,int delay);

/*
 *	make a 3d plot of the free configSpace
 */
void draw_configSpace(unsigned int cs_size,double **configSpace,int delay);


void draw_polys_configSpace(unsigned int cs_size, double **configSpace,int number_of_polygons, struct polygon *polygons,unsigned int delay);

void draw_adjTable( unsigned int cs_size,double **cs,unsigned int* atArr,unsigned int **at,double connectRad,long int delay);
#endif
