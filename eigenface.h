#ifndef _EIGENFACE_H_
#define _EIGENFACE_H_

#include <SDL/SDL.h>
#include <stdlib.h>
#include "constantes.h"
#include "pixel_operations.h"
#include "matrix.h"
#include "svd.h"

vect eigenvalue(SDL_Surface **img_set, int columns);

#endif
