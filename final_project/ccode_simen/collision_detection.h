
#ifndef _COLLISTION_DETECTION_
#define _COLLISTION_DETECTION_

#include "my_type_defs.h"
	

/* checks collision between 2 polygons by checking if their edges
 * intersects or if any point of one polygon is inside another */
int check_collision(struct polygon poly1,struct polygon poly2);


#endif
