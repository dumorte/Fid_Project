#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "feature_scaling.h"
#include "haar_feature.h"
#include "pixel_operations.h"
#include "integral_image.h"

int max(int a, int b){
	return a > b ? a : b; 
}

Uint32 feature_scaling(SDL_Surface *img, struct Feature *f){
	Uint32 scaled_feature; 
	Uint32 s1, s2, s3, s4, s5, s6; // s7, s8, s9; 
	Uint32 *mat = integral_image_matrix(grey_level(img)); 
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
		s1 = mat[f->i*width+f->j]; 
		s2 = mat[(f->i+f->h-1)*width+f->j]; 
		s3 = mat[(f->i+f->h-1)*width+(f->j+f->w-1)]; 
		s4 = mat[(f->i+f->h-1)*width+(f->j+2*f->w-1)]; 
		s5 = mat[f->i*width+(f->j+2*f->w-1)]; 
		s6 = mat[f->i*width+(f->j+f->w-1)]; 
		sum = s3-s6-s2+s1-s4+s5+s3-s6;
		scaled_feature = (sum*a)/(2*f->w*f->h); 
		
		return scaled_feature; 
	}

	if(f->type == B){
		a = 3*f->w*f->h; 
		f->i = (f->i*width)/24;
		f->j = (f->j*width)/24;
		f->h = (f->h*width)/24; 
		f->w = max((f->w*width)/72, (width-f->j+1)/3); 
		s1 = mat[f->i*width+f->j]; 
		s2 = mat[(f->i+f->h-1)*width+f->j]; 
		s3 = mat[(f->i+f->h-1)*width+(f->j+f->w-1)];
		s4 = mat[(f->i+f->h-1)*width+(f->j+2*f->w-1)];
		s5 = mat[(f->i+f->h-1)*width+(f->j+3*f->w-1)];
		s6 = mat[f->i*width+(f->j+3*f->w-1)];
		s7 = mat[f->i*width+(f->j+2*f->w-1)];
		s8 = mat[f->i*width+(f->j+f->w-1)];
		sum = 2*s3+s1-2*s8-s2-2*s4+2*s7+s5-s6;
		scaled_feature = (sum*a)/(3*f->w*f->h); 

		return scaled_feature; 
	}
}
