#ifndef _GEN_POLYS_
#define _GEN_POLYS_

void generate_obstacles_and_links( struct polygon* obstacle1, struct polygon* obstacle2, struct polygon* link1, struct polygon* link2, 
				struct polygon* link3, struct point* base1, struct point* base2, struct point* base3);

void print_polygon_data( struct polygon obstacle1, struct polygon obstacle2, struct polygon link1, struct polygon link2, 
				struct polygon link3, struct point base1, struct point base2, struct point base3);

#endif
