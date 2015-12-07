#include "callback.h"
#include "color.h"
#include "pixel_operations.h"
#include <SDL/SDL_image.h>

void print_mat(int *mat, int w, int h)
{ 
	for(int i = 0; i<h; i++)
	{ 
		for(int j = 0; j<w; j++)
		{ 
			printf("%d|", mat[i*w+j]);
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
			if(r>95 && g>40 && b>20 && (maxi(r,g,b)-min(r,g,b)>15 && abs(r-g)>15 && r>g && r>b))//eclairage fort		//if((r>b && g>b) || (r>220 && g>210 && b>170 && abs(r-g)<=15))
			{ 
				mat[i*img->w+j] = 1;
				//putpixel(img,j,i, SDL_MapRGB(img->format, 255,255,255));
			}
			else
			{ 
				mat[i*img->w+j] = 0;
				//putpixel(img,j,i,SDL_MapRGB(img->format, 0,0,0));
			}
		}
	}
	return mat;
}

int *labeling(SDL_Surface *img)
{ 
	int *bin_matrix = bin_mat(img);
	int w = img->w;
	int h = img->h;
	int *labeled_mat = calloc(w*h, sizeof(int));
	int nbLabels = 0;
	for(int i = 0; i<h; i++)
	{ 
		for(int j = 0; j<w; j++)
		{ 
			if(bin_matrix[i*w+j] == 1)
			{ 
				nbLabels++;
				labeled_mat[i*w+j] = nbLabels;
				bin_matrix[i*w+j] = 0;
				neighbours(bin_matrix, labeled_mat, w, h, i, j, nbLabels);
			}
		}
	}
	free(bin_matrix);
	return labeled_mat;
}

void neighbours(int *bin_mat, int* labeled_mat, int w, int h, int i, int j, int label)
{ 
	if(j-1>=0)
	{ 
		if(bin_mat[i*w+j-1] == 1)
		{ 
			labeled_mat[i*w+j-1] = label;
			bin_mat[i*w+j-1] = 0;
			neighbours(bin_mat, labeled_mat, w, h, i, j-1, label);
		}
		if(i-1>=0)
		{ 
			if(bin_mat[(i-1)*w+j-1] == 1)
			{ 
				labeled_mat[(i-1)*w+j-1] = label;
				bin_mat[(i-1)*w+j-1] = 0;
				neighbours(bin_mat, labeled_mat, w, h, i-1, j-1, label);
			}
		}
		if(i+1<h)
		{ 
			if(bin_mat[(i+1)*w+j-1] == 1)
			{ 
				labeled_mat[(i+1)*w+j-1] = label;
				bin_mat[(i+1)*w+j-1] = 0;
				neighbours(bin_mat, labeled_mat, w, h, i+1, j-1, label);
			}
		}
	}
	if(j+1<w)
	{ 
		if(bin_mat[i*w+j+1] == 1)
		{ 
			labeled_mat[i*w+j+1] = label;
			bin_mat[i*w+j+1] = 0;
			neighbours(bin_mat, labeled_mat, w, h, i, j+1, label);
		}
		if(i-1>=0)
		{ 
			if(bin_mat[(i-1)*w+j+1] == 1)
			{ 
				labeled_mat[(i-1)*w+j+1] = label;
				bin_mat[(i-1)*w+j+1] = 0;
				neighbours(bin_mat, labeled_mat, w, h, i-1, j+1, label);
			}
		}
		if(i+1<h)
		{ 
			if(bin_mat[(i+1)*w+j+1] == 1)
			{ 
				labeled_mat[(i+1)*w+j+1] = label;
				bin_mat[(i+1)*w+j+1] = 0;
				neighbours(bin_mat, labeled_mat, w, h, i+1, j+1, label);
			}
		}
	}
	if(i-1>=0)
	{ 
		if(bin_mat[(i-1)*w+j] == 1)
		{ 
			labeled_mat[(i-1)*w+j] = label;
			bin_mat[(i-1)*w+j] = 0;
			neighbours(bin_mat, labeled_mat, w, h, i-1, j, label);
		}
		if(j-1>=0)
		{ 
			if(bin_mat[(i-1)*w+j-1] == 1)
			{ 
				labeled_mat[(i-1)*w+j-1] = label;
				bin_mat[(i-1)*w+j-1] = 0;
				neighbours(bin_mat, labeled_mat, w, h, i-1, j-1, label);
			}
		}
		if(j+1<w)
		{ 
			if(bin_mat[(i-1)*w+j+1] == 1)
			{ 
				labeled_mat[(i-1)*w+j+1] = label;
				bin_mat[(i-1)*w+j+1] = 0;
				neighbours(bin_mat, labeled_mat, w, h, i-1, j+1, label);
			}
		}
	}
	if(i+1<h)
	{ 
		if(bin_mat[(i+1)*w+j] == 1)
		{ 
			labeled_mat[(i+1)*w+j] = label;
			bin_mat[(i+1)*w+j] = 0;
			neighbours(bin_mat, labeled_mat, w, h, i+1, j, label);
		}
		if(j-1>=0)
		{ 
			if(bin_mat[(i+1)*w+j-1] == 1)
			{ 
				labeled_mat[(i+1)*w+j-1] = label;
				bin_mat[(i+1)*w+j-1] = 0;
				neighbours(bin_mat, labeled_mat, w, h, i+1, j-1, label);
			}
		}
		if(j+1<w)
		{ 
			if(bin_mat[(i+1)*w+j+1] == 1)
			{ 
				labeled_mat[(i+1)*w+j+1] = label;
				bin_mat[(i+1)*w+j+1] = 0;
				neighbours(bin_mat, labeled_mat, w, h, i+1, j+1, label);
			}
		}
	}
}

int get_nb_regions(SDL_Surface *img)
{ 
	int *labeled_mat = labeling(img);
	int counter = 0;
	for(int i = 0; i<img->h; i++)
	{ 
		for(int j = 0; j<img->w; j++)
		{ 
			if(counter<labeled_mat[i*img->w+j])
				counter = labeled_mat[i*img->w+j];
		}
	}
	free(labeled_mat);
	return counter;
}	

int *separate_regions(SDL_Surface *img)
{ 
	int *labeled_mat = labeling(img);
	//print_mat(labeled_mat, img->w, img->h);
	//printf("\n\n");
	int w = img->w;
	int h = img->h;
	int nbRegions = get_nb_regions(img);
	int *separated_regions = malloc(w*h*nbRegions*sizeof(int));
	int counter = 0;
	
	while(counter!=nbRegions)
	{ 
		counter++;
		for(int i = 0; i<h; i++)
		{ 
			for(int j = 0; j<w; j++)
			{ 
				if(labeled_mat[i*w+j] != counter)
					separated_regions[(counter-1)*w*h+i*w+j] = 0;
				else
					separated_regions[(counter-1)*w*h+i*w+j] = counter;
	//			printf("%d|", separated_regions[(counter-1)*w*h+i*w+j]);
			}
	//		printf("\n");
		}
	//	printf("\n\n"); //FIXME suppr printf
	}
	free(labeled_mat);
	return separated_regions;
}

void segment_positions(SDL_Surface *img, t_seg_computing *seg_pos)
{ 
	int *separated_regions = separate_regions(img);
	int nbSegments = get_nb_regions(img);
	int w = img->w;
	int h = img->h;
	for(int i = 0; i<nbSegments; i++)//initialisation pour i
	{ 
		seg_pos[i].posY2 = h+1;
		seg_pos[i].posX2 = w+1;
		seg_pos[i].posY1 = h+1;
		seg_pos[i].posX1 = w+1;
	}
	for(int k = 1; k<=nbSegments; k++)
	{ 
		for(int i = 0; i<h; i++)
		{ 
			for(int j = 0; j<w; j++)
			{ 
				if(separated_regions[(k-1)*w*h+i*w+j] == k)
				{
					if(seg_pos[k-1].posX2>j)
						seg_pos[k-1].posX2 = j;
					if(seg_pos[k-1].posY2>i)
						seg_pos[k-1].posY2 = i;
				}
			}
		}
	}
	for(int k = 1; k<=nbSegments; k++)
	{ 
		seg_pos[k-1].posX1 = seg_pos[k-1].posX2; 
		seg_pos[k-1].posY1 = seg_pos[k-1].posY2; 
		for(int i = 0; i<h; i++)
		{ 
			for(int j = 0; j<w; j++)
			{ 
				if(separated_regions[(k-1)*w*h+i*w+j] == k)
				{ 
					if(seg_pos[k-1].posX1<j)
						seg_pos[k-1].posX1 = j;
					if(seg_pos[k-1].posY1<i)
						seg_pos[k-1].posY1 = i;
				}
			}
		}
	}
	free(separated_regions);
}

void compute_dimension(SDL_Surface *img, t_seg_computing *seg_pos)
{ 
	int *separated_regions = separate_regions(img);
	int nbSegments = get_nb_regions(img);
	for(int k = 0; k<nbSegments; k++)
	{ 
		seg_pos[k].width = 0;
		seg_pos[k].height = 0;
		seg_pos[k].surface= 0;
		seg_pos[k].ratio= 0;
		seg_pos[k].width = seg_pos[k].posX1 - seg_pos[k].posX2;
		seg_pos[k].height = seg_pos[k].posY1 - seg_pos[k].posY2;
		float height = (float)seg_pos[k].height;
		float width = (float)seg_pos[k].width;
		seg_pos[k].ratio = height/width;	
		for(int i = 0; i<img->h; i++)
		{ 
			for(int j = 0; j<img->w; j++)
			{ 
				if(separated_regions[k*img->w*img->h + i*img->w+j] == k+1)
					seg_pos[k].surface+=1;
			}
		}
		
	}
	free(separated_regions);
}

void gravity_center(SDL_Surface *img, t_seg_computing *seg_pos)
{ 
	int nbSegments = get_nb_regions(img);
	int w = img->w;
	int h = img->h;
	int sumX, sumY = 0;
	int *separated_regions = separate_regions(img);
	for(int k = 0; k<nbSegments; k++)
	{ 
		for(int i = 0; i<h; i++)
		{ 
			for(int j = 0; j<w; j++)
			{
				sumX += j*separated_regions[k*w*h+i*w+j];
				sumY += i*separated_regions[k*w*h+i*w+j];
			}
		}
		seg_pos[k].gravCenterX = (1.0/seg_pos[k].surface)*sumX; 
		seg_pos[k].gravCenterY = (1.0/seg_pos[k].surface)*sumY; 
		sumX = 0;
		sumY = 0;
	}
	free(separated_regions);
}

void compute_on_image(SDL_Surface *img, t_seg_computing *seg_pos)
{ 
	int nbSegments = get_nb_regions(img);
	for(int i = 0; i<nbSegments; i++)
	{ 
		if(seg_pos[i].surface>10 && seg_pos[i].ratio>0.8 && seg_pos[i].ratio<1.8)
		{ 
			draw_square(img, seg_pos[i].posX2, seg_pos[i].posY2, seg_pos[i].width, seg_pos[i].height, 16711680);
			//sauvegarde les visages
			save_recognised(img, seg_pos[i].posX2, seg_pos[i].posY2, seg_pos[i].width, seg_pos[i].height);
		}
	}
}

void draw_square(SDL_Surface *img, int x1, int y1, int width, int height, Uint32 color)
{ 
	for(int i = x1; i<x1+width; i++)
		putpixel(img, i, y1, color);
	for(int i = y1; i<y1+height; i++)
		putpixel(img, x1+width, i, color);
	for(int i = x1+width; i>x1; i--)
		putpixel(img, i, y1+height, color);
	for(int i = y1+height; i>y1; i--)
		putpixel(img, x1, i,color);

}

//enregistre les visages encadrés
void save_recognised(SDL_Surface *img, int x1, int y1, int width, int height)
{
	SDL_Rect fillRect;
<<<<<<< HEAD
=======
	SDL_Surface *imgcopied = malloc(sizeof(SDL_Surface));
>>>>>>> e5f7b2824d22269ac9a0b1e96a529e95bcbee521
	fillRect.x = x1;
	fillRect.y = y1;
	fillRect.w = width;
	fillRect.h = height;
	SDL_Surface *imgcopied = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

<<<<<<< HEAD
	SDL_BlitSurface(img, &fillRect, imgcopied, NULL);
	SDL_SaveBMP(imgcopied, "./DataBase/save.bmp");
=======
	SDL_Rect destination;
	destination.x = 0;
	destination.y = 0;
	destination.w = width;
	destination.h = height;

	printf("ok");
	SDL_UnlockSurface(img);
	printf("ok");
	SDL_BlitSurface(img, &fillRect, imgcopied, &destination);
	SDL_LockSurface(img);
	SDL_SaveBMP(imgcopied,"copytruc.bmp");
	SDL_FreeSurface(imgcopied);
>>>>>>> e5f7b2824d22269ac9a0b1e96a529e95bcbee521
}

void face_detection()
{ 
	init_sdl();
	printf("%s\n", file_name);
	//char *file_name = path;
	SDL_Surface *img = load_image(file_name);
	int nbSegments = get_nb_regions(img);
	t_seg_computing *carac = malloc(nbSegments*sizeof(t_seg_computing));
	segment_positions(img, carac);
	compute_dimension(img, carac);
	gravity_center(img, carac);
	compute_on_image(img, carac);
	//display_image(img);
	free(carac);
	gtk_widget_destroy(pImage);
	
	SDL_SaveBMP(img, "copy.bmp");
	GdkPixbuf *pBuf = gdk_pixbuf_new_from_file_at_scale ("./copy.bmp",500,330,TRUE,NULL);
	pImage = gtk_image_new_from_pixbuf(pBuf);
	g_object_unref (pBuf);

	//permet de centrer l'image
	GdkPixbuf *pBufFcd = gtk_image_get_pixbuf (GTK_IMAGE(pImage));
	int w = gdk_pixbuf_get_width(pBufFcd);
	int h = gdk_pixbuf_get_height(pBufFcd);

	gtk_layout_put(GTK_LAYOUT(layout), pImage, 273-(w/2), 196-(h/2));  
	gtk_widget_show_all(pImage);

	//SDL_SaveBMP(img, "copy.bmp");
	SDL_FreeSurface(img);
}
