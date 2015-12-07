#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdlib.h>
#include <stdio.h>

#define min(a,b) ((a < b) ? a : b)
#define abs(x)   (x < 0 ? -x : x)

typedef double **matrix;
typedef double *vect;

/* Basic operations */

matrix create_matrix(int row, int col);
void free_matrix(matrix mat, int row);
vect create_vector(int size);
void free_vector(vect v);
void fill_matrix_zero(matrix m, int row, int col);
void fill_vector_zero(vect v, int size);

/* Others operations */

void matrix_mean_row(matrix mat, int row, int col, vect v);
void matrix_transpose(matrix mat, int row, int col, matrix transpose);
void matrix_multiply(matrix m1, int row1, int col1, matrix m2, int row2, int col2, matrix mul);
void matrix_center(matrix mat, int row, int col, vect mean);
int matrix_symetric(matrix mat, int row, int col);

/* Print */

void print_matrix(matrix mat, int row, int col);
void print_vector(vect vector, int size);

#endif
