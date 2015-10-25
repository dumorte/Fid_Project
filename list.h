#ifndef _LIST_H_
#define _LIST_H_

#include "haar_feature.h"

typedef struct s_list t_list; 
struct s_list {
	t_feature *elem; 
	t_list *next; 
};

#define LSIZE sizeof(struct s_list)

t_list *empty();
int is_empty(t_list *l); 
t_list *add(t_feature *x, t_list l); 
void free_list(t_list *l); 

#endif
