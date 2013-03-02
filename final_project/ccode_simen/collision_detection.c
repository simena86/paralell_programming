#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "collision_detection.h"

int IsOnSegment(double xi, double yi, double xj, double yj,
                        double xk, double yk) {
  return (xi <= xk || xj <= xk) && (xk <= xi || xk <= xj) &&
         (yi <= yk || yj <= yk) && (yk <= yi || yk <= yj);
}

double ComputeDirection(double xi, double yi, double xj, double yj,
                             double xk, double yk) {
  double a = (xk - xi) * (yj - yi);
  double b = (xj - xi) * (yk - yi);
  return a < b ? -1 : a > b ? 1 : 0;
}

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


int main(){
	struct point p1;
	struct point p2;
	struct point p3;
	struct point p4;
	p1.x=2;
	p1.y=2;
	p2.x=3;
	p2.y=4;
	p3.x=0;
	p3.y=5;
	p4.x=3;
	p4.y=1;
	int ret;
	ret =check_if_segment_intersects(	 


}
