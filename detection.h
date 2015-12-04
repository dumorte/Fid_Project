#ifndef _DETECTION_H_
#define _DETECTION_H_

#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include "constantes.h"
#include "pixel_operations.h"

typedef struct s_vector t_vector;
struct s_vector {
	int vect[24*24];
};

t_vector *img_to_vector(SDL_Surface *img);

#endif
