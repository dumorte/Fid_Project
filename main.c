#include <err.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pixel_operations.h"
#include "integral_image.h"
#include "haar_feature.h"
#include "classifier.h"
#include "constantes.h"
#include "feature_scaling.h"
#include "adaboost.h"

void wait_for_keypressed(void);
void init_sdl(void);
SDL_Surface *load_image(char *path);
SDL_Surface *display_image(SDL_Surface *img);


int main(/*int argc, char **argv*/){
	/*if(argc < 2)
		errx(2, "Usage: %s <image path>\n", argv[0]);
	*/
	/*SDL_Surface *img = NULL;

	init_sdl();
	img = load_image("/home/epita/Desktop/Fid_Project/newface24/face24_000200.jpg");
	display_image(img);*/
	//display_image(grey_level(img));
	/*SDL_Rect p;
	p.w = 24;
	p.h = 24;
	SDL_Surface *s = SDL_CreateRGBSurface(0, p.w, p.h, 32, 0, 0, 0, 0);
	SDL_FillRect(s, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

	for(int i = 0; i < img->h-24; i++){
		for(int j = 0; j < img->w-24; j++){
			t_vector *v = feature_vect(img, i, j); 
			p.x = j;
			p.y = i;
			SDL_BlitSurface(s, NULL, screen, &p);
			SDL_Flip(screen);
			free(v);
		}
	}

	SDL_FreeSurface(s);*/
	//SDL_FreeSurface(img);

	t_couple_image *img_set= malloc((PICT_WITH_FACE+PICT_WITH_NO_FACE) * sizeof(SDL_Surface));
	FILE *f = fopen("nameface", "r");
	char *name_picture = malloc(64 * sizeof(char));
	int i = 0;

	while(fgets(name_picture, 60, f) != NULL){
		img_set[i].img = grey_level(load_image(name_picture));
		img_set[i].face = 1;
		img_set[i].weight = 1.0/(2*PICT_WITH_FACE);
		printf("%d\n",i);
		i++;
		fseek(f, 1, SEEK_CUR);
	}
	
	f = fopen("namenonface", "r");
	while(fgets(name_picture, 63, f) != NULL){
		img_set[i].img = grey_level(load_image(name_picture));
		img_set[i].face = -1;
		img_set[i].weight = 1.0/(2*PICT_WITH_NO_FACE);
		printf("%d\n",i);
		i++;
		fseek(f, 1, SEEK_CUR); 
	}
	fclose(f);
	//adaboost(img_set, 4);//FIXME 100
	integral_image_matrix(img_set[0].img);
	/*t_feature *feat = feature_vect(img_set[0].img);
	for(int i = 0; i<NB_FEATURES; i++)
		printf("%d\n", feat[i].param);
	*/
	//Do what we want
	/*SDL_Surface *img = grey_level(load_image("/home/epita/Desktop/Fid_Project/newface24/face24_000200.jpg"));
	t_feature *feature = malloc(sizeof(t_feature));
	feature->i=0; feature->j=0; feature->h=4; feature->w=1; feature->type=A;
	feature_scaling(img, feature);
	t_feature *vect = feature_vect(img);
	free(vect);
	free(feature);*/
	/*for(int i = 0; i < PICT_WITH_FACE; i++)
		free(img_set[i]);
	free(img_set);*/
	/*SDL_Surface *img = grey_level(load_image("/home/epita/Desktop/Fid_Project/nonface24/nonface24_000011.jpg"));
	//SDL_Surface *img = grey_level(load_image("/home/epita/Desktop/Fid_Project/newface24/face24_000199.jpg"));
	t_dec_stump *stump = malloc(sizeof(t_dec_stump));
	stump->error = 0.112500;
	stump->margin = 1250067;
	stump->threshold = 26679060;
	stump->toggle = 1;
	t_feature *vect = feature_vect(img);
	for(int i = 0; i<NB_FEATURES; i++)
	{ 
		if(vect[i].param<stump->threshold + stump->margin && vect[i].param > stump->threshold - stump->margin)
		{ 
			printf("OK\n");
		}
	}*/
	return 0;
}

void wait_for_keypressed(void) {
	SDL_Event event;
	// Infinite loop, waiting for event
	for (;;) {
		// Take an event
		SDL_PollEvent( &event );
		// Switch on event type
		switch (event.type) {
			// Someone pressed a key -> leave the function
			case SDL_KEYDOWN: 
				return;
			default:
				 break;
	    	}
		// Loop until we got the expected event
	}
}

void init_sdl(void) {
	// Init only the video part
	if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
		// If it fails, die with an error message
		errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
	}

	// We don't really need a function for that ...
}

SDL_Surface* load_image(char *path) {
	SDL_Surface *img;

	// Load an image using SDL_image with format detection
	img = IMG_Load(path);
	if (!img)
		// If it fails, die with an error message
		errx(3, "can't load %s: %s", path, IMG_GetError());
	return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
	SDL_Surface *screen;

	// Set the window to the same size as the image
	// img->w, img->h
	screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);

	if ( screen == NULL ) {
		// error management
		errx(1, "Couldn't set %dx%d video mode: %s\n",
		img->w, img->h, SDL_GetError());
	}
 
	/* Blit onto the screen surface */
	if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
		warnx("BlitSurface error: %s\n", SDL_GetError());
 
	// Update the screen
	SDL_UpdateRect(screen, 0, 0, img->w, img->h);
 
	// wait for a key
	wait_for_keypressed();
 
	// return the screen for further uses
	 return screen;
}
