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


float sum_negative_weights_bigger(t_feature *t, int threshold){
	float sum = 0;

	for(int i = 0; i < NB_FEATURES; i++){
		float w = t[i].weight;
		if(w > threshold)
			sum += w;
	}

	return sum;
}

float sum_positive_weights_bigger(t_feature *t, int threshold){
	float sum = 0;

	for(int i = 0; i < NB_FEATURES; i++){
		float w = t[i].weight;
		if(w > threshold)
			sum += w;
	}

	return sum;
}

float sum_positive_weights_lower(t_feature *t, int threshold){
	float sum = 0;

	for(int i = 0; i < NB_FEATURES; i++){
		float w = t[i].weight;
		if(w < threshold)
			sum += w;
	}

	return sum;
}

float sum(t_feature *t, int threshold, int positive){
	float sum = 0;

	for(int i = 0; i < NB_FEATURES; i++){
		float w = t[i].weight;
		if(positive && w < threshold)
			sum += w;
		if(!positive && w < threshold)
			sum += w;
	}

	return sum;
}

t_classifier *decision_stump(t_feature **img_set)
{ 
	int min = img_set[0]->param;

	for(int i = 0; i < PICT_WITH_FACE; i++){
		sort_features(img_set[i]);
		if(img_set[i][0].param < min)
			min = img_set[i]->param;
	}

	t_classifier *dec_stump = malloc(sizeof(t_classifier));
	dec_stump->threshold = min - 1;
	dec_stump->margin = 0;
	dec_stump->error = 2;
	float weights_minus, weights_plus, error_plus, error_minus;
	weights_plus = PICT_WITH_FACE * 0.5;
	weights_minus = 0;
	int j = 0;
	float tmp_threshold = dec_stump->threshold, tmp_margin = dec_stump->margin;
	//end init
	
	while(1){
		error_plus = 
	}

	return dec_stump;
	
}
