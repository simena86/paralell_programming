/*
 * diff.c
 *
 * Code generation for function 'diff'
 *
 * C source code generated on: Fri Mar  1 11:27:49 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "checkCollisionBetweenPolygons.h"
#include "myinpolygon.h"
#include "diff.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void b_diff(const real_T x_data[400], const int32_T x_sizes[2], real_T y_data
            [380], int32_T y_sizes[2])
{
  int8_T ySize[2];
  int32_T ixStart;
  int32_T iyStart;
  int32_T r;
  int32_T ixLead;
  int32_T iyLead;
  real_T work;
  int32_T m;
  real_T tmp2;
  for (ixStart = 0; ixStart < 2; ixStart++) {
    ySize[ixStart] = (int8_T)x_sizes[ixStart];
  }

  ySize[0] = 19;
  y_sizes[0] = 19;
  y_sizes[1] = (int32_T)ySize[1];
  ixStart = 1;
  iyStart = 0;
  for (r = 1; r <= x_sizes[1]; r++) {
    ixLead = ixStart;
    iyLead = iyStart;
    work = x_data[ixStart - 1];
    for (m = 0; m < 19; m++) {
      tmp2 = work;
      work = x_data[ixLead];
      tmp2 = x_data[ixLead] - tmp2;
      ixLead++;
      y_data[iyLead] = tmp2;
      iyLead++;
    }

    ixStart += 20;
    iyStart += 19;
  }
}

void diff(const real_T x_data[100], const int32_T x_sizes[2], real_T y_data[90],
          int32_T y_sizes[2])
{
  int8_T ySize[2];
  int32_T ixStart;
  int32_T iyStart;
  int32_T r;
  int32_T ixLead;
  int32_T iyLead;
  real_T work;
  int32_T m;
  real_T tmp2;
  for (ixStart = 0; ixStart < 2; ixStart++) {
    ySize[ixStart] = (int8_T)x_sizes[ixStart];
  }

  ySize[0] = 9;
  y_sizes[0] = 9;
  y_sizes[1] = (int32_T)ySize[1];
  ixStart = 1;
  iyStart = 0;
  for (r = 1; r <= x_sizes[1]; r++) {
    ixLead = ixStart;
    iyLead = iyStart;
    work = x_data[ixStart - 1];
    for (m = 0; m < 9; m++) {
      tmp2 = work;
      work = x_data[ixLead];
      tmp2 = x_data[ixLead] - tmp2;
      ixLead++;
      y_data[iyLead] = tmp2;
      iyLead++;
    }

    ixStart += 10;
    iyStart += 9;
  }
}

/* End of code generation (diff.c) */
