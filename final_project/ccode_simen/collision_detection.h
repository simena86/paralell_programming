
#ifndef _COLLISTION_DETECTION_
	#define _COLLISTION_DETECTION_

	#ifndef FALSE 
		#define FALSE 0
	#endif 
	#ifndef TRUE
		#define TRUE 1
	#endif
	
	struct polygon{
		double *x_list;
		double *y_list;	
		int numberOfVertices;
	};
	
	struct point{
		double x;
		double y;
	};	
	
	int check_if_segment_intersects(struct point p1,struct point p2,struct point p3,struct point p4);
#endif
