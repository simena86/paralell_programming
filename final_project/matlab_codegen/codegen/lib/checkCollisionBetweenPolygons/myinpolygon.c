/*
 * myinpolygon.c
 *
 * Code generation for function 'myinpolygon'
 *
 * C source code generated on: Fri Mar  1 11:27:49 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "checkCollisionBetweenPolygons.h"
#include "myinpolygon.h"
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
static void b_eml_li_find(const boolean_T x_data[100], const int32_T x_sizes[2],
  int32_T y_data[100], int32_T y_sizes[1]);
static void c_eml_li_find(const boolean_T x_data[90], const int32_T x_sizes[2],
  int32_T y_data[90], int32_T y_sizes[1]);
static void eml_li_find(const boolean_T x[10], int32_T y_data[10], int32_T
  y_sizes[2]);
static void vec_inpolygon(const real_T x_data[10], const int32_T x_sizes[2],
  const real_T y_data[10], const int32_T y_sizes[2], const real_T xv[10], const
  real_T yv[10], boolean_T in_data[10], int32_T in_sizes[2]);

/* Function Definitions */
static void b_eml_li_find(const boolean_T x_data[100], const int32_T x_sizes[2],
  int32_T y_data[100], int32_T y_sizes[1])
{
  int32_T n;
  int32_T k;
  int32_T i;
  n = 10 * x_sizes[1];
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

static void c_eml_li_find(const boolean_T x_data[90], const int32_T x_sizes[2],
  int32_T y_data[90], int32_T y_sizes[1])
{
  int32_T n;
  int32_T k;
  int32_T i;
  n = 9 * x_sizes[1];
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

static void eml_li_find(const boolean_T x[10], int32_T y_data[10], int32_T
  y_sizes[2])
{
  int32_T k;
  int32_T i;
  k = 0;
  for (i = 0; i < 10; i++) {
    if (x[i]) {
      k++;
    }
  }

  y_sizes[0] = 1;
  y_sizes[1] = k;
  k = 0;
  for (i = 0; i < 10; i++) {
    if (x[i]) {
      y_data[k] = i + 1;
      k++;
    }
  }
}

static void vec_inpolygon(const real_T x_data[10], const int32_T x_sizes[2],
  const real_T y_data[10], const int32_T y_sizes[2], const real_T xv[10], const
  real_T yv[10], boolean_T in_data[10], int32_T in_sizes[2])
{
  real_T avy[9];
  real_T scaleFactor[9];
  int32_T i;
  real_T avx[9];
  real_T u0;
  real_T u1;
  int32_T loop_ub;
  int32_T i1;
  real_T xv_data[100];
  real_T yv_data[100];
  boolean_T posX_data[100];
  boolean_T posY_data[100];
  boolean_T negX_data[100];
  boolean_T negY_data[100];
  int32_T quad_sizes[2];
  real_T quad_data[100];
  int32_T idx_sizes[2];
  int32_T tmp_sizes;
  int32_T tmp_data[100];
  int32_T b_tmp_data[100];
  int32_T theCrossProd_sizes[2];
  real_T theCrossProd_data[90];
  int32_T signCrossProduct_sizes[2];
  real_T signCrossProduct_data[90];
  real_T diffQuad_data[90];
  int32_T diffQuad_sizes[2];
  boolean_T idx_data[90];
  int32_T c_tmp_data[90];
  int32_T d_tmp_data[90];
  int32_T e_tmp_data[90];
  real_T A_data[380];
  real_T f_tmp_data[10];
  int32_T b_signCrossProduct_sizes[2];
  boolean_T on_data[10];

  /* ---------------------------------------------- */
  /*  vectorize the computation. */
  /*  Compute scale factors for eps that are based on the original vertex  */
  /*  locations. This ensures that the test points that lie on the boundary  */
  /*  will be evaluated using an appropriately scaled tolerance. */
  /*  (m and mp1 will be reused for setting up adjacent vertices later on.) */
  for (i = 0; i < 9; i++) {
    avy[i] = 0.5 * (xv[i] + xv[i + 1]);
    scaleFactor[i] = 0.5 * (yv[i] + yv[i + 1]);
  }

  b_abs(avy, avx);
  b_abs(scaleFactor, avy);
  for (i = 0; i < 9; i++) {
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
  for (i1 = 0; i1 <= loop_ub; i1++) {
    for (i = 0; i < 10; i++) {
      xv_data[i + 10 * i1] = xv[i] - x_data[x_sizes[0] * i1];
    }
  }

  loop_ub = x_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    for (i = 0; i < 10; i++) {
      yv_data[i + 10 * i1] = yv[i] - y_data[y_sizes[0] * i1];
    }
  }

  /*  Compute the quadrant number for the vertices relative */
  /*  to the test points. */
  loop_ub = 10 * x_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    posX_data[i1] = (xv_data[i1] > 0.0);
  }

  loop_ub = 10 * x_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    posY_data[i1] = (yv_data[i1] > 0.0);
  }

  loop_ub = 10 * x_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    negX_data[i1] = !posX_data[i1];
  }

  loop_ub = 10 * x_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    negY_data[i1] = !posY_data[i1];
  }

  quad_sizes[0] = 10;
  quad_sizes[1] = x_sizes[1];
  loop_ub = 10 * x_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    quad_data[i1] = ((real_T)(negX_data[i1] && posY_data[i1]) + 2.0 * (real_T)
                     (negX_data[i1] && negY_data[i1])) + 3.0 * (real_T)
      (posX_data[i1] && negY_data[i1]);
  }

  /*  Ignore crossings between distinct edge loops that are separated by NaNs */
  loop_ub = 10 * x_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    posX_data[i1] = rtIsNaN(xv_data[i1]);
  }

  loop_ub = 10 * x_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    posY_data[i1] = rtIsNaN(yv_data[i1]);
  }

  idx_sizes[0] = 10;
  idx_sizes[1] = x_sizes[1];
  loop_ub = 10 * x_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    negX_data[i1] = (posX_data[i1] || posY_data[i1]);
  }

  b_eml_li_find(negX_data, idx_sizes, tmp_data, *(int32_T (*)[1])&tmp_sizes);
  loop_ub = tmp_sizes - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    b_tmp_data[i1] = tmp_data[i1];
  }

  loop_ub = tmp_sizes - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    quad_data[b_tmp_data[i1] - 1] = rtNaN;
  }

  /*  Compute the sign() of the cross product and dot product */
  /*  of adjacent vertices. */
  theCrossProd_sizes[0] = 9;
  theCrossProd_sizes[1] = x_sizes[1];
  loop_ub = x_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    for (i = 0; i < 9; i++) {
      theCrossProd_data[i + 9 * i1] = xv_data[i + 10 * i1] * yv_data[(i + 10 *
        i1) + 1] - xv_data[(i + 10 * i1) + 1] * yv_data[i + 10 * i1];
    }
  }

  signCrossProduct_sizes[0] = 9;
  signCrossProduct_sizes[1] = theCrossProd_sizes[1];
  loop_ub = 9 * theCrossProd_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    signCrossProduct_data[i1] = theCrossProd_data[i1];
  }

  b_sign(signCrossProduct_data, signCrossProduct_sizes);

  /*  Adjust values that are within epsilon of the polygon boundary. */
  /*  Making epsilon larger will treat points close to the boundary as  */
  /*  being "on" the boundary. A factor of 3 was found from experiment to be */
  /*  a good margin to hedge against roundoff. */
  diffQuad_sizes[0] = 9;
  diffQuad_sizes[1] = theCrossProd_sizes[1];
  loop_ub = 9 * theCrossProd_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    diffQuad_data[i1] = theCrossProd_data[i1];
  }

  c_abs(diffQuad_data, diffQuad_sizes, theCrossProd_data, theCrossProd_sizes);
  for (i = 0; i < 9; i++) {
    avy[i] = scaleFactor[i] * 2.2204460492503131E-16 * 3.0;
  }

  bsxfun(theCrossProd_data, theCrossProd_sizes, avy, idx_data, idx_sizes);
  c_eml_li_find(idx_data, idx_sizes, c_tmp_data, *(int32_T (*)[1])&tmp_sizes);
  loop_ub = tmp_sizes - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    d_tmp_data[i1] = c_tmp_data[i1];
  }

  loop_ub = tmp_sizes - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    signCrossProduct_data[d_tmp_data[i1] - 1] = 0.0;
  }

  /*  Compute the vertex quadrant changes for each test point. */
  diff(quad_data, quad_sizes, diffQuad_data, diffQuad_sizes);

  /*  Fix up the quadrant differences.  Replace 3 by -1 and -3 by 1. */
  /*  Any quadrant difference with an absolute value of 2 should have */
  /*  the same sign as the cross product. */
  c_abs(diffQuad_data, diffQuad_sizes, theCrossProd_data, theCrossProd_sizes);
  idx_sizes[0] = 9;
  idx_sizes[1] = theCrossProd_sizes[1];
  loop_ub = theCrossProd_sizes[0] * theCrossProd_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    idx_data[i1] = (theCrossProd_data[i1] == 3.0);
  }

  c_eml_li_find(idx_data, idx_sizes, c_tmp_data, *(int32_T (*)[1])&tmp_sizes);
  c_eml_li_find(idx_data, idx_sizes, d_tmp_data, *(int32_T (*)[1])&i);
  loop_ub = i - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    e_tmp_data[i1] = d_tmp_data[i1];
  }

  loop_ub = tmp_sizes - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    A_data[i1] = -diffQuad_data[c_tmp_data[i1] - 1];
  }

  loop_ub = tmp_sizes - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    diffQuad_data[e_tmp_data[i1] - 1] = A_data[i1] / 3.0;
  }

  c_abs(diffQuad_data, diffQuad_sizes, theCrossProd_data, theCrossProd_sizes);
  idx_sizes[0] = 9;
  idx_sizes[1] = theCrossProd_sizes[1];
  loop_ub = theCrossProd_sizes[0] * theCrossProd_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    idx_data[i1] = (theCrossProd_data[i1] == 2.0);
  }

  c_eml_li_find(idx_data, idx_sizes, c_tmp_data, *(int32_T (*)[1])&tmp_sizes);
  c_eml_li_find(idx_data, idx_sizes, d_tmp_data, *(int32_T (*)[1])&i);
  loop_ub = i - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    e_tmp_data[i1] = d_tmp_data[i1];
  }

  loop_ub = tmp_sizes - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    diffQuad_data[e_tmp_data[i1] - 1] = 2.0 *
      signCrossProduct_data[c_tmp_data[i1] - 1];
  }

  /*  Find the inside points. */
  /*  Ignore crossings between distinct loops that are separated by NaNs */
  idx_sizes[0] = 9;
  idx_sizes[1] = diffQuad_sizes[1];
  loop_ub = diffQuad_sizes[0] * diffQuad_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    idx_data[i1] = rtIsNaN(diffQuad_data[i1]);
  }

  c_eml_li_find(idx_data, idx_sizes, c_tmp_data, *(int32_T (*)[1])&tmp_sizes);
  loop_ub = tmp_sizes - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    d_tmp_data[i1] = c_tmp_data[i1];
  }

  loop_ub = tmp_sizes - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    diffQuad_data[d_tmp_data[i1] - 1] = 0.0;
  }

  sum(diffQuad_data, diffQuad_sizes, f_tmp_data, idx_sizes);
  in_sizes[0] = 1;
  in_sizes[1] = idx_sizes[1];
  loop_ub = idx_sizes[0] * idx_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    in_data[i1] = (f_tmp_data[i1] != 0.0);
  }

  /*  Find the points on the polygon.  If the cross product is 0 and */
  /*  the dot product is nonpositive anywhere, then the corresponding */
  /*  point must be on the contour. */
  b_signCrossProduct_sizes[0] = 9;
  b_signCrossProduct_sizes[1] = signCrossProduct_sizes[1];
  loop_ub = signCrossProduct_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    for (i = 0; i < 9; i++) {
      idx_data[i + 9 * i1] = ((signCrossProduct_data[i + signCrossProduct_sizes
        [0] * i1] == 0.0) && (xv_data[i + 10 * i1] * xv_data[(i + 10 * i1) + 1]
        + yv_data[i + 10 * i1] * yv_data[(i + 10 * i1) + 1] <= 0.0));
    }
  }

  any(idx_data, b_signCrossProduct_sizes, on_data, idx_sizes);
  in_sizes[0] = 1;
  loop_ub = in_sizes[1] - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    in_data[i1] = (in_data[i1] || on_data[i1]);
  }
}

void b_myinpolygon(const real_T x[10], const real_T y[10], real_T xv[10], real_T
                   yv[10], boolean_T in[10])
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
  boolean_T mask[10];
  boolean_T b_y;
  boolean_T exitg2;
  boolean_T b1;
  int32_T idx;
  int32_T ii_data[10];
  int32_T ii_sizes[2];
  boolean_T exitg1;
  boolean_T guard1 = FALSE;
  int32_T tmp_data[10];
  int8_T b_ii_data[10];
  int32_T i0;
  int8_T inbounds_data[10];
  int32_T x_sizes[2];
  real_T x_data[10];
  int32_T y_sizes[2];
  real_T y_data[10];
  int32_T in_sizes[2];
  boolean_T in_data[10];
  boolean_T b_in_data[20];
  int32_T b_in_sizes[2];
  int32_T b_tmp_data[20];

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
    while ((exitg6 == 0U) && (ix < 11)) {
      ixstart = ix;
      if (!rtIsNaN(xv[ix - 1])) {
        mtmp = xv[ix - 1];
        exitg6 = 1U;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 10) {
    while (ixstart + 1 < 11) {
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
    while ((exitg5 == 0U) && (ix < 11)) {
      ixstart = ix;
      if (!rtIsNaN(xv[ix - 1])) {
        b_mtmp = xv[ix - 1];
        exitg5 = 1U;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 10) {
    while (ixstart + 1 < 11) {
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
    while ((exitg4 == 0U) && (ix < 11)) {
      ixstart = ix;
      if (!rtIsNaN(yv[ix - 1])) {
        c_mtmp = yv[ix - 1];
        exitg4 = 1U;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 10) {
    while (ixstart + 1 < 11) {
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
    while ((exitg3 == 0U) && (ix < 11)) {
      ixstart = ix;
      if (!rtIsNaN(yv[ix - 1])) {
        d_mtmp = yv[ix - 1];
        exitg3 = 1U;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 10) {
    while (ixstart + 1 < 11) {
      if (yv[ixstart] > d_mtmp) {
        d_mtmp = yv[ixstart];
      }

      ixstart++;
    }
  }

  for (ixstart = 0; ixstart < 10; ixstart++) {
    mask[ixstart] = ((x[ixstart] >= mtmp) && (x[ixstart] <= b_mtmp) &&
                     (y[ixstart] >= c_mtmp) && (y[ixstart] <= d_mtmp));
  }

  b_y = FALSE;
  ixstart = 0;
  exitg2 = 0U;
  while ((exitg2 == 0U) && (ixstart < 10)) {
    if (mask[ixstart] == 0) {
      b1 = TRUE;
    } else {
      b1 = FALSE;
    }

    if (!b1) {
      b_y = TRUE;
      exitg2 = 1U;
    } else {
      ixstart++;
    }
  }

  if (!b_y) {
    for (ixstart = 0; ixstart < 10; ixstart++) {
      in[ixstart] = FALSE;
    }
  } else {
    /* [xv, yv] = close_loops(xv, yv); */
    /*  Issue a warning if the bounding box is outside the modeling world that  */
    /*  we can accurately represent. */
    idx = 0;
    for (ixstart = 0; ixstart < 2; ixstart++) {
      ii_sizes[ixstart] = 1 + 9 * ixstart;
    }

    ixstart = 1;
    exitg1 = 0U;
    while ((exitg1 == 0U) && (ixstart < 11)) {
      guard1 = FALSE;
      if (mask[ixstart - 1]) {
        idx++;
        ii_data[idx - 1] = ixstart;
        if (idx >= 10) {
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

    ix = idx - 1;
    for (ixstart = 0; ixstart <= ix; ixstart++) {
      tmp_data[ixstart] = 1 + ixstart;
    }

    ix = idx - 1;
    for (ixstart = 0; ixstart <= ix; ixstart++) {
      i0 = 0;
      while (i0 <= 0) {
        b_ii_data[ixstart] = (int8_T)ii_data[tmp_data[ixstart] - 1];
        i0 = 1;
      }
    }

    ii_sizes[0] = 1;
    ii_sizes[1] = idx;
    ix = idx - 1;
    for (ixstart = 0; ixstart <= ix; ixstart++) {
      ii_data[ixstart] = (int32_T)b_ii_data[ixstart];
    }

    ix = ii_sizes[1] - 1;
    for (ixstart = 0; ixstart <= ix; ixstart++) {
      inbounds_data[ixstart] = (int8_T)ii_data[ixstart];
    }

    eml_li_find(mask, ii_data, ii_sizes);
    x_sizes[0] = 1;
    x_sizes[1] = ii_sizes[1];
    ix = ii_sizes[0] * ii_sizes[1] - 1;
    for (ixstart = 0; ixstart <= ix; ixstart++) {
      x_data[ixstart] = x[ii_data[ixstart] - 1];
    }

    eml_li_find(mask, ii_data, ii_sizes);
    y_sizes[0] = 1;
    y_sizes[1] = ii_sizes[1];
    ix = ii_sizes[0] * ii_sizes[1] - 1;
    for (ixstart = 0; ixstart <= ix; ixstart++) {
      y_data[ixstart] = y[ii_data[ixstart] - 1];
    }

    /*  Choose block_length to keep memory usage of vec_inpolygon around */
    /*  10 Megabytes. */
    vec_inpolygon(x_data, x_sizes, y_data, y_sizes, xv, yv, in_data, in_sizes);
    b_in_sizes[0] = 1;
    b_in_sizes[1] = in_sizes[1];
    ix = in_sizes[0] * in_sizes[1] - 1;
    for (ixstart = 0; ixstart <= ix; ixstart++) {
      b_in_data[ixstart] = !in_data[ixstart];
    }

    d_eml_li_find(b_in_data, b_in_sizes, b_tmp_data, x_sizes);
    ii_sizes[0] = 1;
    ii_sizes[1] = x_sizes[1];
    ix = x_sizes[0] * x_sizes[1] - 1;
    for (ixstart = 0; ixstart <= ix; ixstart++) {
      ii_data[ixstart] = (int32_T)inbounds_data[b_tmp_data[ixstart] - 1];
    }

    ix = ii_sizes[1] - 1;
    for (ixstart = 0; ixstart <= ix; ixstart++) {
      mask[ii_data[ixstart] - 1] = FALSE;
    }

    /*  Reshape output matrix. */
    for (ixstart = 0; ixstart < 10; ixstart++) {
      in[ixstart] = mask[ixstart];
    }
  }
}

void d_eml_li_find(const boolean_T x_data[20], const int32_T x_sizes[2], int32_T
                   y_data[20], int32_T y_sizes[2])
{
  int32_T k;
  int32_T i;
  k = 0;
  for (i = 1; i <= x_sizes[1]; i++) {
    if (x_data[i - 1]) {
      k++;
    }
  }

  y_sizes[0] = 1;
  y_sizes[1] = k;
  k = 0;
  for (i = 1; i <= x_sizes[1]; i++) {
    if (x_data[i - 1]) {
      y_data[k] = i;
      k++;
    }
  }
}

/* End of code generation (myinpolygon.c) */
