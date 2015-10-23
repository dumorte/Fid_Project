#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "feature_scaling.h"
#include "haar_feature.h"
#include "pixel_operations.h"

int max(int a, int b){
	return a > b ? a : b; 
}

int feature_scaling(SDL_Surface *img, struct Feature *f){
	//Uint32 scaled_feature; 
	Uint32 s1, s2, s3, s4, s5, s6; // s7, s8, s9; 
	int width = img->w; 
	//int height = img->h; 
	Uint32 sum = 0; 
	int a = 0; 

	if(f->type == A){
		a = 2*f->w*f->h; 
		f->i = (f->i*width)/24; 
		f->j = (f->j*width)/24; 
		f->h = (f->h*width)/24; 
		f->w = max((f->w*width)/48, (width-f->j+1)/2); 
		s1 = getpixel(img, f->i, f->j); 
		s2 = getpixel(img, f->i+f->h-1, f->j); 
		s3 = getpixel(img, f->i+f->h-1, f->j+f->w-1); 
		s4 = getpixel(img, f->i+f->h-1, f->j+2*f->w-1); 
		s5 = getpixel(img, f->i, f->j+2*f->w-1); 
		s6 = getpixel(img, f->i, f->j+f->w-1); 
		sum = s3-s6-s2+s1-s4+s5+s3-s6;
		
		return (sum*a)/(2*f->w*f->h); 
	}

	if(f->type == B){
		a = 3*f->w*f->h; 
		f->i;
	}
}
