#include "color.h"
#include "pixel_operations.h"
#include <SDL/SDL_image.h>

void print_mat(int *mat, int w, int h)
{ 
	for(int i = 0; i<h; i++)
	{ 
		for(int j = 0; j<w; j++)
		{ 
			printf("%d | ", mat[i*w+j]);
		}
		printf("\n");
	}
}
int min(int a, int b, int c)
{ 
	int min = a;
	if(b<min)
		min = b;
	if(c<min)
		min = c;
	return min;

}

int maxi(int a, int b, int c)
{ 
	int max = a;
	if(b>max)
		max = b;
	if(c>max)
		max = c;
	return max;
}

int abs(int a)
{ 
	if(a<0)
		return -a;
	return a;
}

int *bin_mat(SDL_Surface *img)
{ 
	int *mat = malloc(img->w*img->h*sizeof(int));
	Uint8 red,green,blue;
	int r,g,b;
	for(int i = 0; i<img->h; i++)
	{ 
		for(int j = 0; j<img->w; j++)
		{ 
			SDL_GetRGB(getpixel(img,j,i), img->format, &red, &green, &blue);
			r = (int)red;
			g = (int)green;
			b = (int)blue;
			if(r>95 && g>40 && b>20 && (maxi(r,g,b)-min(r,g,b)>15 && abs(r-g)>15 && r>g && r>b))//eclairage fort//if((r>b && g>b) || (r>220 && g>210 && b>170 && abs(r-g)<=15))
			{ 
				mat[i*img->w+j] = 1;
				putpixel(img,j,i, SDL_MapRGB(img->format, 255,255,255));
			}
			else
			{ 
				mat[i*img->w+j] = 0;
				putpixel(img,j,i,SDL_MapRGB(img->format, 0,0,0));
			}
		}
	}
	return mat;
}

int *labeling(int *bin_mat, int w, int h, int nbLabels)
{ 
	int *labeled_mat = calloc(w*h, sizeof(int));
	for(int i = 0; i<h; i++)
	{ 
		for(int j = 0; j<w; j++)
		{ 
			if(bin_mat[i*w+j] == 1)
			{ 
				nbLabels++;
				labeled_mat[i*w+j] = nbLabels;
				bin_mat[i*w+j] = 0;
				//memoriser ou on est dans la matrice et di diff wero, cherche en haut a gauche (si diff 0), a droite et en bas
				int mem = i*width+j;
				if()
			}
		}
	}
}
