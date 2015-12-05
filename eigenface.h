#ifndef _EIGENFACE_H_
#define _EIGENFACE_H_

#include <SDL/SDL.h>
#include <stdlib.h>
#include "constantes.h" //FIXME
#include "pixel_operations.h"

float *create_matrix_mean(SDL_Surface **img_set, int columns);
float *transposed_matrix(float *mat, int width, int height, int columns);
float *multiply_matrix(float *m1, float *m2, int row1, int row2, int col1, int col2); 
void print_matrix(float *m, int width, int height); 

#endif
