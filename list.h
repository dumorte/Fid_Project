#ifndef _LIST_H_
#define _LIST_H_

#include <SDL/SDL.h>

#include "haar_feature.h"

/*
typedef struct s_lit_surface t_list_surface; 
struct s_list_surface {
	SDL_Surface *surface; 
	t_list_surface *next; 
};
*/

typedef struct s_list_feature t_list_feature; 
struct s_list_feature {
	t_feature *feature; 
	t_list_feature *next; 
};

#define FEATURE_SIZE sizeof(struct s_list_feature)
/* #define SURFACE_SIZE sizeof(struct s_list_surface) */

t_list_feature *empty_list_feature();
int is_empty_feature(t_list_feature *l); 
t_list_feature *add_feature(t_feature *x, t_list_feature *l); 
void free_list_feature(t_list_feature *l); 

/*
t_list_surface *empty_list_surface(); 
int is_empty_surface(t_list_surface *l); 
t_list_surface *add_surface(SDL_Surface *x, t_list_surface *l); 
void free_list_surface(t_list_surface *l); 
*/

#endif
