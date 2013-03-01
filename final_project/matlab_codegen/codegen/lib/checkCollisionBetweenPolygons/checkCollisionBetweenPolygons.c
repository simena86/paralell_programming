/*
 * checkCollisionBetweenPolygons.c
 *
 * Code generation for function 'checkCollisionBetweenPolygons'
 *
 * C source code generated on: Fri Mar  1 11:27:49 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "checkCollisionBetweenPolygons.h"
#include "myinpolygon.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
boolean_T checkCollisionBetweenPolygons(const real_T P1[20], const real_T P2[20])
{
  boolean_T bCollide;
  real_T b_P2[10];
  real_T c_P2[10];
  int32_T k;
  boolean_T in2[10];
  boolean_T y;
  boolean_T exitg4;
  boolean_T b0;
  boolean_T exitg3;
  boolean_T exitg2;
  int32_T r;
  int32_T j;
  int32_T exitg1;
  int32_T b_r;
  real_T den;
  real_T u_a;
  boolean_T guard1 = FALSE;

  /*  Returns a boolean indicating whether two arbitrary polygons collide. */
  /*  Requires to polygons defined as n-by-2 arrays of counterclockwise points. */
  /*  Function first tests whether any vertices of one polygon are inside the */
  /*  other, then checks for intersection of segments. */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Intro to Robotics, ME170A/ECE181A, Spring 2009 */
  /*  Joey Durham */
  /*  April 21, 2009 */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  bCollide = FALSE;

  /*  First, check if any vertex of P1 is inside P2 */
  for (k = 0; k < 10; k++) {
    b_P2[k] = P2[k];
    c_P2[k] = P2[10 + k];
  }

  b_myinpolygon(*(real_T (*)[10])&P1[0], *(real_T (*)[10])&P1[10], b_P2, c_P2,
                in2);
  y = FALSE;
  k = 0;
  exitg4 = 0U;
  while ((exitg4 == 0U) && (k < 10)) {
    if (in2[k] == 0) {
      b0 = TRUE;
    } else {
      b0 = FALSE;
    }

    if (!b0) {
      y = TRUE;
      exitg4 = 1U;
    } else {
      k++;
    }
  }

  if (y) {
    /* fprintf('Vertices in polygon\n'); */
    bCollide = TRUE;
  } else {
    /*  Next, check if any vertex of P2 is inside P1 */
    for (k = 0; k < 10; k++) {
      b_P2[k] = P1[k];
      c_P2[k] = P1[10 + k];
    }

    b_myinpolygon(*(real_T (*)[10])&P2[0], *(real_T (*)[10])&P2[10], b_P2, c_P2,
                  in2);
    y = FALSE;
    k = 0;
    exitg3 = 0U;
    while ((exitg3 == 0U) && (k < 10)) {
      if (in2[k] == 0) {
        b0 = TRUE;
      } else {
        b0 = FALSE;
      }

      if (!b0) {
        y = TRUE;
        exitg3 = 1U;
      } else {
        k++;
      }
    }

    if (y) {
      bCollide = TRUE;
    } else {
      /*  Finally, loop over all combinations of edges of segments checking for */
      /*  intersection.  s1 and s2 are the endpoints of the ith segment of P1, while t1 */
      /*  and t2 are for the jth segment of P2 */
      k = 0;
      exitg2 = 0U;
      while ((exitg2 == 0U) && (k < 10)) {
        r = (k - (int32_T)floor((1.0 + (real_T)k) / 10.0) * 10) + 1;
        j = 0;
        do {
          exitg1 = 0U;
          if (j < 10) {
            b_r = (j - (int32_T)floor((1.0 + (real_T)j) / 10.0) * 10) + 1;
            den = (P2[10 + b_r] - P2[10 + j]) * (P1[r] - P1[k]) - (P2[b_r] -
              P2[j]) * (P1[10 + r] - P1[10 + k]);
            u_a = (P2[b_r] - P2[j]) * (P1[10 + k] - P2[10 + j]) - (P2[10 + b_r]
              - P2[10 + j]) * (P1[k] - P2[j]);
            guard1 = FALSE;
            if (fabs(den) < 0.001) {
              if (fabs(u_a) < 0.001) {
                /*  Segments are coincident */
                /* fprintf('Coincident segments\n'); */
                bCollide = TRUE;
                exitg1 = 1U;
              } else {
                /*  Segments are parallel and cannot intersect */
                guard1 = TRUE;
              }
            } else {
              u_a /= den;
              den = ((P1[r] - P1[k]) * (P1[10 + k] - P2[10 + j]) - (P1[10 + r] -
                      P1[10 + k]) * (P1[k] - P2[j])) / den;
              if ((u_a >= 0.0) && (u_a <= 1.0) && (den >= 0.0) && (den <= 1.0))
              {
                /*  Segments intersect */
                /* fprintf('Intersecting segments\n'); */
                bCollide = TRUE;
                exitg1 = 1U;
              } else {
                guard1 = TRUE;
              }
            }

            if (guard1 == TRUE) {
              j++;
            }
          } else {
            k++;
            exitg1 = 2U;
          }
        } while (exitg1 == 0U);

        if (exitg1 == 1U) {
          exitg2 = 1U;
        }
      }
    }
  }

  return bCollide;
}

/* End of code generation (checkCollisionBetweenPolygons.c) */
