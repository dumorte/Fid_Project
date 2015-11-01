#ifndef _HAAR_FEATURE_H_
#define _HAAR_FEATURE_H_

#define NB_FEATURES 162336
#include <SDL/SDL.h>
#define SIZE 24

enum featureType {
	A, B, C, D, E 
}; 

typedef struct s_feature t_feature; 
struct s_feature {
	enum featureType type; 
	int i; 
	int j; 
	int w; 
	int h; 
	int param;
	float weight;
}; 

t_feature *feature_vect(SDL_Surface *img); 

#endif
