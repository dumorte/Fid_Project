#include "list.h"

t_list *empty(){
	return NULL; 
}

int is_empty(t_list *l){
	return !l; 
}

t_list *add(t_feature *x, t_list l){
	t_list *t = NULL; 
	t = malloc(LSIZE); 
	t->elem = x; 
	t->next = l; 
	
	return l; 
}

void free_list(t_list *l){
	t_list *tmp; 
	
	while(l){
		tmp = l->next; 
		free(l); 
		l = tmp; 
	}
}
