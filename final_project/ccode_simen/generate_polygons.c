#include <stdio.h>
#include <jansson.h>
#include "collision_detection.h"
#include "gnuplot_i.h"
#include <time.h>
#include "compute3LinkFreeWorkspace.h"
#include "generate_polygons.h"

void print_polygon(struct polygon aPolygon){
	int i;
	puts("Polygon data\n");
	for(i=0;i<aPolygon.numberOfVertices;i++){
		printf("Vertice number %d : (%2.2f, %2.2f)\n",i,aPolygon.x_list[i], aPolygon.y_list[i]);
	}
}

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


// allocate memory for 
void allocate_memory_polygons(struct polygon *obstacle1, struct polygon *obstacle2, struct polygon* link1, 
							struct polygon* link2,struct polygon* link3){
	int i;
	obstacle1->x_list=(double *)malloc(obstacle1->numberOfVertices*sizeof(double));
	obstacle2->x_list=(double *)malloc(obstacle2->numberOfVertices*sizeof(double));
	obstacle1->y_list=(double *)malloc(obstacle1->numberOfVertices*sizeof(double));
	obstacle2->y_list=(double *)malloc(obstacle2->numberOfVertices*sizeof(double));
	link1->x_list=(double*)malloc(link1->numberOfVertices*sizeof(double));
	link1->y_list=(double*)malloc(link1->numberOfVertices*sizeof(double));
	link2->x_list=(double*)malloc(link2->numberOfVertices*sizeof(double));
	link2->y_list=(double*)malloc(link2->numberOfVertices*sizeof(double));
	link3->x_list=(double*)malloc(link3->numberOfVertices*sizeof(double));
	link3->y_list=(double*)malloc(link3->numberOfVertices*sizeof(double));
}


// load obstacle data from json 
void get_obstacle_data(json_t* obstacles,struct polygon* obstacle1,struct polygon* obstacle2){
	int i;
	for(i=0;i<obstacle1->numberOfVertices;i++){
		obstacle1->x_list[i]=json_number_value(  json_array_get( 	json_object_get(obstacles,"obstacle1x")     , i)    );
		obstacle1->y_list[i]=json_number_value(  json_array_get( 	json_object_get(obstacles,"obstacle1y")     , i)    );
	}
	for(i=0;i<obstacle2->numberOfVertices;i++){
		obstacle2->x_list[i]=json_number_value(  json_array_get( 	json_object_get(obstacles,"obstacle2x")     , i)    );
		obstacle2->y_list[i]=json_number_value(  json_array_get( 	json_object_get(obstacles,"obstacle2y")     , i)    );
	}
}


// load  robot-link data from json 
void get_link_data(json_t* linkPolys,json_t* linkBases,struct polygon* link1,struct polygon* link2,struct polygon* link3,
					struct point* base1,struct point* base2,struct point* base3){
	int i;
	for(i=0;i<link1->numberOfVertices;i++){
		link1->x_list[i]=json_number_value(  json_array_get( 	json_object_get(linkPolys,"link1x")     , i)    );
		link1->y_list[i]=json_number_value(  json_array_get( 	json_object_get(linkPolys,"link1y")     , i)    );
	}
	for(i=0;i<link3->numberOfVertices;i++){
		link2->x_list[i]=json_number_value(  json_array_get( 	json_object_get(linkPolys,"link2x")     , i)    );
		link2->y_list[i]=json_number_value(  json_array_get( 	json_object_get(linkPolys,"link2y")     , i)    );
	}
	for(i=0;i<link3->numberOfVertices;i++){
		link3->x_list[i]=json_number_value(  json_array_get( 	json_object_get(linkPolys,"link3x")     , i)    );
		link3->y_list[i]=json_number_value(  json_array_get( 	json_object_get(linkPolys,"link3y")     , i)    );
	}
	base1->x=json_number_value(  json_array_get( 	json_object_get(linkBases,"base1")     , 0)    );
	base1->y=json_number_value(  json_array_get( 	json_object_get(linkBases,"base1")     , 1)    );
	base2->x=json_number_value(  json_array_get( 	json_object_get(linkBases,"base2")     , 0)    );
	base2->y=json_number_value(  json_array_get( 	json_object_get(linkBases,"base2")     , 1)    );
	base3->x=json_number_value(  json_array_get( 	json_object_get(linkBases,"base3")     , 0)    );
	base3->y=json_number_value(  json_array_get( 	json_object_get(linkBases,"base3")     , 1)    );
}

/*
 * Parse a json file to get data for obstacles and links
 */
void generate_obstacles_and_links( struct polygon* obstacle1, struct polygon* obstacle2, struct polygon* link1, struct polygon* link2, 
				struct polygon* link3, struct point* base1, struct point* base2, struct point* base3){
	json_error_t error;
	json_t *root;
	json_t* linkBases, *links, *linkPolys;
	json_t* obstacles;
	root=json_load_file("../matlab_generate_polygons/polygons.json",0,&error);
	links=json_object_get(root,"links");
	linkPolys=json_object_get(links,"linkPolys");
	linkBases=json_object_get(links,"linkBases");
	obstacles=json_object_get(root, "obstacles");

	// get all lengths of vertices of polygons
	// links
	link1->numberOfVertices=json_integer_value( json_object_get(linkPolys,"nVertices1") ) ;
	link2->numberOfVertices=json_integer_value( json_object_get(linkPolys,"nVertices2") ) ;
	link3->numberOfVertices=json_integer_value( json_object_get(linkPolys,"nVertices3") ) ;
	obstacle1->numberOfVertices=json_integer_value(json_object_get(obstacles,"nVertices1"));
	obstacle2->numberOfVertices=json_integer_value(json_object_get(obstacles,"nVertices2") );
	allocate_memory_polygons(obstacle1, obstacle2, link1, link2,link3);

	get_link_data(linkPolys,linkBases,link1,link2,link3,base1,base2,base3);
	get_obstacle_data(obstacles,obstacle1,obstacle2);
	char *string;
	json_decref(links);
	json_decref(root);
	json_decref(linkPolys);
	json_decref(obstacles);
	json_decref( linkBases);
}



void print_polygon_data( struct polygon obstacle1, struct polygon obstacle2, struct polygon link1, struct polygon link2, 
				struct polygon link3, struct point base1, struct point base2, struct point base3){
	int i;
	puts("\n Links ---------\n");
	puts("link1");
	for(i=0;i<link1.numberOfVertices;i++){
		printf("------ (x1, y1) = %2.2f, %2.2f\n", link1.x_list[i], link1.y_list[i]);
	}
	puts("link2");
	for(i=0;i<link2.numberOfVertices;i++){
		printf("------ (x1, y1) = %2.2f, %2.2f\n", link2.x_list[i], link2.y_list[i]);
	}
	puts("link3");
	for(i=0;i<link3.numberOfVertices;i++){
		printf("------ (x1, y1) = %2.2f, %2.2f\n", link3.x_list[i], link3.y_list[i]);
	}
	printf("base1 : (%2.2f,%2.2f), base2 : (%2.2f,%2.2f), base3 : (%2.2f,%2.2f)\n",base1.x,base1.y,base2.x,base2.y,base3.x,base3.y );

}

