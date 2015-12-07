#include "eigenface.h"

vect eigenvalue(SDL_Surface **img_set, int columns){
	Uint8 grey;
	int width = img_set[0]->w;
	int height = img_set[0]->h;
	matrix mat = create_matrix(width*height, columns);
	matrix transpose = create_matrix(columns, width*height);
	matrix mul = create_matrix(width*height, width*height);
	vect eigenvalues = create_vector(width*height);
	matrix V = create_matrix(width*height, width*height);

	for(int i = 0; i < columns; i++){
		int row = 0;
		for(int j = 0; j < width; j++){
			for(int k = 0; k < height; k++){
				SDL_GetRGB(getpixel(img_set[i], j, k), img_set[i]->format, &grey, &grey, &grey);
				mat[row][i] = grey;
				row++;
			}
		}
	}

	vect mean = create_vector(width*height);
	matrix_mean_row(mat, width*height, columns, mean);
	matrix_center(mat, width*height, columns, mean);
	matrix_transpose(mat, width*height, columns, transpose);
	matrix_multiply(mat, width*height, columns, transpose, columns, width*height, mul);
	svd(mul, width*height, width*height, eigenvalues, V);

	free(mat);
	free(transpose);
	free(mul);
	free(V);
	free(mean);

	print_vector(eigenvalues, width*height);

	return eigenvalues;
}	
