#ifndef _FEATURE_SCALING_H_
#define _FEATURE_SCALING_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "haar_feature.h"
#include "pixel_operations.h"
#include "integral_image.h"
#include "constantes.h"

void feature_scaling(SDL_Surface *img, t_feature *f); 

#endif
