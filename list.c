#include "list.h"

/* Fonctions pour t_list_feature */

t_list_feature *empty_list_feature(){
	return NULL; 
}

int is_empty_feature(t_list_feature *l){
	return !l; 
}

t_list_feature *add_feature(t_feature *x, t_list_feature *l){
	t_list_feature *t = NULL; 
	t = malloc(FEATURE_SIZE); 
	t->feature = x; 
	t->next = l; 
	
	return l; 
}

void free_list_feature(t_list_feature *l){
	t_list_feature *tmp; 
	
	while(l){
		tmp = l->next; 
		free(l); 
		l = tmp; 
	}
}

/* Fonctions pour t_list_surface 

t_list_surface *empty_list_surface(){
	return NULL; 
}

int is_empty_surface(t_list_surface *l){
	return !l; 
}

t_list_surface *add_surface(SDL_Surface *x, t_list_surface *l){
	t_list_surface *t = NULL; 
	t = malloc(SURFACE_SIZE); 
	t->surface = x; 
	t->next = l; 

	return l; 
}

void free_list_surface(t_list_surface *l){
	t_list_surface *tmp; 

	while(l){
		tmp = l->next; 
		free(l); 
		l = tmp; 
	}
} */
