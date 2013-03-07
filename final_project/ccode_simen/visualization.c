#include <stdio.h>
#include "visualization.h"
asdfasdf

void mysleep(int milisecond){
	int i=0;
	float a =0;
	for(i=0;i<milisecond*50000;i++){
		a=a+4.5;	
	}
}

void draw_polygons(struct polygon* polygons, int number_of_polygons,int delay){
	if(h==0){
		h = gnuplot_init();
		gnuplot_cmd(h, "clear");
		gnuplot_cmd(h,"reset");
		//gnuplot_cmd(h,"set terminal gif animate ");
		//gnuplot_cmd(h,"set output \"animate.gif\"");
		gnuplot_cmd(h, "set isosample 40" );
		gnuplot_cmd(h, "set xrange [-4:4]");
		gnuplot_cmd(h, "set yrange [-4:4]");
		gnuplot_cmd(h, "set style arrow 1 nohead")	;
	}	
	int i,j;
	gnuplot_cmd(h,"unset arrow");
	for(j=0;j<number_of_polygons;j++){
		for(i=0;i<polygons[j].numberOfVertices-1;i++){	
			gnuplot_resetplot(h);
			gnuplot_cmd(h, "set arrow from %f,%f to %f,%f as 1",polygons[j].x_list[i], polygons[j].y_list[i],polygons[j].x_list[i+1], 
					polygons[j].y_list[i+1]);
		}
	}
	gnuplot_cmd(h, "plot NaN notitle");
	mysleep(delay);
}

void draw_configSpace(unsigned int cs_size,double **configSpace, int delay){
	int i,j;
	if(h==0){
		h = gnuplot_init();
		gnuplot_cmd(h, "clear");
		gnuplot_cmd(h,"reset");
		//gnuplot_cmd(h,"set terminal gif animate ");
		//gnuplot_cmd(h,"set output \"animate.gif\"");
		gnuplot_cmd(h, "set xrange [-4:4]");
		gnuplot_cmd(h, "set yrange [-4:4]");
		gnuplot_cmd(h, "set zrange [-4:4]");
	}
	gnuplot_cmd(h,"splot \"-\" using 1:2:3 with points pointtype 26 ps 0.3 lt palette");
	for(i=0;i<cs_size;i++){
		gnuplot_cmd(h,"%f %f %f", configSpace[i][0], configSpace[i][1], configSpace[i][2]);	
	}
	gnuplot_cmd(h,"e");
	mysleep(delay);
}

void draw_polys_configSpace(unsigned int cs_size, double **configSpace,int number_of_polygons, struct polygon *polygons,unsigned int delay){
	int i,j,k;
	if(h==0){
		h = gnuplot_init();
		gnuplot_cmd(h, "clear");
		gnuplot_cmd(h,"reset");
		gnuplot_cmd(h,"set terminal gif small animate delay 1 optimize");
		gnuplot_cmd(h,"set output \"animate.gif\"");
//		gnuplot_cmd(h,"set terminal postscript color");
//		gnuplot_cmd(h,"set output \"plot1.ps\"");
		gnuplot_cmd(h, "set isosample 40" );
		gnuplot_cmd(h, "set xrange [-4:4]");
		gnuplot_cmd(h, "set yrange [-4:4]");
	}	
	gnuplot_cmd(h,"set multiplot layout 1, 2;");
	// plot polygon
	gnuplot_cmd(h, "set style arrow 1 nohead")	;
	for(j=0;j<number_of_polygons;j++){
		for(i=0;i<polygons[j].numberOfVertices-1;i++){	
			gnuplot_cmd(h, "set arrow from %f,%f to %f,%f as 1",polygons[j].x_list[i], polygons[j].y_list[i],polygons[j].x_list[i+1], 
					polygons[j].y_list[i+1]);
		}
	}
	gnuplot_cmd(h,"set size square");
	gnuplot_cmd(h, "plot [-4:4][-4:4] NaN title \"Work Space\"");
	gnuplot_cmd(h,"unset arrow");
	// plot configSpace
	gnuplot_cmd(h,"splot [-3.1:3.1][-3.1:3.1][-3.1:3.1] \"-\" using 1:2:3 with points pointtype 26 ps 0.3 title \"Configuration Space\" ");
	for(i=0;i<cs_size;i++){
		gnuplot_cmd(h,"%f %f %f", configSpace[i][0], configSpace[i][1], configSpace[i][2]);	
	}
	gnuplot_cmd(h,"e");
	gnuplot_cmd(h,"unset multiplot");	
	mysleep(delay);
}









