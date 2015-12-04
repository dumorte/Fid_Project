#include "detection.h"

t_vector *img_to_vector(SDL_Surface *img){
	t_vector *v = malloc(sizeof(t_vector)); 
	int width = img->w; 
	int height = img->h; 
	Uint8 val = 0; 

	for(int i = 0; i < height; i++){
		printf("\n"); 
		for(int j = 0; j < width; j++){
			SDL_GetRGB(getpixel(img, i, j), img->format, &val, &val, &val); 
			v->vect[i*width+j] = val; 
			printf("%d | ", val); 
		}
	}

	return v; 
}
