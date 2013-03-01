/*
 * bsxfun.c
 *
 * Code generation for function 'bsxfun'
 *
 * C source code generated on: Fri Mar  1 11:27:49 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "checkCollisionBetweenPolygons.h"
#include "myinpolygon.h"
#include "bsxfun.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void b_bsxfun(const real_T a_data[380], const int32_T a_sizes[2], const real_T
              b[19], boolean_T c_data[380], int32_T c_sizes[2])
{
  int8_T csz[2];
  int32_T i6;
  int32_T asub;
  int32_T ak;
  int32_T ck;
  boolean_T cv[19];
  int32_T k;
  for (i6 = 0; i6 < 2; i6++) {
    csz[i6] = 0;
  }

  csz[0] = 19;
  csz[1] = (int8_T)a_sizes[1];
  c_sizes[0] = 19;
  c_sizes[1] = (int32_T)csz[1];
  asub = 1;
  ak = 0;
  i6 = 19 * c_sizes[1] - 19;
  for (ck = 0; ck <= i6; ck += 19) {
    for (k = 0; k < 19; k++) {
      cv[k] = (a_data[ak + k] < b[k]);
    }

    for (k = 0; k < 19; k++) {
      c_data[ck + k] = cv[k];
    }

    if (asub < a_sizes[1]) {
      ak += 19;
      asub++;
    } else {
      asub = 1;
    }
  }
}

void bsxfun(const real_T a_data[90], const int32_T a_sizes[2], const real_T b[9],
            boolean_T c_data[90], int32_T c_sizes[2])
{
  int8_T csz[2];
  int32_T i3;
  int32_T asub;
  int32_T ak;
  int32_T ck;
  boolean_T cv[9];
  int32_T k;
  for (i3 = 0; i3 < 2; i3++) {
    csz[i3] = 0;
  }

  csz[0] = 9;
  csz[1] = (int8_T)a_sizes[1];
  c_sizes[0] = 9;
  c_sizes[1] = (int32_T)csz[1];
  asub = 1;
  ak = 0;
  i3 = 9 * c_sizes[1] - 9;
  for (ck = 0; ck <= i3; ck += 9) {
    for (k = 0; k < 9; k++) {
      cv[k] = (a_data[ak + k] < b[k]);
    }

    for (k = 0; k < 9; k++) {
      c_data[ck + k] = cv[k];
    }

    if (asub < a_sizes[1]) {
      ak += 9;
      asub++;
    } else {
      asub = 1;
    }
  }
}

/* End of code generation (bsxfun.c) */
