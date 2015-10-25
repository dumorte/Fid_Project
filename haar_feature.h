#ifndef _HAAR_FEATURE_H_
#define _HAAR_FEATURE_H_

#define NB_FEATURES 162336

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
	Uint32 param; 
}; 

typedef struct s_vector t_vector; 
struct s_vector {
	t_feature tab[NB_FEATURES]; 
};

struct t_vector *feature_vect(SDL_Surface *img, int x, int y); 
struct t_vector **haar_feature(SDL_Surface *img); 

#endif
