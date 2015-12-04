#ifndef _HAAR_FEATURE_H_
#define _HAAR_FEATURE_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "pixel_operations.h"
#include "integral_image.h"
#include "constantes.h"

enum featureType {
	A, B, C, D, E 
}; 

typedef struct s_feature t_feature; 
struct s_feature {
	enum featureType type; 
	int i, j, w, h, param, face;
	float weight;
}; 

t_feature *feature_vect(SDL_Surface *img); 

#endif
