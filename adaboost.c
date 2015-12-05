#include "adaboost.h"

void adaboost(t_couple_image *img_set, int T){
	int count = 0; //FIXME
	float error = 0;
	FILE *file = fopen("strong_classifier", "w"); 
	for(int t = 0; t < T; t++){
		/*for(int i = 0; i<PICT_WITH_FACE+PICT_WITH_NO_FACE; i++)//FIXME
		{ 
			if(img_set[i].weight<0)   //regarde si ca a lieu avant ou apres t=2 (apparaissait avant) 
			{ 
				count++;
				printf("%d %lf\n", img_set[i].face, img_set[i].weight);
			}
		}
		*/
		t_dec_stump *ht = best_stump(img_set);
		t_feature *f = malloc(sizeof(t_feature));
		f->i=ht->i; f->j=ht->j, f->w=ht->w; f->h=ht->h; f->type=ht->type;
		for(int i = 0; i<PICT_WITH_FACE+PICT_WITH_NO_FACE; i++)
		{ 
			//if(ht->toggle!=img_set[i].face)
			//	error+=img_set[i].weight;
			feature_scaling(img_set[i].img, f);
			if(f->param<ht->threshold-ht->margin)
			{ 
				error+=img_set[i].weight;
				count++;
			}
			printf("count=misclassified : %d\n", count);
		}
		free(f);
		if(error == 0 && t==0)
		{ 
			fprintf(file, "%lf %d %d %d %d %d %d %d %d\n", ht->error, ht->threshold, ht->margin, ht->toggle, ht->i, ht->j, ht->w, ht->h, ht->type); 
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
		fprintf(file, "%lf %d %d %d %d %d %d %d %d\n", ht->error, ht->threshold, ht->margin, ht->toggle, ht->i, ht->j, ht->w, ht->h, ht->type); 
		printf("%lf %d %d %d %d %d %d %d %d\n", ht->error, ht->threshold, ht->margin, ht->toggle, ht->i, ht->j, ht->w, ht->h, ht->type); 

		free(ht);
		printf("t = %d\n", t); 
		//faire un break a la fin du 3 eme round(t=2) juste apres ht
	}
	fclose(file); 
}

t_dec_stump *get_strong_classifier(int T){
	FILE *file = fopen("strong_classifier", "r"); 
	t_dec_stump *sc = malloc(T*sizeof(t_dec_stump)); 

	if(file){
		for(int i = 0; i < T; i++){
			fscanf(file, "%f %d %d %d", &(sc[i].error), &(sc[i].threshold), &(sc[i].margin), &(sc[i].toggle)); //FIXME
		}	
	}

	fclose(file); 

	return sc;
}
