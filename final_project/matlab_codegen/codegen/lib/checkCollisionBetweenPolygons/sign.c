/*
 * sign.c
 *
 * Code generation for function 'sign'
 *
 * C source code generated on: Fri Mar  1 11:27:49 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "checkCollisionBetweenPolygons.h"
#include "myinpolygon.h"
#include "sign.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void b_sign(real_T x_data[90], int32_T x_sizes[2])
{
  int32_T i7;
  int32_T k;
  real_T x;
  i7 = 9 * x_sizes[1];
  for (k = 0; k <= i7 - 1; k++) {
    x = x_data[k];
    if (x_data[k] > 0.0) {
      x = 1.0;
    } else if (x_data[k] < 0.0) {
      x = -1.0;
    } else {
      if (x_data[k] == 0.0) {
        x = 0.0;
      }
    }

    x_data[k] = x;
  }
}

void c_sign(real_T x_data[380], int32_T x_sizes[2])
{
  int32_T i8;
  int32_T k;
  real_T x;
  i8 = 19 * x_sizes[1];
  for (k = 0; k <= i8 - 1; k++) {
    x = x_data[k];
    if (x_data[k] > 0.0) {
      x = 1.0;
    } else if (x_data[k] < 0.0) {
      x = -1.0;
    } else {
      if (x_data[k] == 0.0) {
        x = 0.0;
      }
    }

    x_data[k] = x;
  }
}

/* End of code generation (sign.c) */
