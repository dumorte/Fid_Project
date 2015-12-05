#ifndef _EIGENFACE_H_
#define _EIGENFACE_H_

#include <SDL/SDL.h>
#include <stdlib.h>
#include "constantes.h" //FIXME
#include "pixel_operations.h"

float *create_matrix_mean(SDL_Surface **img_set, int columns);
float *transposed_matrix(float *mat, int width, int height, int columns);

#endif
