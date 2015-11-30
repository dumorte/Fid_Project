#ifndef _ADABOOST_H_
#define _ADABOOST_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "classifier.h"

typedef struct s_couple_image t_couple_image;
struct s_couple_image{
	SDL_Surface *img;
	int face;
	float weight;
};

void print_classifier(t_dec_stump *dec, FILE *f); 
void adaboost(SDL_Surface **img_set, int T);

#endif
