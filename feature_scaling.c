#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "feature_scaling.h"
#include "haar_feature.h"
#include "pixel_operations.h"
#include "integral_image.h"
#include "constantes.h"

/*void scaled_feature(SDL_Surface *img, t_vector *vect){
	for(int i = 0; i < NB_FEATURES; i++){
		feature_scaling(img, &vect->tab[i]);
	}
}*/

/*int max(int a, int b){
	return a > b ? a : b; 
}*/

void feature_scaling(SDL_Surface *img, t_feature *f){
	//Uint32 scaled_feature; 
	Uint32 s1, s2, s3, s4, s5, s6, s7, s8, s9; 
	Uint32 *mat = integral_image_matrix(grey_level(img)); 
	int width = img->w; 
	//int height = img->h; 
	Uint32 sum = 0; 
	//int a = 0; 

	switch(f->type){
		case A: 
			//a = 2*f->w*f->h; 
			f->i = (f->i*width)/24; 
			printf("%d\n",f->i);
			f->j = (f->j*width)/24; printf("%d\n",f->j);
			f->h = (f->h*width)/24; printf("%d\n",f->h);
			f->w = ((2*f->w*width)/24)/2; printf("%d\n",f->w);//suppr max && 1+... expression debut 
			s1 = mat[f->i*width+f->j]; 
			s2 = mat[(f->i+f->h-1)*width+f->j]; 
			s3 = mat[(f->i+f->h-1)*width+(f->j+f->w-1)]; 
			s4 = mat[(f->i+f->h-1)*width+(f->j+2*f->w-1)]; 
			s5 = mat[f->i*width+(f->j+2*f->w-1)]; 
			s6 = mat[f->i*width+(f->j+f->w-1)]; 
			sum = s1-s2+2*s3-s4+s5-2*s6;
			//scaled_feature = (sum*a)/(2*f->w*f->h); 
			
			f->param = sum;//scaled_feature 
			break; 

		case B: 
			//a = 3*f->w*f->h; 
			f->i = (f->i*width)/24;
			f->j = (f->j*width)/24;
			f->h = (f->h*width)/24; 
			f->w = ((3*f->w*width)/24)/3; 
			s1 = mat[f->i*width+f->j]; 
			s2 = mat[(f->i+f->h-1)*width+f->j]; 
			s3 = mat[(f->i+f->h-1)*width+(f->j+f->w-1)];
			s4 = mat[(f->i+f->h-1)*width+(f->j+2*f->w-1)];
			s5 = mat[(f->i+f->h-1)*width+(f->j+3*f->w-1)];
			s6 = mat[f->i*width+(f->j+3*f->w-1)];
			s7 = mat[f->i*width+(f->j+2*f->w-1)];
			s8 = mat[f->i*width+(f->j+f->w-1)];
			sum = s1-s2+2*s3-2*s4+s5-s6+2*s7-2*s8;
			//scaled_feature = (sum*a)/(3*f->w*f->h); 
	
			f->param = sum; 
			break; 

		case C: 
			//a = 2*f->w*f->h; 
			f->i = (f->i*width)/24; 
			f->j = (f->j*width)/24; 
			f->w = (f->w*width)/24; 
			f->h = ((2*f->h*width)/24)/2; 
			s1 = mat[f->i*width+f->j]; 
			s2 = mat[(f->i+f->h-1)*width+f->j]; 
			s3 = mat[(f->i+1*f->h-1)*width+f->j]; 
			s4 = mat[(f->i+2*f->h-1)*width+(f->j+f->w-1)]; 
			s5 = mat[(f->i+f->h-1)*width+(f->j+f->w-1)]; 
			s6 = mat[f->i*width+(f->j+f->w-1)];
			sum = s1-2*s2+s3-s4+2*s5-s6;
			//scaled_feature = (sum*a)/(2*f->w*f->h); 
			f->param = sum; 
			break; 
		case D: 
			//a = 3*f->w*f->h; 
			f->i = (f->i*width)/24; 
			f->j = (f->j*width)/24; 
			f->w = (f->w*width)/24; 
			f->h = (1+(3*f->h*width)/24)/3; 
			s1 = mat[f->i*width+f->j]; 
			s2 = mat[(f->i+f->h-1)*width+f->j]; 
			s3 = mat[(f->i+2*f->h-1)*width+f->j];
			s4 = mat[(f->i+3*f->h-1)*width+f->j];
			s5 = mat[(f->i+3*f->h-1)*width+(f->j+f->w-1)];
			s6 = mat[(f->i+2*f->h-1)*width+(f->j+f->w-1)];
			s7 = mat[(f->i+f->h-1)*width+(f->j+f->w-1)];
			s8 = mat[f->i*width+(f->j+f->w-1)];
			sum = s1-2*s2+2*s3-s4+s5-2*s6+2*s7-s8; 
			//scaled_feature = (sum*a)/(3*f->w*f->h); 
			f->param = sum; 
			break; 

		case E: 
			//a = 4*f->w*f->h; 
			f->i = (f->i*width)/24; 
			f->j = (f->j*width)/24; 
			f->w = (1+(2*f->w*width)/24)/2; 
			f->h = (1+(2*f->h*width)/24)/2; 
			s1 = mat[f->i*width+f->j]; 
			s2 = mat[(f->i+f->h-1)*width+f->j]; 
			s3 = mat[(f->i+2*f->h-1)*width+f->j]; 
			s4 = mat[(f->i+2*f->h-1)*width+(f->j+f->w-1)]; 
			s5 = mat[(f->i+2*f->h-1)*width+(f->j+2*f->w-1)]; 
			s6 = mat[(f->i+f->h-1)*width+(f->j+2*f->w-1)];
			s7 = mat[f->i*width+(f->j+2*f->w-1)]; 
			s8 = mat[f->i*width+(f->j+f->w-1)]; 
			s9 = mat[(f->i+f->h-1)*width+(f->j+f->w-1)]; 
			sum = s1-2*s2+s3-2*s4+s5-2*s6+s7-2*s8+4*s9;
			//scaled_feature = (sum*a)/(4*f->w*f->h); 
			f->param = sum; 
			break; 

		default: 
			break;  
	}

	free(mat); 
}
