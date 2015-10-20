#include "pixel_operations.h"


//integral zone


Uint32 *integral_image_matrix(SDL_Surface *img, size_t width, size_t height)
{ 
	//def width && height
	int *mat = malloc(height*width*sizeof(Uint32));
	for(int i = 0; i<height; i++)
		for(int j=0; j<width;j++)
			mat[i*width + j] = integral_image_point(img, i, j);
	return mat;
}

Uint32 integral_image_point(SDL_Surface *img, int x, int y)
{
	if(x == 0 || y==0)
		return getpixel(img, x, y);
	else
		return getpixel(img, x, y) + integral_image_point(img, x-1, y) + integral_image_point(img, x, y-1) - integral_image_point(img, x-1, y-1);
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
