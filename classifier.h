#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include "haar_feature.h"
#include <stdlib.h>
#include <stdio.h>

//#include "list.h"
#define min(a,b) (a<b?a:b)

typedef struct s_classifier t_classifier;
struct s_classifier {
	float threshold;
	float toggle;
	float error;
	float margin;
};

t_feature *sort_features(t_feature *feature);

#endif
