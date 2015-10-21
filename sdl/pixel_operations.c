#include "pixel_operations.h"

SDL_Surface *matrix_to_img(SDL_Surface *img, Uint32 *mat)
{ 
	Uint32 width = img->w;
	Uint32 height = img->h;
	for(Uint32 i = 1; i<height+1; i++)
		for(Uint32 j=1; j<width+1;j++)
			putpixel(img, j-1, i-1, mat[i*width+j]);
	return img;
}

//integral zone : formule : s(A)+s(D)-s(B)-s(C) for ABDC triangle

Uint32 *integral_image_matrix(SDL_Surface *img)
{
	//changer bornes du tab
	Uint32 width = img->w;
	Uint32 height = img->h;
	Uint32 *mat = malloc((height+1)*(width+1)*sizeof(Uint32));
	for(Uint32 i = 1; i<height+1; i++){
		for(Uint32 j=1; j<width+1; j++){
			mat[i*width + j] = getpixel(img, j-1, i-1) + mat[i*width+j-1] + mat[(i-1)*width + j] - mat[(i-1)*width + j-1];
		}
	}
	return mat;
}

SDL_Surface *grey_level(SDL_Surface *img)
{                                                                                                          
	Uint8 r, g, b;                                                                                                                      
	float average = 0;                                                                                                                  

	for(int i = 0; i < img->w; i++){                                                                                                    
		for(int j = 0; j < img->h; j++){                                                                                            
			SDL_GetRGB(getpixel(img, i, j), img->format, &r, &g, &b);                                                           
			average = (0.3 * r + 0.59 * g + 0.11 * b) / 3;                                                                      
			r = average;                                                                                                        
			b = average;                                                                                                        
			g = average;                                                                                                        
                        putpixel(img, i, j, SDL_MapRGB(img->format, r, g, b));
		}
	}
	return img;
}           

static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
	int bpp = surf->format->BytesPerPixel;

	return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) {	
	Uint8 *p = pixelref(surface, x, y);
	switch(surface->format->BytesPerPixel) {
		case 1:
			return *p;
		case 2:
			return *(Uint16 *)p;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
		case 4:
			return *(Uint32 *)p;
	}

	return 0;
}
 
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
	Uint8 *p = pixelref(surface, x, y);
	switch(surface->format->BytesPerPixel) {
		case 1:
			*p = pixel;
			break;
		case 2:
			*(Uint16 *)p = pixel;
			break;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;
		case 4:
			*(Uint32 *)p = pixel;
			break;
	}
}
