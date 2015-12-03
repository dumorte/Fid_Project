#include "adaboost.h"

void adaboost(t_couple_image *img_set, int T){
	float error = 0;
	float ht_error = 0; 
	int ht_threshold = 0, ht_margin = 0, ht_toggle = 0; 
	FILE *file = fopen("strong_classifier", "w"); 
	for(int t = 0; t < T; t++){
		t_dec_stump *ht = best_stump(img_set);
		for(int i = 0; i<PICT_WITH_FACE+PICT_WITH_NO_FACE; i++)
		{ 
			if(ht->toggle!=img_set[i].face)
				error+=img_set[i].weight;
		}
		if(error == 0 && t==0)
		{ 
			ht_error = ht->error; 
			ht_threshold = ht->threshold; 
			ht_margin = ht->margin; 
			ht_toggle = ht->toggle; 
			fprintf(file, "%lf %d %d %d\n", ht_error, ht_threshold, ht_margin, ht_toggle); 
			free(ht);
			break;
		}
		else
		{ 
			//alphat = 0.5*log((1.0-error)/error);
			for(int i = 0; i<PICT_WITH_FACE + PICT_WITH_NO_FACE; i++)
			{ 
				img_set[i].weight = (img_set[i].weight/2);
				if(ht->toggle!=img_set[i].face)
					img_set[i].weight*=1.0/error;
				else
					img_set[i].weight*=1.0/(1-error);

			}
		}
		ht_error = ht->error; 
		ht_threshold = ht->threshold; 
		ht_margin = ht->margin; 
		ht_toggle = ht->toggle; 
		fprintf(file, "%lf %d %d %d\n", ht_error, ht_threshold, ht_margin, ht_toggle); 
		free(ht);
		printf("t = %d\n", t); 
	}
	fclose(file); 
}

t_dec_stump *get_strong_classifier(int T){
	FILE *file = fopen("strong_classifier", "r"); 
	t_dec_stump *sc = malloc(T*sizeof(t_dec_stump)); 

	if(file){
		for(int i = 0; i < T; i++){
			fscanf(file, "%f %d %d %d", &(sc[i].error), &(sc[i].threshold), &(sc[i].margin), &(sc[i].toggle)); 
		}	
	}

	fclose(file); 

	return sc;
}
