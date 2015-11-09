#include "classifier.h"
#include "constantes.h"

int cmpfunc (const void * a, const void * b)
{
	if (((t_feature*)a)->param < ((t_feature*)b)->param)
		return -1;
	else if((((t_feature*)a)->param > ((t_feature*)b)->param))
		return 1;
	else
		return 0;
}

t_feature *sort_features(t_feature *f)
{ 
	qsort(f, NB_FEATURES, sizeof(t_feature), cmpfunc); 
	return f;
}


t_classifier *decision_stump(t_feature **img_set)
{ 
	for(int i = 0; i < PICT_WITH_FACE; i++){
		sort_features(img_set[i]);
	}
	t_classifier *dec_stump = malloc(sizeof(t_classifier));
	dec_stump->threshold = img_set[0]->param - 1;
	dec_stump->margin = 0;
	dec_stump->error = 2;
	//end init

	return dec_stump;
	
}
