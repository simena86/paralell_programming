/**
 * Matrix Multiply API
 *
 **/

#ifndef MATRIX_MULTIPLY_H_INCLUDED

#define MATRIX_MULTIPLY_H_INCLUDED

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <assert.h>
//#include <Accelerate/Accelerate.h>
//#include <cblas.h>

typedef struct {
  int rows;
  int cols;
  int colstride;
  double *values;
} matrix_t;

#define element(X,i,j) (X)->values[(i) + (j)*(X)->colstride]

int matrix_multiply_run_1(matrix_t *A, matrix_t *B, matrix_t *C);
int matrix_multiply_run_2(matrix_t *A, matrix_t *B, matrix_t *C);

matrix_t * make_matrix(int rows, int cols);
void free_matrix(matrix_t *m);
void print_matrix(matrix_t *m);
int check_answer(matrix_t *A, matrix_t *B, matrix_t *C);

double elapsed_seconds();



#endif
