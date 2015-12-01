#ifndef _ADABOOST_H_
#define _ADABOOST_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "classifier.h"
#include "constantes.h"
typedef struct s_strong_classifier t_strong_classifier;
struct s_strong_classifier{
	t_dec_stump strong_classifier[200];
};

t_strong_classifier *adaboost(t_couple_image *img_set, int T);

#endif
