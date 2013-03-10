#ifndef _GEN_POLYS_
#define _GEN_POLYS_

#include "my_type_defs.h"

/*
 *	read data from a json file "polygons.json" to initialize link- and obstacle polygons with their
 *	vertices, and link bases
 */
void generate_obstacles_and_links( struct polygon* obstacle1, struct polygon* obstacle2, struct polygon* link1, struct polygon* link2, 
				struct polygon* link3, struct point* base1, struct point* base2, struct point* base3);

void print_polygon_data( struct polygon obstacle1, struct polygon obstacle2, struct polygon link1, struct polygon link2, 
				struct polygon link3, struct point base1, struct point base2, struct point base3);

void print_polygon(struct polygon aPolygon);





#endif
