#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "collision_detection.h"

/*	check if point p1 is on the inside of every line segment joining vertices in polygon
 *	using the cross product to check this. 
 *  vector from vertice i to vertice i+1 : v_i --> v_i+1
 *  vector from v1 to point p1 :			  v_i --> p1   */ 
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


int IsOnSegment(double xi, double yi, double xj, double yj,double xk,double yk){
  return (xi <= xk || xj <= xk) && (xk <= xi || xk <= xj) &&
         (yi <= yk || yj <= yk) && (yk <= yi || yk <= yj);
}

double ComputeDirection(double xi, double yi, double xj, double yj,double xk, double yk){
  double a = (xk - xi) * (yj - yi);
  double b = (xj - xi) * (yk - yi);
  return a < b ? -1 : a > b ? 1 : 0;
}

/* do line segment p11--p12, p21--p22 intersect */
int check_if_segment_intersects(struct point p11, struct point p12, struct point p21, struct point p22){
	int x1, x2, x3,x4, y1,y2,y3,y4;
	x1=p11.x;
	y1=p11.y;
	x2=p12.x;
	y2=p12.y;
	x3=p21.x;
	y3=p21.y;
	x4=p22.x;
	y4=p22.y;
	double d1 = ComputeDirection(x3, y3, x4, y4, x1, y1);
	double d2 = ComputeDirection(x3, y3, x4, y4, x2, y2);
	double d3 = ComputeDirection(x1, y1, x2, y2, x3, y3);
	double d4 = ComputeDirection(x1, y1, x2, y2, x4, y4);
	return (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
         ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) ||
         (d1 == 0 && IsOnSegment(x3, y3, x4, y4, x1, y1)) ||
         (d2 == 0 && IsOnSegment(x3, y3, x4, y4, x2, y2)) ||
         (d3 == 0 && IsOnSegment(x1, y1, x2, y2, x3, y3)) ||
         (d4 == 0 && IsOnSegment(x1, y1, x2, y2, x4, y4));
}

int check_collision(struct polygon poly1, struct polygon poly2){
	int i,j;
	// check for line intersection;
	for(i=0;i<poly1.numberOfVertices-1;i++){
		for(j=0;j<poly2.numberOfVertices-1;j++){
			struct point p1={poly1.x_list[i], poly1.y_list[i]};
			struct point p2={poly1.x_list[i+1], poly1.y_list[i+1]};
			struct point p3={poly2.x_list[j], poly2.y_list[j]};
			struct point p4={poly2.x_list[j+1], poly2.y_list[j+1]};
			if(check_if_segment_intersects(p1,p2,p3,p4)){
				return TRUE;
			}else if(check_if_outside_convex_polygon(p1,poly1)){
				return TRUE;
			}else if(check_if_outside_convex_polygon(p3,poly2)){
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

int main(){
	int ret;
	struct polygon poly1;
	struct polygon poly2;
	generate_polygons(&poly1,&poly2);
	ret=check_collision(poly1,poly2);
	printf("collision : %d",ret);
	return 0;
}
