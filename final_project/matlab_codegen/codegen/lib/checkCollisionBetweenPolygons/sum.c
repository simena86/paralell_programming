/*
 * sum.c
 *
 * Code generation for function 'sum'
 *
 * C source code generated on: Fri Mar  1 11:27:49 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "checkCollisionBetweenPolygons.h"
#include "myinpolygon.h"
#include "sum.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void b_sum(const real_T x_data[380], const int32_T x_sizes[2], real_T y_data[20],
           int32_T y_sizes[2])
{
  int8_T sz[2];
  int32_T ixstart;
  int32_T k;
  int32_T ix;
  int32_T iy;
  int32_T i;
  real_T s;
  for (ixstart = 0; ixstart < 2; ixstart++) {
    sz[ixstart] = (int8_T)x_sizes[ixstart];
  }

  sz[0] = 1;
  y_sizes[0] = 1;
  y_sizes[1] = (int32_T)sz[1];
  if (x_sizes[1] == 0) {
    y_sizes[0] = 1;
    k = y_sizes[1] - 1;
    for (ixstart = 0; ixstart <= k; ixstart++) {
      y_data[ixstart] = 0.0;
    }
  } else {
    ix = -1;
    iy = -1;
    for (i = 1; i <= x_sizes[1]; i++) {
      ixstart = ix + 1;
      ix++;
      s = x_data[ixstart];
      for (k = 0; k < 18; k++) {
        ix++;
        s += x_data[ix];
      }

      iy++;
      y_data[iy] = s;
    }
  }
}

void sum(const real_T x_data[90], const int32_T x_sizes[2], real_T y_data[10],
         int32_T y_sizes[2])
{
  int8_T sz[2];
  int32_T ixstart;
  int32_T k;
  int32_T ix;
  int32_T iy;
  int32_T i;
  real_T s;
  for (ixstart = 0; ixstart < 2; ixstart++) {
    sz[ixstart] = (int8_T)x_sizes[ixstart];
  }

  sz[0] = 1;
  y_sizes[0] = 1;
  y_sizes[1] = (int32_T)sz[1];
  if (x_sizes[1] == 0) {
    y_sizes[0] = 1;
    k = y_sizes[1] - 1;
    for (ixstart = 0; ixstart <= k; ixstart++) {
      y_data[ixstart] = 0.0;
    }
  } else {
    ix = -1;
    iy = -1;
    for (i = 1; i <= x_sizes[1]; i++) {
      ixstart = ix + 1;
      ix++;
      s = x_data[ixstart];
      for (k = 0; k < 8; k++) {
        ix++;
        s += x_data[ix];
      }

      iy++;
      y_data[iy] = s;
    }
  }
}

/* End of code generation (sum.c) */
