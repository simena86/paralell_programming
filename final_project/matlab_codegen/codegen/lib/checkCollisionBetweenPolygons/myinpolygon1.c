/*
 * myinpolygon1.c
 *
 * Code generation for function 'myinpolygon1'
 *
 * C source code generated on: Fri Mar  1 11:27:49 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "checkCollisionBetweenPolygons.h"
#include "myinpolygon.h"
#include "myinpolygon1.h"
#include "any.h"
#include "sum.h"
#include "abs.h"
#include "diff.h"
#include "bsxfun.h"
#include "sign.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void b_vec_inpolygon(const real_T x_data[20], const int32_T x_sizes[2],
  const real_T y_data[20], const int32_T y_sizes[2], const real_T xv[20], const
  real_T yv[20], boolean_T in_data[20], int32_T in_sizes[2], boolean_T on_data
  [20], int32_T on_sizes[2]);
static void e_eml_li_find(const boolean_T x[20], int32_T y_data[20], int32_T
  y_sizes[2]);
static void f_eml_li_find(const boolean_T x_data[400], const int32_T x_sizes[2],
  int32_T y_data[400], int32_T y_sizes[1]);
static void g_eml_li_find(const boolean_T x_data[380], const int32_T x_sizes[2],
  int32_T y_data[380], int32_T y_sizes[1]);
static void h_eml_li_find(const boolean_T x_data[20], const int32_T x_sizes[2],
  int32_T y_data[20], int32_T y_sizes[1]);

/* Function Definitions */
static void b_vec_inpolygon(const real_T x_data[20], const int32_T x_sizes[2],
  const real_T y_data[20], const int32_T y_sizes[2], const real_T xv[20], const
  real_T yv[20], boolean_T in_data[20], int32_T in_sizes[2], boolean_T on_data
  [20], int32_T on_sizes[2])
{
  real_T avy[19];
  real_T scaleFactor[19];
  int32_T i;
  real_T avx[19];
  real_T u0;
  real_T u1;
  int32_T loop_ub;
  int32_T i4;
  real_T xv_data[400];
  real_T yv_data[400];
  boolean_T posX_data[400];
  boolean_T posY_data[400];
  boolean_T negX_data[400];
  boolean_T negY_data[400];
  int32_T quad_sizes[2];
  real_T quad_data[400];
  int32_T idx_sizes[2];
  int32_T tmp_sizes;
  int32_T tmp_data[400];
  int32_T b_tmp_data[400];
  int32_T theCrossProd_sizes[2];
  real_T theCrossProd_data[380];
  int32_T signCrossProduct_sizes[2];
  real_T signCrossProduct_data[380];
  real_T diffQuad_data[380];
  int32_T diffQuad_sizes[2];
  boolean_T idx_data[380];
  int32_T c_tmp_data[380];
  int32_T d_tmp_data[380];
  int32_T e_tmp_data[380];
  real_T A_data[380];
  real_T f_tmp_data[20];
  int32_T b_signCrossProduct_sizes[2];

  /* ---------------------------------------------- */
  /*  vectorize the computation. */
  /*  Compute scale factors for eps that are based on the original vertex  */
  /*  locations. This ensures that the test points that lie on the boundary  */
  /*  will be evaluated using an appropriately scaled tolerance. */
  /*  (m and mp1 will be reused for setting up adjacent vertices later on.) */
  for (i = 0; i < 19; i++) {
    avy[i] = 0.5 * (xv[i] + xv[i + 1]);
    scaleFactor[i] = 0.5 * (yv[i] + yv[i + 1]);
  }

  d_abs(avy, avx);
  d_abs(scaleFactor, avy);
  for (i = 0; i < 19; i++) {
    u0 = avx[i];
    u1 = avy[i];
    u0 = (u0 >= u1) || rtIsNaN(u1) ? u0 : u1;
    u1 = avx[i] * avy[i];
    u0 = (u0 >= u1) || rtIsNaN(u1) ? u0 : u1;
    scaleFactor[i] = u0;
  }

  /*  Translate the vertices so that the test points are */
  /*  at the origin. */
  loop_ub = x_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    for (i = 0; i < 20; i++) {
      xv_data[i + 20 * i4] = xv[i] - x_data[x_sizes[0] * i4];
    }
  }

  loop_ub = x_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    for (i = 0; i < 20; i++) {
      yv_data[i + 20 * i4] = yv[i] - y_data[y_sizes[0] * i4];
    }
  }

  /*  Compute the quadrant number for the vertices relative */
  /*  to the test points. */
  loop_ub = 20 * x_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    posX_data[i4] = (xv_data[i4] > 0.0);
  }

  loop_ub = 20 * x_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    posY_data[i4] = (yv_data[i4] > 0.0);
  }

  loop_ub = 20 * x_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    negX_data[i4] = !posX_data[i4];
  }

  loop_ub = 20 * x_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    negY_data[i4] = !posY_data[i4];
  }

  quad_sizes[0] = 20;
  quad_sizes[1] = x_sizes[1];
  loop_ub = 20 * x_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    quad_data[i4] = ((real_T)(negX_data[i4] && posY_data[i4]) + 2.0 * (real_T)
                     (negX_data[i4] && negY_data[i4])) + 3.0 * (real_T)
      (posX_data[i4] && negY_data[i4]);
  }

  /*  Ignore crossings between distinct edge loops that are separated by NaNs */
  loop_ub = 20 * x_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    posX_data[i4] = rtIsNaN(xv_data[i4]);
  }

  loop_ub = 20 * x_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    posY_data[i4] = rtIsNaN(yv_data[i4]);
  }

  idx_sizes[0] = 20;
  idx_sizes[1] = x_sizes[1];
  loop_ub = 20 * x_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    negX_data[i4] = (posX_data[i4] || posY_data[i4]);
  }

  f_eml_li_find(negX_data, idx_sizes, tmp_data, *(int32_T (*)[1])&tmp_sizes);
  loop_ub = tmp_sizes - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    b_tmp_data[i4] = tmp_data[i4];
  }

  loop_ub = tmp_sizes - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    quad_data[b_tmp_data[i4] - 1] = rtNaN;
  }

  /*  Compute the sign() of the cross product and dot product */
  /*  of adjacent vertices. */
  theCrossProd_sizes[0] = 19;
  theCrossProd_sizes[1] = x_sizes[1];
  loop_ub = x_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    for (i = 0; i < 19; i++) {
      theCrossProd_data[i + 19 * i4] = xv_data[i + 20 * i4] * yv_data[(i + 20 *
        i4) + 1] - xv_data[(i + 20 * i4) + 1] * yv_data[i + 20 * i4];
    }
  }

  signCrossProduct_sizes[0] = 19;
  signCrossProduct_sizes[1] = theCrossProd_sizes[1];
  loop_ub = 19 * theCrossProd_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    signCrossProduct_data[i4] = theCrossProd_data[i4];
  }

  c_sign(signCrossProduct_data, signCrossProduct_sizes);

  /*  Adjust values that are within epsilon of the polygon boundary. */
  /*  Making epsilon larger will treat points close to the boundary as  */
  /*  being "on" the boundary. A factor of 3 was found from experiment to be */
  /*  a good margin to hedge against roundoff. */
  diffQuad_sizes[0] = 19;
  diffQuad_sizes[1] = theCrossProd_sizes[1];
  loop_ub = 19 * theCrossProd_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    diffQuad_data[i4] = theCrossProd_data[i4];
  }

  e_abs(diffQuad_data, diffQuad_sizes, theCrossProd_data, theCrossProd_sizes);
  for (i = 0; i < 19; i++) {
    avy[i] = scaleFactor[i] * 2.2204460492503131E-16 * 3.0;
  }

  b_bsxfun(theCrossProd_data, theCrossProd_sizes, avy, idx_data, idx_sizes);
  g_eml_li_find(idx_data, idx_sizes, c_tmp_data, *(int32_T (*)[1])&tmp_sizes);
  loop_ub = tmp_sizes - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    d_tmp_data[i4] = c_tmp_data[i4];
  }

  loop_ub = tmp_sizes - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    signCrossProduct_data[d_tmp_data[i4] - 1] = 0.0;
  }

  /*  Compute the vertex quadrant changes for each test point. */
  b_diff(quad_data, quad_sizes, diffQuad_data, diffQuad_sizes);

  /*  Fix up the quadrant differences.  Replace 3 by -1 and -3 by 1. */
  /*  Any quadrant difference with an absolute value of 2 should have */
  /*  the same sign as the cross product. */
  e_abs(diffQuad_data, diffQuad_sizes, theCrossProd_data, theCrossProd_sizes);
  idx_sizes[0] = 19;
  idx_sizes[1] = theCrossProd_sizes[1];
  loop_ub = theCrossProd_sizes[0] * theCrossProd_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    idx_data[i4] = (theCrossProd_data[i4] == 3.0);
  }

  g_eml_li_find(idx_data, idx_sizes, c_tmp_data, *(int32_T (*)[1])&tmp_sizes);
  g_eml_li_find(idx_data, idx_sizes, d_tmp_data, *(int32_T (*)[1])&i);
  loop_ub = i - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    e_tmp_data[i4] = d_tmp_data[i4];
  }

  loop_ub = tmp_sizes - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    A_data[i4] = -diffQuad_data[c_tmp_data[i4] - 1];
  }

  loop_ub = tmp_sizes - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    diffQuad_data[e_tmp_data[i4] - 1] = A_data[i4] / 3.0;
  }

  e_abs(diffQuad_data, diffQuad_sizes, theCrossProd_data, theCrossProd_sizes);
  idx_sizes[0] = 19;
  idx_sizes[1] = theCrossProd_sizes[1];
  loop_ub = theCrossProd_sizes[0] * theCrossProd_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    idx_data[i4] = (theCrossProd_data[i4] == 2.0);
  }

  g_eml_li_find(idx_data, idx_sizes, c_tmp_data, *(int32_T (*)[1])&tmp_sizes);
  g_eml_li_find(idx_data, idx_sizes, d_tmp_data, *(int32_T (*)[1])&i);
  loop_ub = i - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    e_tmp_data[i4] = d_tmp_data[i4];
  }

  loop_ub = tmp_sizes - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    diffQuad_data[e_tmp_data[i4] - 1] = 2.0 *
      signCrossProduct_data[c_tmp_data[i4] - 1];
  }

  /*  Find the inside points. */
  /*  Ignore crossings between distinct loops that are separated by NaNs */
  idx_sizes[0] = 19;
  idx_sizes[1] = diffQuad_sizes[1];
  loop_ub = diffQuad_sizes[0] * diffQuad_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    idx_data[i4] = rtIsNaN(diffQuad_data[i4]);
  }

  g_eml_li_find(idx_data, idx_sizes, c_tmp_data, *(int32_T (*)[1])&tmp_sizes);
  loop_ub = tmp_sizes - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    d_tmp_data[i4] = c_tmp_data[i4];
  }

  loop_ub = tmp_sizes - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    diffQuad_data[d_tmp_data[i4] - 1] = 0.0;
  }

  b_sum(diffQuad_data, diffQuad_sizes, f_tmp_data, idx_sizes);
  in_sizes[0] = 1;
  in_sizes[1] = idx_sizes[1];
  loop_ub = idx_sizes[0] * idx_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    in_data[i4] = (f_tmp_data[i4] != 0.0);
  }

  /*  Find the points on the polygon.  If the cross product is 0 and */
  /*  the dot product is nonpositive anywhere, then the corresponding */
  /*  point must be on the contour. */
  b_signCrossProduct_sizes[0] = 19;
  b_signCrossProduct_sizes[1] = signCrossProduct_sizes[1];
  loop_ub = signCrossProduct_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    for (i = 0; i < 19; i++) {
      idx_data[i + 19 * i4] = ((signCrossProduct_data[i +
        signCrossProduct_sizes[0] * i4] == 0.0) && (xv_data[i + 20 * i4] *
        xv_data[(i + 20 * i4) + 1] + yv_data[i + 20 * i4] * yv_data[(i + 20 * i4)
        + 1] <= 0.0));
    }
  }

  b_any(idx_data, b_signCrossProduct_sizes, on_data, on_sizes);
  in_sizes[0] = 1;
  loop_ub = in_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    in_data[i4] = (in_data[i4] || on_data[i4]);
  }
}

static void e_eml_li_find(const boolean_T x[20], int32_T y_data[20], int32_T
  y_sizes[2])
{
  int32_T k;
  int32_T i;
  k = 0;
  for (i = 0; i < 20; i++) {
    if (x[i]) {
      k++;
    }
  }

  y_sizes[0] = 1;
  y_sizes[1] = k;
  k = 0;
  for (i = 0; i < 20; i++) {
    if (x[i]) {
      y_data[k] = i + 1;
      k++;
    }
  }
}

static void f_eml_li_find(const boolean_T x_data[400], const int32_T x_sizes[2],
  int32_T y_data[400], int32_T y_sizes[1])
{
  int32_T n;
  int32_T k;
  int32_T i;
  n = 20 * x_sizes[1];
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x_data[i - 1]) {
      k++;
    }
  }

  y_sizes[0] = k;
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x_data[i - 1]) {
      y_data[k] = i;
      k++;
    }
  }
}

static void g_eml_li_find(const boolean_T x_data[380], const int32_T x_sizes[2],
  int32_T y_data[380], int32_T y_sizes[1])
{
  int32_T n;
  int32_T k;
  int32_T i;
  n = 19 * x_sizes[1];
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x_data[i - 1]) {
      k++;
    }
  }

  y_sizes[0] = k;
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x_data[i - 1]) {
      y_data[k] = i;
      k++;
    }
  }
}

static void h_eml_li_find(const boolean_T x_data[20], const int32_T x_sizes[2],
  int32_T y_data[20], int32_T y_sizes[1])
{
  int32_T k;
  int32_T i;
  k = 0;
  for (i = 1; i <= x_sizes[1]; i++) {
    if (x_data[i - 1]) {
      k++;
    }
  }

  y_sizes[0] = k;
  k = 0;
  for (i = 1; i <= x_sizes[1]; i++) {
    if (x_data[i - 1]) {
      y_data[k] = i;
      k++;
    }
  }
}

void myinpolygon(const real_T x[20], const real_T y[20], const real_T xv[20],
                 const real_T yv[20], boolean_T in[20], boolean_T on_data[200],
                 int32_T on_sizes[2])
{
  int32_T ixstart;
  real_T mtmp;
  int32_T ix;
  boolean_T exitg6;
  real_T b_mtmp;
  boolean_T exitg5;
  real_T c_mtmp;
  boolean_T exitg4;
  real_T d_mtmp;
  boolean_T exitg3;
  boolean_T mask[20];
  boolean_T b_y;
  boolean_T exitg2;
  boolean_T b3;
  int32_T idx;
  int32_T ii_data[20];
  int32_T ii_sizes[2];
  boolean_T exitg1;
  boolean_T guard1 = FALSE;
  int32_T tmp_data[20];
  int32_T loop_ub;
  int8_T b_ii_data[20];
  int8_T inbounds_data[20];
  int32_T x_sizes[2];
  real_T x_data[20];
  int32_T y_sizes[2];
  real_T y_data[20];
  int32_T b_on_sizes[2];
  boolean_T b_on_data[20];
  boolean_T in_data[20];
  boolean_T onmask[20];
  int32_T c_on_sizes[2];
  int8_T b_tmp_data[20];
  int32_T in_sizes[2];
  int8_T c_tmp_data[20];

  /* INPOLYGON True for points inside or on a polygonal region. */
  /*    IN = INPOLYGON(X,Y,XV,YV) returns a matrix IN the size of X and Y. */
  /*    IN(p,q) = 1 if the point (X(p,q), Y(p,q)) is either strictly inside or */
  /*    on the edge of the polygonal region whose vertices are specified by the */
  /*    vectors XV and YV; otherwise IN(p,q) = 0. */
  /*  */
  /*    [IN ON] = INPOLYGON(X,Y,XV,YV) returns a second matrix, ON, which is  */
  /*    the size of X and Y.  ON(p,q) = 1 if the point (X(p,q), Y(p,q)) is on  */
  /*    the edge of the polygonal region; otherwise ON(p,q) = 0. */
  /*  */
  /*    INPOLYGON supports non-convex and self-intersecting polygons. */
  /*    The function also supports multiply-connected or disjoint polygons;  */
  /*    however, the distinct edge loops should be separated by NaNs. In the */
  /*    case of multiply-connected polygons, the external and internal loops */
  /*    should have opposite orientations; for example, a counterclockwise  */
  /*    outer loop and clockwise inner loops or vice versa. Self-intersections */
  /*    are not supported in this context due to the ambiguity associated with */
  /*    loop orientations. */
  /*  */
  /*    Example 1: */
  /*        % Self-intersecting polygon */
  /*        xv = rand(6,1); yv = rand(6,1); */
  /*        xv = [xv ; xv(1)]; yv = [yv ; yv(1)]; */
  /*        x = rand(1000,1); y = rand(1000,1); */
  /*        in = inpolygon(x,y,xv,yv); */
  /*        plot(xv,yv,x(in),y(in),'.r',x(~in),y(~in),'.b') */
  /*  */
  /*    Example 2: */
  /*        % Multiply-connected polygon - a square with a square hole. */
  /*        % Counterclockwise outer loop, clockwise inner loop. */
  /*        xv = [0 3 3 0 0 NaN 1 1 2 2 1]; */
  /*        yv = [0 0 3 3 0 NaN 1 2 2 1 1]; */
  /*        x = rand(1000,1)*3; y = rand(1000,1)*3; */
  /*        in = inpolygon(x,y,xv,yv); */
  /*        plot(xv,yv,x(in),y(in),'.r',x(~in),y(~in),'.b') */
  /*  */
  /*    Class support for inputs X,Y,XV,YV: */
  /*       float: double, single */
  /*  */
  /*    See also, DelaunayTri */
  /*  */
  /*    Copyright 1984-2011 The MathWorks, Inc. */
  /*    $Revision: 1.14.4.11 $  $Date: 2011/05/17 02:32:25 $ */
  /*  The algorithm is similar to that described in the following reference. */
  /*  */
  /*  @article{514556, */
  /*  author = {Kai Hormann and Alexander Agathos}, */
  /*  title = {The point in polygon problem for arbitrary polygons}, */
  /*  journal = {Comput. Geom. Theory Appl.}, */
  /*  volume = {20}, */
  /*  number = {3}, */
  /*  year = {2001}, */
  /*  issn = {0925-7721}, */
  /*  pages = {131--144}, */
  /*  doi = {http://dx.doi.org/10.1016/S0925-7721(01)00012-8}, */
  /*  publisher = {Elsevier Science Publishers B. V.}, */
  /*  address = {Amsterdam, The Netherlands, The Netherlands}, */
  /*  } */
  /*  The edge loops defining each contour are checked for closure, and if */
  /*  necessary they are closed. */
  ixstart = 1;
  mtmp = xv[0];
  if (rtIsNaN(xv[0])) {
    ix = 2;
    exitg6 = 0U;
    while ((exitg6 == 0U) && (ix < 21)) {
      ixstart = ix;
      if (!rtIsNaN(xv[ix - 1])) {
        mtmp = xv[ix - 1];
        exitg6 = 1U;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 20) {
    while (ixstart + 1 < 21) {
      if (xv[ixstart] < mtmp) {
        mtmp = xv[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  b_mtmp = xv[0];
  if (rtIsNaN(xv[0])) {
    ix = 2;
    exitg5 = 0U;
    while ((exitg5 == 0U) && (ix < 21)) {
      ixstart = ix;
      if (!rtIsNaN(xv[ix - 1])) {
        b_mtmp = xv[ix - 1];
        exitg5 = 1U;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 20) {
    while (ixstart + 1 < 21) {
      if (xv[ixstart] > b_mtmp) {
        b_mtmp = xv[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  c_mtmp = yv[0];
  if (rtIsNaN(yv[0])) {
    ix = 2;
    exitg4 = 0U;
    while ((exitg4 == 0U) && (ix < 21)) {
      ixstart = ix;
      if (!rtIsNaN(yv[ix - 1])) {
        c_mtmp = yv[ix - 1];
        exitg4 = 1U;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 20) {
    while (ixstart + 1 < 21) {
      if (yv[ixstart] < c_mtmp) {
        c_mtmp = yv[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  d_mtmp = yv[0];
  if (rtIsNaN(yv[0])) {
    ix = 2;
    exitg3 = 0U;
    while ((exitg3 == 0U) && (ix < 21)) {
      ixstart = ix;
      if (!rtIsNaN(yv[ix - 1])) {
        d_mtmp = yv[ix - 1];
        exitg3 = 1U;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 20) {
    while (ixstart + 1 < 21) {
      if (yv[ixstart] > d_mtmp) {
        d_mtmp = yv[ixstart];
      }

      ixstart++;
    }
  }

  for (ix = 0; ix < 20; ix++) {
    mask[ix] = ((x[ix] >= mtmp) && (x[ix] <= b_mtmp) && (y[ix] >= c_mtmp) &&
                (y[ix] <= d_mtmp));
  }

  b_y = FALSE;
  ixstart = 0;
  exitg2 = 0U;
  while ((exitg2 == 0U) && (ixstart < 20)) {
    if (mask[ixstart] == 0) {
      b3 = TRUE;
    } else {
      b3 = FALSE;
    }

    if (!b3) {
      b_y = TRUE;
      exitg2 = 1U;
    } else {
      ixstart++;
    }
  }

  if (!b_y) {
    on_sizes[0] = 10;
    on_sizes[1] = 2;
    for (ix = 0; ix < 20; ix++) {
      in[ix] = FALSE;
      on_data[ix] = FALSE;
    }
  } else {
    /* [xv, yv] = close_loops(xv, yv); */
    /*  Issue a warning if the bounding box is outside the modeling world that  */
    /*  we can accurately represent. */
    idx = 0;
    for (ix = 0; ix < 2; ix++) {
      ii_sizes[ix] = 1 + 19 * ix;
    }

    ixstart = 1;
    exitg1 = 0U;
    while ((exitg1 == 0U) && (ixstart < 21)) {
      guard1 = FALSE;
      if (mask[ixstart - 1]) {
        idx++;
        ii_data[idx - 1] = ixstart;
        if (idx >= 20) {
          exitg1 = 1U;
        } else {
          guard1 = TRUE;
        }
      } else {
        guard1 = TRUE;
      }

      if (guard1 == TRUE) {
        ixstart++;
      }
    }

    if (1 > idx) {
      idx = 0;
    }

    loop_ub = idx - 1;
    for (ix = 0; ix <= loop_ub; ix++) {
      tmp_data[ix] = 1 + ix;
    }

    loop_ub = idx - 1;
    for (ix = 0; ix <= loop_ub; ix++) {
      ixstart = 0;
      while (ixstart <= 0) {
        b_ii_data[ix] = (int8_T)ii_data[tmp_data[ix] - 1];
        ixstart = 1;
      }
    }

    ii_sizes[0] = 1;
    ii_sizes[1] = idx;
    loop_ub = idx - 1;
    for (ix = 0; ix <= loop_ub; ix++) {
      ii_data[ix] = (int32_T)b_ii_data[ix];
    }

    loop_ub = ii_sizes[1] - 1;
    for (ix = 0; ix <= loop_ub; ix++) {
      inbounds_data[ix] = (int8_T)ii_data[ix];
    }

    e_eml_li_find(mask, ii_data, ii_sizes);
    x_sizes[0] = 1;
    x_sizes[1] = ii_sizes[1];
    loop_ub = ii_sizes[0] * ii_sizes[1] - 1;
    for (ix = 0; ix <= loop_ub; ix++) {
      x_data[ix] = x[ii_data[ix] - 1];
    }

    e_eml_li_find(mask, ii_data, ii_sizes);
    y_sizes[0] = 1;
    y_sizes[1] = ii_sizes[1];
    loop_ub = ii_sizes[0] * ii_sizes[1] - 1;
    for (ix = 0; ix <= loop_ub; ix++) {
      y_data[ix] = y[ii_data[ix] - 1];
    }

    /*  Choose block_length to keep memory usage of vec_inpolygon around */
    /*  10 Megabytes. */
    b_vec_inpolygon(x_data, x_sizes, y_data, y_sizes, xv, yv, in_data, ii_sizes,
                    b_on_data, b_on_sizes);
    on_sizes[0] = 1;
    on_sizes[1] = b_on_sizes[1];
    loop_ub = b_on_sizes[0] * b_on_sizes[1] - 1;
    for (ix = 0; ix <= loop_ub; ix++) {
      on_data[ix] = b_on_data[ix];
    }

    for (ix = 0; ix < 20; ix++) {
      onmask[ix] = mask[ix];
    }

    c_on_sizes[0] = 1;
    c_on_sizes[1] = on_sizes[1];
    loop_ub = on_sizes[1] - 1;
    for (ix = 0; ix <= loop_ub; ix++) {
      b_on_data[ix] = !on_data[ix];
    }

    h_eml_li_find(b_on_data, c_on_sizes, tmp_data, *(int32_T (*)[1])&ixstart);
    loop_ub = ixstart - 1;
    for (ix = 0; ix <= loop_ub; ix++) {
      b_tmp_data[ix] = inbounds_data[tmp_data[ix] - 1];
    }

    loop_ub = ixstart - 1;
    for (ix = 0; ix <= loop_ub; ix++) {
      onmask[b_tmp_data[ix] - 1] = FALSE;
    }

    on_sizes[0] = 10;
    on_sizes[1] = 2;
    for (ixstart = 0; ixstart < 20; ixstart++) {
      on_data[ixstart] = onmask[ixstart];
    }

    in_sizes[0] = 1;
    in_sizes[1] = ii_sizes[1];
    loop_ub = ii_sizes[0] * ii_sizes[1] - 1;
    for (ix = 0; ix <= loop_ub; ix++) {
      b_on_data[ix] = !in_data[ix];
    }

    d_eml_li_find(b_on_data, in_sizes, ii_data, ii_sizes);
    loop_ub = ii_sizes[0] * ii_sizes[1] - 1;
    for (ix = 0; ix <= loop_ub; ix++) {
      c_tmp_data[ix] = inbounds_data[ii_data[ix] - 1];
    }

    loop_ub = ii_sizes[1] - 1;
    for (ix = 0; ix <= loop_ub; ix++) {
      mask[c_tmp_data[ix] - 1] = FALSE;
    }

    /*  Reshape output matrix. */
    for (ixstart = 0; ixstart < 20; ixstart++) {
      in[ixstart] = mask[ixstart];
    }
  }
}

/* End of code generation (myinpolygon1.c) */
