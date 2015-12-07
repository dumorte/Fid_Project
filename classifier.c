#include "classifier.h"

int max(t_feature *f, int a)
{ 
	int maximum = f[0].param;
	for(int i=1; i<PICT_WITH_FACE+PICT_WITH_NO_FACE; i++)
	{ 
		if(f[i].param>maximum)
			maximum = f[i].param;
	}
	return maximum+a;
}

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
	qsort(f, PICT_WITH_FACE+PICT_WITH_NO_FACE, sizeof(t_feature), cmpfunc); 
	return f;
}

t_dec_stump *dec_stump(t_couple_image *img_set, t_feature *f)
{ 
	t_dec_stump *stump = malloc(sizeof(t_dec_stump));
	stump->i = f[0].i;
	stump->j = f[0].j;
	stump->w = f[0].w;
	stump->h = f[0].h;
	stump->type = f[0].type;
	stump->threshold = f[0].param-1;
	stump->margin = 0;
	stump->error = 2;
	stump->toggle = 0;
	float weight_bigger_face = 0, weight_bigger_nonface = 0;
	float weight_lower_face = 0, weight_lower_nonface = 0;
	float errorplus, errorminus;
	float errormem, togglemem; 
	float thresholdmem = stump->threshold;
	float marginmem = stump->margin;
	int n = PICT_WITH_FACE + PICT_WITH_NO_FACE;
	int j = 0;
	for(int i = 0; i<n; i++)
	{ 
		if(img_set[i].face == 1)
			weight_bigger_face+=img_set[i].weight;
		else
			weight_bigger_nonface+=img_set[i].weight;

	}

	for(;;)
	{ 
		errorplus = weight_lower_face + weight_bigger_nonface;
		errorminus = weight_bigger_face + weight_lower_nonface;
		if(errorplus<errorminus)
		{ 
			errormem = errorplus;
			togglemem = 1;
		}
		else
		{ 
			errormem = errorminus;
			togglemem = -1;
		}
		if(errormem<stump->error || (errormem==stump->error && marginmem>stump->margin))
		{ 
			stump->error = errormem;
			stump->threshold = thresholdmem;
			stump->margin = marginmem;
			stump->toggle = togglemem;
		}
		j++;
		if(j==n)
			break;
		for(;;)
		{ 
			if(f[j].face == -1)
			{ 
				weight_lower_nonface+=img_set[f[j].index].weight; //poids de l'image rattachee a la feature
				weight_bigger_nonface-=img_set[f[j].index].weight;
			}
			else
			{ 
				weight_lower_face+=img_set[f[j].index].weight;
				weight_bigger_face-=img_set[f[j].index].weight;
			}
			if(j==n-1 || f[j].param!=f[j+1].param)
				break;
			else
				j++;
		}
		if(j==n-1)
		{ 
			thresholdmem = f[j].param + 1;//max(f,1);
			marginmem=0;
		}
		else
		{ 
			thresholdmem = (f[j].param + f[j+1].param)/2;
			marginmem = f[j+1].param - f[j].param;
		}
	}
	return stump;
}

t_dec_stump *best_stump(t_couple_image *img_set) 
{ 
	t_dec_stump *beststump = malloc(sizeof(t_dec_stump));
	beststump->error = 2;
	for(int type = A; type<=E; type++){
		for(int i = 0; i < SIZE; i+=2){
			for(int j = 0; j < SIZE; j+=2){
				for(int w = 1; j+2*w-1 < SIZE; w++){
					for(int h = 1; i+h-1 < SIZE; h++){
						t_feature *feature_vect = malloc((PICT_WITH_FACE+PICT_WITH_NO_FACE)*sizeof(t_feature));
						for(int nbimages = 0; nbimages<PICT_WITH_FACE+PICT_WITH_NO_FACE; nbimages++)
						{ 
							feature_vect[nbimages].i=i; feature_vect[nbimages].j=j; feature_vect[nbimages].h=h; feature_vect[nbimages].w=w; feature_vect[nbimages].type=type; feature_vect[nbimages].face = img_set[nbimages].face; feature_vect[nbimages].index = nbimages;    
							feature_scaling(img_set[nbimages].img, feature_vect+nbimages);
						}
						sort_features(feature_vect);
						t_dec_stump *tmp = dec_stump(img_set, feature_vect);

						if(tmp->error<beststump->error || ((tmp->error==beststump->error) && (tmp->margin>beststump->margin)))
						{ 
							beststump->error = tmp->error;
							beststump->margin = tmp->margin;
							beststump->threshold= tmp->threshold;
							beststump->toggle = tmp->toggle;
							beststump->i = tmp->i;
							beststump->j = tmp->j;
							beststump->w = tmp->w;
							beststump->h = tmp->h;
							beststump->type = tmp->type;
						}
						free(tmp);
						free(feature_vect);
					}
				}
			}
		}
		printf("Type = %d\n", type); 
	}
	return beststump;
}

void print_classifier(t_dec_stump *dec, FILE *f){
	fprintf(f, "threshold=%d;toggle=%d;error=%lf;margin=%d\n", dec->threshold, dec->toggle, dec->error, dec->margin); 
}
