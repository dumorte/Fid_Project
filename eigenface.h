#ifndef _EIGENFACE_H_
#define _EIGENFACE_H_

#include <SDL/SDL.h>
#include <stdlib.h>
#include "constantes.h" //FIXME
#include "pixel_operations.h"
#include "matrix.h"
#include "svd.h"

//float *create_matrix_mean(SDL_Surface **img_set, int columns);
vect eigenvalue(SDL_Surface **img_set, int columns);

#endif
