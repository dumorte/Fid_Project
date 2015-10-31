#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include "haar_feature.h"
#include <stdlib.h>
#include <stdio.h>

//#include "list.h"
#define min(a,b) (a<b?a:b)

typedef struct s_classifier t_classifier;
struct s_classifier {
	int threshold;
	int toggle;
	int error;
	int margin;
};

t_vector *sort_features(t_vector *v);

#endif
