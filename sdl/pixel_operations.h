// pixel_operations.h

#ifndef PIXEL_OPERATIONS_H_
#define PIXEL_OPERATIONS_H_

#include <stdlib.h>
#include <SDL.h>

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
SDL_Surface *grey_level(SDL_Surface *img);
Uint32 integral_image_point(SDL_Surface *img, unsigned x, unsigned y);
Uint32 *integral_image_matrix(SDL_Surface *img);
SDL_Surface *matrix_to_img(SDL_Surface *img, Uint32 *mat);

#endif
