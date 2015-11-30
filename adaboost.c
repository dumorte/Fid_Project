#include "adaboost.h"

void print_classifier(t_dec_stump *dec, FILE *f){
	fprintf(f, "threshold=%lf;toggle=%lf;error=%lf;margin=%lf\n", dec->threshold, dec->toggle, dec->error, dec->margin); 
}

void adaboost(SDL_Surface **img_set){

	for(int i = 1; i < T; i++){
		t_dec_stump *stump = best_stump(img_set); 
			
	}
}
