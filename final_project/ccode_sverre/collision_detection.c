#include "headers.h"


/*	check if point p1 is on the inside of every line segment joining vertices in polygon
 *	using the cross product to check this. 
 *  vector from vertice i to vertice i+1 : v_i --> v_i+1
 *  vector from v1 to point p1 :	       v_i --> p1   */ 
int check_if_outside_convex_polygon(struct point p1, struct polygon poly1){
	double vec_polygon_edge_x, vec_polygon_edge_y, vec_poly_point_x,vec_poly_point_y, cross_prod_z_component;
	int i;
	for(i=0;i<poly1.numberOfVertices-1;i++){
		vec_polygon_edge_x=poly1.x_list[i+1] - poly1.x_list[i];
		vec_polygon_edge_y=poly1.y_list[i+1] - poly1.y_list[i];
		vec_poly_point_x=p1.x-poly1.x_list[i];
		vec_poly_point_y=p1.y-poly1.y_list[i];
		cross_prod_z_component=vec_polygon_edge_x*vec_poly_point_y - vec_polygon_edge_y*vec_poly_point_x;
		if(cross_prod_z_component < 0){
			return TRUE;
		}
	} 
	return FALSE;
}

/* do line segment p11--p12, p21--p22 intersect */
int check_if_segment_intersects(struct point p11, struct point p12, struct point p21, struct point p22){
	double den=(p22.y-p21.y)*(p12.x-p11.x) - (p22.x-p21.x)*(p12.y-p11.y);
	double u_a=(p22.x-p21.x)*(p11.y-p21.y) - (p22.y-p21.y)*(p11.x-p21.x);
	double u_b=(p12.x-p11.x)*(p11.y-p21.y)-(p12.y-p11.y)*(p11.x-p21.x);
//	u_a=u_a/den;
//	u_b=u_b/den;
//	if( u_a >= 0 && u_a <= 1 && u_b >= 0 && u_b <= 1 ){
	if( u_a >= 0 && u_b >= 0 &&  u_a <= 1*den && u_b <= 1*den ){
		return TRUE;
	}else{
		return FALSE;
	}
}

int check_collision(struct polygon poly1, struct polygon poly2){
	int i,j;
	struct point p1,p2,p3,p4;
	// check for line intersection;
	for(i=0;i<poly1.numberOfVertices-1;i++){
		for(j=0;j<poly2.numberOfVertices-1;j++){
			p1.x=poly1.x_list[i];
			p1.y=poly1.y_list[i];
			p2.x=poly1.x_list[i+1];
			p2.y=poly1.y_list[i+1];
			p3.x=poly2.x_list[j];
			p3.y=poly2.y_list[j];
			p4.x=poly2.x_list[j+1];
			p4.y=poly2.y_list[j+1];
			if(check_if_segment_intersects(p1,p2,p3,p4)){
				return TRUE;
			}else if(!check_if_outside_convex_polygon(p3,poly1)){
				return TRUE;
			}else if(!check_if_outside_convex_polygon(p1,poly2)){
				return TRUE;
			}
		}	
	}
	return FALSE; 
}

void generate_polygons(struct polygon *p1, struct polygon* p2){
	int i;
	int nvertices=6;
	double cords_x[6]={ 1.3072,0.6720,-0.5132,-0.6040,0.3601,1.3072}; 
	double cords_y[6]={ -0.0231,1.6069,1.2948,-0.1734,-1.2832,-0.0231};
	p1->numberOfVertices=nvertices;
	p2->numberOfVertices=nvertices;
	p1->x_list=(double *)malloc(p1->numberOfVertices*sizeof(double));
	p1->y_list=(double *)malloc(p1->numberOfVertices*sizeof(double));
	p2->x_list=(double *)malloc(p2->numberOfVertices*sizeof(double));
	p2->y_list=(double *)malloc(p2->numberOfVertices*sizeof(double));
	for(i=0;i<p1->numberOfVertices;i++){
		p1->x_list[i]=cords_x[i];
		p1->y_list[i]=cords_y[i];
	}
	for(i=0;i<p2->numberOfVertices;i++){
		p2->x_list[i]=cords_x[i]+1 ;
		p2->y_list[i]=cords_y[i]+1 ;
	}
}
