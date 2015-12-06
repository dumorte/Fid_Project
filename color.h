#ifndef COLOR_H_
#define COLOR_H_

#include <SDL.h>

int *bin_mat(SDL_Surface *img);
void print_mat(int *mat, int w, int h);
int abs(int a);
int min(int a, int b, int c);
int maxi(int a, int b, int c);
int *labeling(int *bin_mat, int w, int h);
#endif
