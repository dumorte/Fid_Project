#include "feature_scaling.h"
#include "haar_feature.h"

Uint32 feature_scaling(SDL_Surface *img, struct Feature *f){
	Uint32 scaled_feature; 
	Uint32 s1, s2, s3, s4, s5, s6, s7, s8, s9; 
	int width = img->w; 
	int height = img->h; 
	int a = 0; 

	if(f->type == A){
		a = 2 * f->w * f->h; 
		f->i = (f->i * width) / 24; 
		f->j = (f->j * width) / 24; 
		f->h = (f->h * width) / 24; 

	}
}
