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

/*float *create_matrix_mean(SDL_Surface **img_set, int columns) //passer les images en niv de gris //columns = nbimages
{ 
	Uint8 grey;
	float mean = 0;
	int width = img_set[0]->w;
	int height = img_set[0]->h;
	float *mat = malloc((columns+1)*width*height*sizeof(float));
	int pos = 0;
	
	//Place values into matrix
	for(int k = 0; k<columns; k++)
	{ 
		for(int i = 0; i<height; i++)
		{ 
			for(int j = 0; j<width; j++)
			{ 
				SDL_GetRGB(getpixel(img_set[k], i, j), img_set[k]->format, &grey, &grey, &grey);
				mat[pos+k] = (float)grey;
				pos+=columns+1;
			}
		}
		pos = 0;
	}
	
	//Calculate mean
	pos = columns;
	for(int i = 0; i<width*height; i++)
	{ 
		for(int j = 0; j<columns; j++)
		{ 
			mean+=mat[i*(columns+1)+j];
		}
		mean/=3;
		mat[pos] = mean;
		pos+=(columns+1);
		mean=0;
	}
	
	//Substract mean to each pixel value
	pos = columns;
	for(int i = 0; i<width*height; i++)
	{ 
		for(int j = 0; j<columns; j++)
		{ 
			mat[i*(columns+1)+j]-=mat[pos];
		}
		pos+=(columns+1);
	}
	
	//Print matrix
	for(int i = 0; i<width*height; i++)
	{ 
		for(int j = 0; j<columns+1; j++)
		{ 
			printf("%6f | ", mat[i*(columns+1)+j]);
		}
		printf("\n");
	}
	return mat;
}*/
