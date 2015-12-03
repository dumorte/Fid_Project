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
	Uint32 pixel;
	Uint8 r,g,b,grey;
        Uint32 *mat = calloc((height+1)*(width+1), sizeof(Uint32));
        for(Uint32 i=1; i<height+1; i++){
		//printf("\n");
                for(Uint32 j=1; j<width+1; j++){
			pixel = getpixel(img, i-1, j-1);
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			grey = (r+g+b)/3;
			printf("grey : %d\n", grey);
                        mat[i*width + j] = grey + mat[i*width+j-1] + mat[(i-1)*width + j] - mat[(i-1)*width + j-1];
			//printf("%d | ", mat[i*width+j]);
                }
        }
	Uint32 *matcpy = calloc((height)*(width), sizeof(Uint32));
	printf("\n\n");
	for(Uint32 i = 1; i<height+1; i++){
		printf("\n");
		for(Uint32 j=1; j<width+1; j++)
		{ 
			matcpy[(i-1)*width+j-1]= mat[i*width+j];
			printf("%d | ", matcpy[(i-1)*width+j-1]);
		}
	}
	free(mat);
        return matcpy;
}
