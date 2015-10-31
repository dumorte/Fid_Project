#include "classifier.h"

int cmpfunc (const void * a, const void * b)
{
	if (((t_feature*)a)->param < ((t_feature*)b)->param)
		return -1;
	else if((((t_feature*)a)->param > ((t_feature*)b)->param))
		return 1;
	else
		return 0;
}

t_vector *sort_features(t_vector *v)
{ 
	qsort(v->tab, NB_FEATURES, sizeof(t_feature), cmpfunc); 
	for(int i = 0; i<NB_FEATURES; i++){
		printf("%d:              ", i);
		printf("%d\n", v->tab[i].param);
	}
	return v;
}

//initialiser weights lors de la creation des features
