#include "integral_image.h"

SDL_Surface *matrix_to_img(SDL_Surface *img, Uint32 *mat) //Only for testing, to remove FIXME
{
        Uint32 width = img->w;
        Uint32 height = img->h;
        for(Uint32 i = 0; i<height; i++)
                for(Uint32 j=0; j<width;j++)
                        putpixel(img, j, i, mat[i*width+j]);
        return img;
}

Uint32 *integral_image_matrix(SDL_Surface *img)
{
        Uint32 width = img->w;
        Uint32 height = img->h;
	Uint8 grey;
        Uint32 *mat = calloc((height+1)*(width+1), sizeof(Uint32));
	
	for(Uint32 i=1; i<height+1; i++){
                for(Uint32 j=1; j<width+1; j++){
			SDL_GetRGB(getpixel(img, i-1, j-1), img->format, &grey, &grey, &grey);
                        mat[i*(width+1) + j] = grey + mat[i*(width+1)+j-1] + mat[(i-1)*(width+1) + j] - mat[(i-1)*(width+1) + j-1];
                }
        }
	
	Uint32 *matcpy = calloc((height)*(width), sizeof(Uint32));
	for(Uint32 i = 1; i<height+1; i++){
		for(Uint32 j=1; j<width+1; j++)
		{ 
			matcpy[(i-1)*width+j-1]= mat[i*(width+1)+j];
		}
	}
	free(mat);
	return matcpy;
}
