
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

#endif
