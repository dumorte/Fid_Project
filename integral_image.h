#ifndef INTEGRAL_IMAGE_H_
#define INTEGRAL_IMAGE_H_

#include <stdlib.h>
#include <SDL.h>
#include "pixel_operations.h"

Uint32 *integral_image_matrix(SDL_Surface *img);
SDL_Surface *matrix_to_img(SDL_Surface *img, Uint32 *mat);

#endif
