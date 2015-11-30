#include "classifier.h"
#include "constantes.h"
#include "feature_scaling.h"
#include "adaboost.h"

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

t_dec_stump *dec_stump(t_couple_images *img_set, t_feature *f)
{ 
	t_dec_stump *stump = malloc(sizeof(t_dec_stump));
	stump->threshold = f[0].param-1;
	stump->margin = 0;
	stump->error = 2;
	float weight_bigger_face = 0, weight_bigger_nonface = 0;
	float weight_lower_face = 0, weight_lower_nonface = 0;
	float errorplus, errorminus;
	float errormem, togglemem; 
	float thresholdmem = stump->threshold;
	float marginmem = stump->margin;
	int n = PICT_WITH_FACE + PICT_WITH_NO_FACE;
	int j = 0;
	for(int i = 1; i<n; i++)
	{ 
		if(f[i].face)
			weight_bigger_face+=f[i].weight;
		else
			weight_bigger_nonface+=f[i].weight;

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
			togglemem = 0;
		}
		if(errormem<=stump->error && marginmem>stump->margin)
		{ 
			stump->error = errormem;
			stump->threshold = thresholdmem;
			stump->margin = marginmem;
			stump->toggle = togglemem;
		}
		if(j==n)
			break;
		j+=1;
		for(;;)
		{ 
			if(!f[j].face)
			{ 
				weight_lower_nonface+=f[j].weight;
				weight_bigger_nonface-=f[j].weight;
			}
			else
			{ 
				weight_lower_face+=f[j].weight;
				weight_bigger_face-=f[j].weight;
			}
			if(j==n || ((f[j].param==f[j+1].param)&&(f[j].face==f[j+1].face)))
				break;
			else
				j+=1;
		}
		if(j==n)
		{ 
			thresholdmem = max(f,1);
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

t_dec_stump *best_stump(t_couple_image *img_set) //FIXM   ont leurs probabilistic weights sur eux a img_set[i].weight
{ 
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = SIZE;
	r.h = SIZE;
	t_dec_stump *beststump = malloc(sizeof(t_dec_stump));
	beststump->error = 2;
	for(int type = A; type<=E; type++){
		for(int i = r.y; i < r.y+r.h; i++){
			for(int j = r.x; j < r.x+r.w; j++){
				for(int w = 1; j+2*w-1 < r.x+r.w; w++){
					for(int h = 1; i+h-1 < r.y+r.h; h++){
						t_feature *feature_vect = malloc((PICT_WITH_FACE+PICT_WITH_NO_FACE)*sizeof(t_feature));
						for(int nbimages = 0; nbimages<PICT_WITH_FACE+PICT_WITH_NO_FACE; nbimages++)
						{ 
							feature_vect[nbimages].i=i; feature_vect[nbimages].j=j; feature_vect[nbimages].h=h; feature_vect[nbimages].w=w; feature_vect[nbimages].type=type;
							feature_scaling(img_set[nbimages].img, feature_vect+nbimages);
						}
						sort_features(feature_vect);
						printf("Call of decision stump type = %d ; i = %d ; j = %d ; w = %d ; h = %d\n", type, i, j, w, h); 
						t_dec_stump *tmp = dec_stump(img_set, feature_vect);

						if(tmp->error<beststump->error || ((tmp->error==beststump->error) && (tmp->margin>beststump->margin)))
							beststump = tmp;
						free(tmp);
						free(feature_vect);
					}
				}
			}
		}
	}

	FILE *f = fopen("class", "w"); 
	print_classifier(beststump, f); 
	fclose(f); 

	return beststump;
}
