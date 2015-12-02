#ifndef _ADABOOST_H_
#define _ADABOOST_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "classifier.h"
#include "constantes.h"

t_dec_stump *adaboost(t_couple_image *img_set, int T);

#endif
