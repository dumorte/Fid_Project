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

/*t_vector *sort_features(t_vector *v)
{ 
	qsort(v->tab, NB_FEATURES, sizeof(t_feature), cmpfunc); 
	for(int i = 0; i<NB_FEATURES; i++){
		printf("%d:              ", i);
		printf("%d\n", v->tab[i].param);
	}
	return v;
}*/

//t_classifier *decision_stump(/*tableau de t_vector nomme training_ex*/)
/*{ 
	t_vector *sorted_examples = sort_features(v);//tries
	free(v);
	t_classifier *dec_stump = malloc(sizeof(t_classifier));
	dec_stump->threshold = v->tab[0].param - 1;
	dec_stump->margin = 0;
	dec_stump->error = 2;
	//end init

	
}*/
