#include "headers.h"

void mysleep(long int milisecond){
	long int i=0;
	double a=14;
	for(i=0;i<milisecond*100;i++){
		a=i*a/4.5;	
		a=sqrt(a*a + sqrt(44444));
	}
}

void draw_polygons(struct polygon* polygons, int number_of_polygons,int delay){
	if(h==0){
		h = gnuplot_init();
		gnuplot_cmd(h, "clear");
		gnuplot_cmd(h,"reset");
		//gnuplot_cmd(h,"set terminal gif animate ");
		//gnuplot_cmd(h,"set output \"animate.gif\"");
		gnuplot_cmd(h,"set terminal gif small animate delay 7 optimize");
		gnuplot_cmd(h,"set output \"animate.gif\"");
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





void draw_adjTable( unsigned int cs_size,double **cs,unsigned int* atArr,unsigned int **at,long int delay){
	int i,j;
	if(h==0){
		h = gnuplot_init();
		gnuplot_cmd(h, "clear");
		gnuplot_cmd(h,"reset");
		gnuplot_cmd(h,"set terminal gif small animate delay 1 optimize");
		gnuplot_cmd(h,"set output \"animate.gif\"");
		gnuplot_cmd(h, "set isosample 40" );
//		gnuplot_cmd(h,"set terminal postscript color");
//		gnuplot_cmd(h,"set output \"plot1.ps\"");
//		gnuplot_cmd(h, "set xrange [-4:4]");
//		gnuplot_cmd(h, "set yrange [-4:4]");
//		gnuplot_cmd(h, "set zrange [-4:4]");
//		gnuplot_cmd(h, "set xlabel \"theta_1\" ");
//		gnuplot_cmd(h, "set ylabel \"theta_2\" ");
//		gnuplot_cmd(h, "set zlabel \"theta_3\" ");
	}
	gnuplot_resetplot(h);	
	gnuplot_cmd(h,"set multiplot");

	double tol=0.001;
	gnuplot_cmd(h,"splot [-3.2:3.2][-3.2:3.2][-3.2:3.2] \"-\" using 1:2:3 with points pointtype 26 ps 0.6 notitle ");
	for(i=0;i<cs_size;i++){
		if( cs[i][0]<(-PI+tol) || cs[i][1]<(-PI+tol) || cs[i][2]<(-PI+tol) || 
			cs[i][0]>(PI-tol) || cs[i][1]>(PI-tol) || cs[i][2]>(PI-tol) ){
			// do nothing
		}else{
			gnuplot_cmd(h,"%f %f %f", cs[i][0], cs[i][1], cs[i][2]);	
		}
	}
	gnuplot_cmd(h,"e");

	gnuplot_cmd(h, "set xlabel \"theta_1\" ")	;
	gnuplot_cmd(h, "set ylabel \"theta_2\" ")	;
	gnuplot_cmd(h, "set zlabel \"theta_3\" ")	;
	gnuplot_cmd(h, "set style arrow 1 nohead")	;
	
	gnuplot_cmd(h, "set label 1 \" Free Configuration Space \" at 1,2 ")	;
	int temp;
	for(i=0;i<cs_size;i++){
		for(j=0;j<atArr[i];j++){
			temp=at[i][j];
			if( cs[i][0]<(-PI+tol) || cs[i][1]<(-PI+tol) || cs[i][2]<(-PI+tol) || 
				cs[i][0]>(PI-tol) || cs[i][1]>(PI-tol) || cs[i][2]>(PI-tol) ||
				(cs[temp][0]<(-PI+tol) || cs[temp][1]<(-PI+tol) || cs[temp][2]<(-PI+tol) ||
				 cs[temp][0]>(PI-tol)  || cs[temp][1]>(PI-tol) || cs[temp][2]>(PI-tol)) ){
				// do nothing
			}else{
				gnuplot_cmd(h, "set arrow from %f,%f,%f to %f,%f,%f as 1",cs[i][0],cs[i][1], cs[i][2],cs[temp][0],cs[temp][1], cs[temp][2]);   
				mysleep(delay);
				gnuplot_cmd(h,"splot[-3.2:3.2][-3.2:3.2][-3.2:3.2] NaN notitle");
			}	
		}
	}
	gnuplot_cmd(h,"set label 2 \"Adjacency table\" at 2,2 ")	;
	gnuplot_cmd(h,"show label ")	;
	mysleep(delay);
//	gnuplot_cmd(h,"unset multiplot");
}


void draw_shortest_path(struct Status s,unsigned int path_length,unsigned int* path){
	int i,k;
	char j,collision;
		
	// reference polygons
	struct polygon obstacle1, obstacle2, link1Poly,link2Poly,link3Poly;
	struct point link1BaseRef,link2BaseRef,link3BaseRef;;
	generate_obstacles_and_links(&obstacle1, &obstacle2, &link1Poly, &link2Poly, &link3Poly , &link1BaseRef , &link2BaseRef , &link3BaseRef);
	int numberOfObstacles=2;
	struct polygon *obstacleList;
	obstacleList=(struct polygon*)malloc(numberOfObstacles*sizeof(struct polygon));
	obstacleList[0]=obstacle1;
	obstacleList[1]=obstacle2;
	
	// list of all polygons used for drawing 
	static struct polygon* polygons;
	polygons=(struct polygon*)malloc(5*sizeof(struct polygon));
	static struct point displacedLinkEnd1, displacedLinkEnd2, displacedLinkEnd3;
	static struct polygon displacedLink1, displacedLink2, displacedLink3;
	initTempPolys(link1Poly,link2Poly,link2Poly, &displacedLink1 , &displacedLink2 , &displacedLink3  );

	// iterate through sample_list and check for collision wit obstacles
	double temp[3];
	for(i=0;i< path_length ;i++){
		temp[0]=s.cs_total[ path[i] ][0];
		temp[1]=s.cs_total[ path[i] ][1];
		temp[2]=s.cs_total[ path[i] ][2];


		displaceLinkPoly(temp[0], &displacedLink1, &displacedLinkEnd1, link1BaseRef, link1Poly, link2BaseRef);	
		displaceLinkPoly(temp[0]+temp[1],&displacedLink2,&displacedLinkEnd2,displacedLinkEnd1,link2Poly,link3BaseRef);	
		displaceLinkPoly(temp[0]+temp[1]+temp[2],&displacedLink3,&displacedLinkEnd3,displacedLinkEnd2, 
						link3Poly, link3BaseRef);	
		polygons[0] = displacedLink1;
		polygons[1] = displacedLink2;
		polygons[2] = displacedLink3;
		polygons[3] = obstacleList[0];
		polygons[4] = obstacleList[1];
		draw_polygons(polygons,5,1000);

	}	
	free(polygons);
	free(displacedLink1.x_list);
	free(displacedLink2.x_list);
	free(displacedLink3.x_list);
	free(displacedLink1.y_list);
	free(displacedLink2.y_list);
	free(displacedLink3.y_list);
}



