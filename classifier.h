#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include "haar_feature.h"
#include <stdlib.h>
#include <stdio.h>

//#include "list.h"

typedef struct s_classifier t_classifier;
struct s_classifier {
	float threshold, toggle, error, margin;
};

t_feature *sort_features(t_feature *feature);

#endif
