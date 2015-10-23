#ifndef _HAAR_FEATURE_H_
#define _HAAR_FEATURE_H_

#define NB_FEATURES 162336

enum featureType {
	A, B, C, D, E 
}; 

struct Feature {
	enum featureType type; 
	int i; 
	int j; 
	int w; 
	int h; 
	Uint32 param; 
}; 

struct Vector {
	struct Feature tab[NB_FEATURES]; 
};

struct Vector *feature_vect(SDL_Surface *img, int x, int y); 
struct Vector **haar_feature(SDL_Surface *img); 

#endif
