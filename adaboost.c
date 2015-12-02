#include "adaboost.h"


/*float sum_weights_images(t_couple_image *img)
{ 
	int sum = 0;
	for(int i = 0; i<PICT_WITH_FACE+PICT_WITH_NO_FACE; i++)
	{ 
		sum += img[i].weight;
	}
	return sum;
}*/

/*t_strong_classifier*/
void adaboost(t_couple_image *img_set, int T){
	float error = 0;
	t_strong_classifier *strong_classifier = malloc(sizeof(t_strong_classifier));
	FILE *f = fopen("strong_classifier", "w"); 
	for(int t = 0; t < T; t++){
		t_dec_stump *ht = best_stump(img_set);
		for(int i = 0; i<PICT_WITH_FACE+PICT_WITH_NO_FACE; i++)
		{ 
			if(ht->toggle!=img_set[i].face)
				error+=img_set[i].weight;
		}
		if(error == 0 && t==0) //FIXME
		{ 
			strong_classifier->strong_classifier[t].threshold = ht->threshold;
			strong_classifier->strong_classifier[t].margin = ht->margin;
			strong_classifier->strong_classifier[t].toggle = ht->toggle;
			strong_classifier->strong_classifier[t].error = ht->error;
			fprintf(f, "%lf %d %d %d\n", strong_classifier->strong_classifier[t].error, strong_classifier->strong_classifier[t].threshold, strong_classifier->strong_classifier[t].margin, strong_classifier->strong_classifier[t].toggle); 
			free(ht);
			//return strong_classifier;
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
		strong_classifier->strong_classifier[t].threshold = ht->threshold;
		strong_classifier->strong_classifier[t].margin = ht->margin;
		strong_classifier->strong_classifier[t].toggle = ht->toggle;
		strong_classifier->strong_classifier[t].error = ht->error;
		fprintf(f, "%lf %d %d %d\n", strong_classifier->strong_classifier[t].error, strong_classifier->strong_classifier[t].threshold, strong_classifier->strong_classifier[t].margin, strong_classifier->strong_classifier[t].toggle); 
		free(ht);
		printf("t = %d\n", t); 
	}
	//return strong_classifier;
	
	/*FILE *f = fopen("strong_classifier", "w"); 
	for(int i = 0; i < T; i++){
		fprintf(f, "%lf %d %d %d\n", strong_classifier->strong_classifier[i].error, strong_classifier->strong_classifier[i].threshold, strong_classifier->strong_classifier[i].margin, strong_classifier->strong_classifier[i].toggle); 
	}*/

	fclose(f); 
}
