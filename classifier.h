#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "haar_feature.h"
#include "constantes.h"
#include "feature_scaling.h"

typedef struct s_couple_image t_couple_image;
struct s_couple_image{
	SDL_Surface *img;
	int face;
	float weight;
};

typedef struct s_dec_stump t_dec_stump;
struct s_dec_stump {
	int threshold, toggle, margin;
	float error;
	int i, j, w, h;
	enum featureType type;
};

void print_classifier(t_dec_stump *dec, FILE *f); 
t_feature *sort_features(t_feature *feature);
t_dec_stump *dec_stump(t_couple_image *img_set, t_feature *f);
t_dec_stump *best_stump(t_couple_image *img_set);
int max(t_feature *f, int a);

#endif
