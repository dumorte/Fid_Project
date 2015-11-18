#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include "haar_feature.h"
#include "constantes.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

//#include "list.h"

typedef struct s_example_images t_example_images;
struct s_example_images {
	SDL_Surface *img;
	int face;
	int n;
};

typedef struct s_weak_classifier t_weak_classifier;
struct s_weak_classifier {
	t_feature f;
	float weight, error;
};

t_feature *sort_features(t_feature *feature);

float sum_weights(float *weight, t_example_images *ex_img);
t_classifier learning_classification(t_example_images);

#endif
