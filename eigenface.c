#include "eigenface.h"

float *create_matrix_mean(SDL_Surface **img_set, int columns) //passer les images en niv de gris //columns = nbimages
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
}

float *transposed_matrix(float *mat, int width, int height, int columns)//FIXME
{ 
	printf("\n\n");
	float *transposed_mat = malloc(columns*width*height*sizeof(float));
	for(int i = 0; i<width*height; i++)
	{ 
		for(int j = 0; j<columns; j++)
		{ 
			transposed_mat[j*columns+i] = mat[i*(columns+1)+j];
		}
	}
	for(int i = 0; i<columns+1; i++)
	{ 
		for(int j = 0; j<width*height; j++)
		{ 
			printf("%6f | ", transposed_mat[i*columns+j]);
		}
		printf("\n");
	}
	return transposed_mat;
}
