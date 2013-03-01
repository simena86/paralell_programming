/*
 * abs.c
 *
 * Code generation for function 'abs'
 *
 * C source code generated on: Fri Mar  1 11:27:49 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "checkCollisionBetweenPolygons.h"
#include "myinpolygon.h"
#include "abs.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void b_abs(const real_T x[9], real_T y[9])
{
  int32_T k;
  for (k = 0; k < 9; k++) {
    y[k] = fabs(x[k]);
  }
}

void c_abs(const real_T x_data[90], const int32_T x_sizes[2], real_T y_data[90],
           int32_T y_sizes[2])
{
  int8_T iv0[2];
  int32_T i2;
  int32_T k;
  for (i2 = 0; i2 < 2; i2++) {
    iv0[i2] = (int8_T)x_sizes[i2];
  }

  y_sizes[0] = 9;
  y_sizes[1] = (int32_T)iv0[1];
  i2 = 9 * x_sizes[1];
  for (k = 0; k <= i2 - 1; k++) {
    y_data[k] = fabs(x_data[k]);
  }
}

void d_abs(const real_T x[19], real_T y[19])
{
  int32_T k;
  for (k = 0; k < 19; k++) {
    y[k] = fabs(x[k]);
  }
}

void e_abs(const real_T x_data[380], const int32_T x_sizes[2], real_T y_data[380],
           int32_T y_sizes[2])
{
  int8_T iv1[2];
  int32_T i5;
  int32_T k;
  for (i5 = 0; i5 < 2; i5++) {
    iv1[i5] = (int8_T)x_sizes[i5];
  }

  y_sizes[0] = 19;
  y_sizes[1] = (int32_T)iv1[1];
  i5 = 19 * x_sizes[1];
  for (k = 0; k <= i5 - 1; k++) {
    y_data[k] = fabs(x_data[k]);
  }
}

/* End of code generation (abs.c) */
