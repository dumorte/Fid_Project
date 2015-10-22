#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "haar_feature.h"
#include "pixel_operations.h"
#include "integral_image.h"

struct Vector *feature_vect(SDL_Surface *img){
	struct Vector *v = malloc(sizeof(struct Vector)); 
	Uint32 *mat = integral_image_matrix(img); 
	SDL_Surface *ii = matrix_to_img(img, mat); 
	SDL_Rect r; 
	r.x = 0; 
	r.y = 0; 
	r.w = 24; 
	r.h = 24; 
	Uint32 s1, s2, s3, s4, s5, s6, s7, s8, s9; 
	int f = 0; 
	
	/* Feature type A */
	for(int i = 0; i < r.w; i++){
		for(int j = 0; j < r.h; j++){
			for(int w = 1; 2*w <= r.w+1-j%r.h; w++){
				for(int h = 1; h <= r.w+1-i%r.w; h++){
					s1 = getpixel(ii, i, j); 
					s2 = getpixel(ii, i+h-1, j); 
					s3 = getpixel(ii, i+h-1, j+w-1); 
					s4 = getpixel(ii, i+h-1, j+2*w-1); 
					s5 = getpixel(ii, i, j+2*w-1); 
					s6 = getpixel(ii, i, j+w-1); 
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
	for(int i = 0; i < r.w; i++){
		for(int j = 0; j < r.h; j++){
			for(int w = 1; 3*w <= r.w+1-j%r.w; w++){
				for(int h = 1; h <= r.w+1-i%r.h; h++){
					s1 = getpixel(ii, i, j); 
					s2 = getpixel(ii, i+h-1, j); 
					s3 = getpixel(ii, i+h-1, j+w-1);
					s4 = getpixel(ii, i+h-1, j+2*w-1);
					s5 = getpixel(ii, i+h-1, j+3*w-1);
					s6 = getpixel(ii, i, j+3*w-1);
					s7 = getpixel(ii, i, j+2*w-1);
					s8 = getpixel(ii, i, j+w-1);
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
	for(int i = 0; i < r.w; i++){
		for(int j = 0; j < r.h; j++){
			for(int w = 1; w <= r.w+1-j%r.w; w++){
				for(int h = 1; 2*h <= r.h+1-i%r.h; h++){
					s1 = getpixel(ii, i, j); 
					s2 = getpixel(ii, i+h-1, j); 
					s3 = getpixel(ii, i+2*h-1, j); 
					s4 = getpixel(ii, i+2*h-1, j+w-1); 
					s5 = getpixel(ii, i+h-1, j+w-1); 
					s6 = getpixel(ii, i, j+w-1);
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
	for(int i = 0; i < r.w; i++){
		for(int j = 0; j < r.h; j++){
			for(int w = 1; w <= r.w+1-j%r.w; w++){
				for(int h = 1; 3*h <= r.h+1-i%r.h; h++){
					s1 = getpixel(ii, i, j); 
					s2 = getpixel(ii, i+h-1, j); 
					s3 = getpixel(ii, i+2*h-1, j);
					s4 = getpixel(ii, i+3*h-1, j);
					s5 = getpixel(ii, i+3*h-1, j+w-1);
					s6 = getpixel(ii, i+2*h-1, j+w-1);
					s7 = getpixel(ii, i+h-1, j+w-1);
					s8 = getpixel(ii, i, j+w-1);
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
	for(int i = 0; i < r.w; i++){
		for(int j = 0; j < r.h; j++){
			for(int w = 1; 2*w <= r.w+1-j%r.w; w++){
				for(int h = 1; 2*h <= r.h+1-i%r.h; h++){
					s1 = getpixel(ii, i, j); 
					s2 = getpixel(ii, i+h-1, j); 
					s3 = getpixel(ii, i+2*h-1, j); 
					s4 = getpixel(ii, i+2*h-1, j+w-1); 
					s5 = getpixel(ii, i+2*h-1, j+2*w-1); 
					s6 = getpixel(ii, i+h-1, j+2*w-1);
					s7 = getpixel(ii, i, j+2*w-1); 
					s8 = getpixel(ii, i, j+w-1); 
					s9 = getpixel(ii, i+h-1, j+w-1); 
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
