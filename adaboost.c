#include "adaboost.h"

void print_classifier(t_dec_stump *dec, FILE *f){
	fprintf(f, "threshold=%lf;toggle=%lf;error=%lf;margin=%lf\n", dec->threshold, dec->toggle, dec->error, dec->margin); 
}

float sum_weights_images(t_couple_images *img)
{ 
	int sum = 0;
	for(int i = 0; i<PICT_WITH_FACE+PICT_WITH_NO_FACE; i++)
	{ 
		sum += img[i].weight;
	}
	return sum;
}

void adaboost(SDL_Surface *img_set, int T){
	float weights;
	float alphat;
	float error = 0;
	for(int t = 1; t < T; t++){
		error = sum_weights_images(img_set); //FIXME
		t_dec_stump *ht = best_stump(img_set); 
		if(error == 0 && t==1)
			return ht;
		else
		{ 
			alphat = 0.5*log((1.0-error)/error);
			for(int i = 0; i<PICT_WITH_FACE + PICT_WITH_NO_FACE; i++)
			{ 
				img_set[i].weight = img_set[i].weight/2
			}
		}
	}
}
