#include "integral_image.h"

SDL_Surface *matrix_to_img(SDL_Surface *img, Uint32 *mat)
{
        Uint32 width = img->w;
        Uint32 height = img->h;
        for(Uint32 i = 1; i<height+1; i++)
                for(Uint32 j=1; j<width+1;j++)
                        putpixel(img, j-1, i-1, mat[i*width+j]);
        return img;
}

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

