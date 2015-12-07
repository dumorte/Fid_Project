#include "matrix.h"

/* Basic operations */

matrix create_matrix(int row, int col){
	matrix m = (matrix) malloc(row * sizeof(vect));

	for(int i = 0; i < row; i++){
		m[i] = (vect) malloc(col * sizeof(double));
	}

	return m;
}

void free_matrix(matrix mat, int row){
	for(int i = 0; i < row; i++)
		free(mat[i]);

	free(mat);
	mat = NULL;
}

vect create_vector(int size){
	vect v = (vect) malloc(size * sizeof(double));

	return v;
}

void free_vector(vect v){
	free(v);
	v = NULL;
}

void fill_matrix_zero(matrix m, int row, int col){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			m[i][j] = 0;
		}
	}
}

void fill_vector_zero(vect v, int size){
	for(int i = 0; i < size; i++)
		v[i] = 0;
}

/* Others operations */

void matrix_mean_row(matrix mat, int row, int col, vect v){
	double sum;

	for(int i = 0; i < row; i++){
		sum = 0; 
		for(int j = 0; j < col; j++)
			sum += mat[i][j];
		v[i] = sum / col;
	}
}

void matrix_transpose(matrix mat, int row, int col, matrix transpose){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			transpose[j][i] = mat[i][j];
		}
	}
}

void matrix_multiply(matrix m1, int row1, int col1, matrix m2, int row2, int col2, matrix mul){
	fill_matrix_zero(mul, row1, col2);

	if(col1 != row2)
		return;

	for(int i = 0; i < row1; i++)
		for(int j = 0; j < col2; j++)
			for(int k = 0; k < col1; k++)
				mul[i][j] += m1[i][k] * m2[k][j];
}

void matrix_center(matrix mat, int row, int col, vect mean){
	fill_vector_zero(mean, col);

	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			mean[j] += mat[i][j];

	for(int i = 0; i < col; i++)
		mean[i] /= row;

	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			mat[i][j] -= mean[j];
}

int matrix_symetric(matrix mat, int row, int col){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(mat[i][j] != mat[j][i])
				return 0;
		}
	}

	return 1;
}

/* Print */

void print_matrix(matrix mat, int row, int col){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			printf("%0.6f", mat[i][j]);
			if(j < col - 1)
				printf(" | ");
		}
		printf("\n");
	}
}

void print_vector(vect vector, int size){
	for(int i = 0; i < size; i++){
		printf("%0.6f | ", vector[i]);
	}
}
