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
	int param; 
}; 

typedef struct s_vector t_vector; 
struct s_vector {
	t_feature tab[NB_FEATURES]; 
};

typedef struct s_haar_feature t_haar_feature;
struct s_haar_feature {
	t_vector *vect;
};

t_vector *feature_vect(SDL_Surface *img, int x, int y); 
t_haar_feature *haar_feature(SDL_Surface *img); 

#endif
