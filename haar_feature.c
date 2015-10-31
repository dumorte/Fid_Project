#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "haar_feature.h"
#include "pixel_operations.h"
#include "integral_image.h"

#define SIZE 24

t_vector **haar_feature(SDL_Surface *img){
	int width = img->w - SIZE; 
	int height = img->h - SIZE;
	t_vector **haar = malloc(sizeof(t_vector));

	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			t_vector *v = feature_vect(img, i, j);
			haar[i*width+j] = v;
			free(v); 
		}
	}

	return haar; 
}

t_vector *feature_vect(SDL_Surface *img, int x, int y){
	t_vector *v = malloc(sizeof(t_vector)); 
	Uint32 *mat = integral_image_matrix(grey_level(img));  
	int width = img->w; 
	//int height = img->h; 
	SDL_Rect r; 
	r.x = x; 
	r.y = y; 
	r.w = SIZE; 
	r.h = SIZE; 
	int s1, s2, s3, s4, s5, s6, s7, s8, s9; 
	int f = 0; 
	
	/* Feature type A */
	for(int i = r.y; i < r.y+r.h; i++){
		for(int j = r.x; j < r.x+r.w; j++){
			for(int w = 1; 2*w < (r.x+r.w+1-j); w++){
				for(int h = 1; h < (r.y+r.h+1-i); h++){
					s1 = mat[i*width+j]; 
					s2 = mat[(i+h-1)*width+j]; 
					s3 = mat[(i+h-1)*width+(j+w-1)]; 
					s4 = mat[(i+h-1)*width+(j+2*w-1)]; 
					s5 = mat[i*width+(j+2*w-1)]; 
					s6 = mat[i*width+(j+w-1)]; 
					v->tab[f].type = A; 
					v->tab[f].i = i; 
					v->tab[f].j = j; 
					v->tab[f].w = w; 
					v->tab[f].h = h; 
					v->tab[f].param = s3-s6-s2+s1-s4+s5+s3-s6;
					f++;
				}
			}
		}
	}

	/* Feature type B */
	for(int i = r.y; i < r.y+r.h; i++){
		for(int j = r.x; j < r.x+r.w; j++){
			for(int w = 1; 3*w < (r.x+r.w+1-j); w++){
				for(int h = 1; h < (r.y+r.w+1-i); h++){
					s1 = mat[i*width+j]; 
					s2 = mat[(i+h-1)*width+j]; 
					s3 = mat[(i+h-1)*width+(j+w-1)];
					s4 = mat[(i+h-1)*width+(j+2*w-1)];
					s5 = mat[(i+h-1)*width+(j+3*w-1)];
					s6 = mat[i*width+(j+3*w-1)];
					s7 = mat[i*width+(j+2*w-1)];
					s8 = mat[i*width+(j+w-1)];
					v->tab[f].type = B; 
					v->tab[f].i = i; 
					v->tab[f].j = j; 
					v->tab[f].w = w; 
					v->tab[f].h = h; 
					v->tab[f].param = 2*s3+s1-2*s8-s2-2*s4+2*s7+s5-s6;
					f++; 
				}
			}
		}
	}

	/* Feature type C */
	for(int i = r.y; i < r.y+r.h; i++){
		for(int j = r.x; j < r.x+r.w; j++){
			for(int w = 1; w < (r.x+r.w+1-j); w++){
				for(int h = 1; 2*h < (r.y+r.h+1-i); h++){
					s1 = mat[i*width+j]; 
					s2 = mat[(i+h-1)*width+j]; 
					s3 = mat[(i+2*h-1)*width+j]; 
					s4 = mat[(i+2*h-1)*width+(j+w-1)]; 
					s5 = mat[(i+h-1)*width+(j+w-1)]; 
					s6 = mat[i*width+(j+w-1)];
					v->tab[f].type = C; 
					v->tab[f].i = i; 
					v->tab[f].j = j; 
					v->tab[f].w = w; 
					v->tab[f].h = h; 
					v->tab[f].param = 2*s5+s1-s6-2*s2-s4+s3;
					f++; 
				}
			}
		}
	}

	/* Feature type D */
	for(int i = r.y; i < r.y+r.h; i++){
		for(int j = r.x; j < r.x+r.w; j++){
			for(int w = 1; w < (r.x+r.w+1-j); w++){
				for(int h = 1; 3*h < (r.y+r.h+1-i); h++){
					s1 = mat[i*width+j]; 
					s2 = mat[(i+h-1)*width+j]; 
					s3 = mat[(i+2*h-1)*width+j];
					s4 = mat[(i+3*h-1)*width+j];
					s5 = mat[(i+3*h-1)*width+(j+w-1)];
					s6 = mat[(i+2*h-1)*width+(j+w-1)];
					s7 = mat[(i+h-1)*width+(j+w-1)];
					s8 = mat[i*width+(j+w-1)];
					v->tab[f].type = D;
					v->tab[f].i = i; 
					v->tab[f].j = j; 
					v->tab[f].w = w; 
					v->tab[f].h = h; 
					v->tab[f].param = 2*s7+s1-2*s2-s8-2*s6+2*s3+s5-s4; 
					f++; 
				}
			}
		}
	}

	/* Feature type E */
	for(int i = r.y; i < r.y+r.h; i++){
		for(int j = r.x; j < r.x+r.w; j++){
			for(int w = 1; 2*w < (r.x+r.w+1-j); w++){
				for(int h = 1; 2*h < (r.y+r.h+1-i); h++){
					s1 = mat[i*width+j]; 
					s2 = mat[(i+h-1)*width+j]; 
					s3 = mat[(i+2*h-1)*width+j]; 
					s4 = mat[(i+2*h-1)*width+(j+w-1)]; 
					s5 = mat[(i+2*h-1)*width+(j+2*w-1)]; 
					s6 = mat[(i+h-1)*width+(j+2*w-1)];
					s7 = mat[i*width+(j+2*w-1)]; 
					s8 = mat[i*width+(j+w-1)]; 
					s9 = mat[(i+h-1)*width+(j+w-1)]; 
					v->tab[f].type = E; 
					v->tab[f].i = i; 
					v->tab[f].j = j; 
					v->tab[f].w = w; 
					v->tab[f].h = h; 
					v->tab[f].param = 4*s9+s1-2*s2-2*s8-2*s4+s3-2*s6+s7+s5; 
					f++; 
				}
			}
		}
	}

	return v; 
}
