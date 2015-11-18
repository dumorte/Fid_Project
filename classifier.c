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

float sum_weights(float *weight, t_example_images *ex_img)
{ 
	float x = 0;
	for(int t = 0; t<200; t++)
		for(int j = 0; j<ex_img->n; j++)
			x+=weight[t*ex_img->n + j];
	return x;
}

/*FIXME*/t_strong_classifier learning_classification(t_example_images *ex_img)
{ 
	struct t_example_image *cpy = ex_img;
	int T = 200;
	float *weight = malloc(T*ex_img->n*sizeof(int));//tableau de poids
	
	for(int i = 0; i<ex_img->n; i++)//initialize weights
	{ 
		if(ex_img->face)
			weight[i] = 1/PICT_WITH_FACE;
		else
			weight[i] = 1/PICT_WITH_NO_FACE;
		ex_img++;
	}
	ex_img = cpy;

	for(int t = 0; t<T; t++)
	{ 
		for(int i = 0; i<ex_img->n; i++)
		{ 
			//Normalize weights
			weight[t*ex_img->n + i] = weight[t*ex_img->n + i]/sum_weights(weight, ex_img);
			//

			ex_img++;
		}
	}	
	ex_img = cpy;

	free(ex_img);
}
