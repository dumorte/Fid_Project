#ifndef PIXEL_OPERATIONS_H_
#define PIXEL_OPERATIONS_H_

#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
SDL_Surface *grey_level(SDL_Surface *img);
SDL_Surface *load_image(char *path);
void wait_for_keypressed(void);
void init_sdl(void);
SDL_Surface* display_image(SDL_Surface *img);


#endif
