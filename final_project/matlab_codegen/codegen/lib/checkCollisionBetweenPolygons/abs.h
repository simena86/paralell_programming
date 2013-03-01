/*
 * abs.h
 *
 * Code generation for function 'abs'
 *
 * C source code generated on: Fri Mar  1 11:27:49 2013
 *
 */

#ifndef __ABS_H__
#define __ABS_H__
/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"

#include "rtwtypes.h"
#include "checkCollisionBetweenPolygons_types.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern void b_abs(const real_T x[9], real_T y[9]);
extern void c_abs(const real_T x_data[90], const int32_T x_sizes[2], real_T y_data[90], int32_T y_sizes[2]);
extern void d_abs(const real_T x[19], real_T y[19]);
extern void e_abs(const real_T x_data[380], const int32_T x_sizes[2], real_T y_data[380], int32_T y_sizes[2]);
#endif
/* End of code generation (abs.h) */
