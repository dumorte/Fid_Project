#include "adaboost.h"

void adaboost(t_couple_image *img_set, int T){
	float error = 0;
	FILE *f = fopen("strong_classifier", "w"); 
	for(int t = 0; t < T; t++){
		t_dec_stump *ht = best_stump(img_set);
		for(int i = 0; i<PICT_WITH_FACE+PICT_WITH_NO_FACE; i++)
		{ 
			if(ht->toggle!=img_set[i].face)
				error+=img_set[i].weight;
		}
		if(error == 0 && t==0)
		{ 
			fprintf(f, "%lf %d %d %d\n", ht->error, ht->threshold, ht->margin, ht->toggle); 
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
		fprintf(f, "%lf %d %d %d\n", ht->error, ht->threshold, ht->margin, ht->toggle); 
		free(ht);
		printf("t = %d\n", t); 
	}
	fclose(f); 
}
