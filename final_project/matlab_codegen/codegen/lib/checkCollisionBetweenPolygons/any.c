/*
 * any.c
 *
 * Code generation for function 'any'
 *
 * C source code generated on: Fri Mar  1 11:27:49 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "checkCollisionBetweenPolygons.h"
#include "myinpolygon.h"
#include "any.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void any(const boolean_T x_data[90], const int32_T x_sizes[2], boolean_T y_data
         [10], int32_T y_sizes[2])
{
  int8_T outsize[2];
  int32_T i2;
  int32_T iy;
  int32_T i;
  int32_T i1;
  boolean_T exitg1;
  boolean_T b2;
  for (i2 = 0; i2 < 2; i2++) {
    outsize[i2] = (int8_T)x_sizes[i2];
  }

  outsize[0] = 1;
  y_sizes[0] = 1;
  y_sizes[1] = (int32_T)outsize[1];
  iy = outsize[1] - 1;
  for (i2 = 0; i2 <= iy; i2++) {
    y_data[i2] = FALSE;
  }

  i2 = 0;
  iy = -1;
  for (i = 1; i <= x_sizes[1]; i++) {
    i1 = i2 + 1;
    i2 += 9;
    iy++;
    exitg1 = 0U;
    while ((exitg1 == 0U) && (i1 <= i2)) {
      if (x_data[i1 - 1] == 0) {
        b2 = TRUE;
      } else {
        b2 = FALSE;
      }

      if (!b2) {
        y_data[iy] = TRUE;
        exitg1 = 1U;
      } else {
        i1++;
      }
    }
  }
}

void b_any(const boolean_T x_data[380], const int32_T x_sizes[2], boolean_T
           y_data[20], int32_T y_sizes[2])
{
  int8_T outsize[2];
  int32_T i2;
  int32_T iy;
  int32_T i;
  int32_T i1;
  boolean_T exitg1;
  boolean_T b4;
  for (i2 = 0; i2 < 2; i2++) {
    outsize[i2] = (int8_T)x_sizes[i2];
  }

  outsize[0] = 1;
  y_sizes[0] = 1;
  y_sizes[1] = (int32_T)outsize[1];
  iy = outsize[1] - 1;
  for (i2 = 0; i2 <= iy; i2++) {
    y_data[i2] = FALSE;
  }

  i2 = 0;
  iy = -1;
  for (i = 1; i <= x_sizes[1]; i++) {
    i1 = i2 + 1;
    i2 += 19;
    iy++;
    exitg1 = 0U;
    while ((exitg1 == 0U) && (i1 <= i2)) {
      if (x_data[i1 - 1] == 0) {
        b4 = TRUE;
      } else {
        b4 = FALSE;
      }

      if (!b4) {
        y_data[iy] = TRUE;
        exitg1 = 1U;
      } else {
        i1++;
      }
    }
  }
}

/* End of code generation (any.c) */
