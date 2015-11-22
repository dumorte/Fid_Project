#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include "haar_feature.h"
#include "constantes.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

//#include "list.h"

typedef struct s_dec_stump t_dec_stump;
struct s_dec_stump {
	float threshold, toggle, error, margin;
};

t_feature *sort_features(t_feature *feature);
t_dec_stump *dec_stump(t_feature *f);
t_dec_stump *best_stump(SDL_Surface **img_set);
int max(t_feature *f, int a);

#endif
