#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "haar_feature.h"
#include "pixel_operations.h"
#include "integral_image.h"
#include "constantes.h"

/*t_vector **haar_feature(SDL_Surface *img){
	int width = img->w - SIZE; 
	int height = img->h - SIZE;
	t_vector **haar = malloc(sizeof(t_vector));

	for(int i = 0; i < height; i++){
		for(int j = 0; j<width; j++){
			t_vector *v = feature_vect(img, i, j); 
			haar[i*width+j] = v;	
			free(v); 
		}
	}

	return haar; 
}*/

t_feature *feature_vect(SDL_Surface *img){
	t_feature *v = malloc(NB_FEATURES*sizeof(t_feature)); 
	Uint32 *mat = integral_image_matrix(grey_level(img));  
	int width = img->w; 
	//int height = img->h; 
	SDL_Rect r; 
	r.x = 0; 
	r.y = 0; 
	r.w = SIZE; 
	r.h = SIZE; 
	int s1, s2, s3, s4, s5, s6, s7, s8, s9; 
	int f = 0; 

	
	/* Feature type A */
	for(int i = r.y; i < r.y+r.h; i++){
		for(int j = r.x; j < r.x+r.w; j++){
			for(int w = 1; j+2*w-1 < r.x+r.w; w++){
				for(int h = 1; i+h-1 < r.y+r.h; h++){ //Premiere boucle = 0
					s1 = mat[i*width+j]; 
					s2 = mat[(i+h-1)*width+j]; 
					s3 = mat[(i+h-1)*width+(j+w-1)]; 
					s4 = mat[(i+h-1)*width+(j+2*w-1)]; 
					s5 = mat[i*width+(j+2*w-1)]; 
					s6 = mat[i*width+(j+w-1)]; 
					v[f].type = A; 
					v[f].i = i; 
					v[f].j = j; 
					v[f].w = w; 
					v[f].h = h; 
					v[f].weight = 0.5;
					v[f].param = s1-s2+2*s3-s4+s5-2*s6;
					f++;
				}
			}
		}
	}

	/* Feature type B */
	for(int i = r.y; i < r.y+r.h; i++){
		for(int j = r.x; j < r.x+r.w; j++){
			for(int w = 1; j+3*w-1 < r.x+r.w; w++){
				for(int h = 1; i+h-1 < r.y+r.w; h++){
					s1 = mat[i*width+j]; 
					s2 = mat[(i+h-1)*width+j]; 
					s3 = mat[(i+h-1)*width+(j+w-1)];
					s4 = mat[(i+h-1)*width+(j+2*w-1)];
					s5 = mat[(i+h-1)*width+(j+3*w-1)];
					s6 = mat[i*width+(j+3*w-1)];
					s7 = mat[i*width+(j+2*w-1)];
					s8 = mat[i*width+(j+w-1)];
					v[f].type = B; 
					v[f].i = i; 
					v[f].j = j; 
					v[f].w = w; 
					v[f].h = h; 
					v[f].weight = 0.5;
					v[f].param = s1-s2+2*s3-2*s4+s5-s6+2*s7-2*s8;
					f++; 
				}
			}
		}
	}

	/* Feature type C */
	for(int i = r.y; i < r.y+r.h; i++){
		for(int j = r.x; j < r.x+r.w; j++){
			for(int w = 1; j+w-1 < r.x+r.w; w++){
				for(int h = 1; i+2*h-1 < r.y+r.h; h++){
					s1 = mat[i*width+j]; 
					s2 = mat[(i+h-1)*width+j]; 
					s3 = mat[(i+2*h-1)*width+j]; 
					s4 = mat[(i+2*h-1)*width+(j+w-1)]; 
					s5 = mat[(i+h-1)*width+(j+w-1)]; 
					s6 = mat[i*width+(j+w-1)];
					v[f].type = C; 
					v[f].i = i; 
					v[f].j = j; 
					v[f].w = w; 
					v[f].h = h; 
					v[f].weight = 0.5; 
					v[f].param = s1-2*s2+s3-s4+2*s5-s6;
					f++; 
				}
			}
		}
	}

	/* Feature type D */
	for(int i = r.y; i < r.y+r.h; i++){
		for(int j = r.x; j < r.x+r.w; j++){
			for(int w = 1; j+w-1 < r.x+r.w; w++){
				for(int h = 1; i+3*h-1 < r.y+r.h; h++){
					s1 = mat[i*width+j]; 
					s2 = mat[(i+h-1)*width+j]; 
					s3 = mat[(i+2*h-1)*width+j];
					s4 = mat[(i+3*h-1)*width+j];
					s5 = mat[(i+3*h-1)*width+(j+w-1)];
					s6 = mat[(i+2*h-1)*width+(j+w-1)];
					s7 = mat[(i+h-1)*width+(j+w-1)];
					s8 = mat[i*width+(j+w-1)];
					v[f].type = D;
					v[f].i = i; 
					v[f].j = j; 
					v[f].w = w; 
					v[f].h = h; 
					v[f].weight = 0.5;
					v[f].param = s1-2*s2+2*s3-s4+s5-2*s6+2*s7-s8; 
					f++; 
				}
			}
		}
	}

	/* Feature type E */
	for(int i = r.y; i < r.y+r.h; i++){
		for(int j = r.x; j < r.x+r.w; j++){
			for(int w = 1; j+2*w-1 < r.x+r.w; w++){
				for(int h = 1; i+2*h-1 < r.y+r.h; h++){
					s1 = mat[i*width+j]; 
					s2 = mat[(i+h-1)*width+j]; 
					s3 = mat[(i+2*h-1)*width+j]; 
					s4 = mat[(i+2*h-1)*width+(j+w-1)]; 
					s5 = mat[(i+2*h-1)*width+(j+2*w-1)]; 
					s6 = mat[(i+h-1)*width+(j+2*w-1)];
					s7 = mat[i*width+(j+2*w-1)]; 
					s8 = mat[i*width+(j+w-1)]; 
					s9 = mat[(i+h-1)*width+(j+w-1)]; 
					v[f].type = E; 
					v[f].i = i; 
					v[f].j = j; 
					v[f].w = w; 
					v[f].h = h; 
					v[f].weight = 0.5;
					v[f].param = s1-2*s2+s3-2*s4+s5-2*s6+s7-2*s8+4*s9; 
					f++; 
				}
			}
		}
	}

	return v; 
}
