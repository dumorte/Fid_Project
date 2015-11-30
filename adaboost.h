#ifndef _ADABOOST_H_
#define _ADABOOST_H_

#include <stdlib.h>
#include <stdio.h>

#include "classifier.h"

void print_classifier(t_dec_stump *dec, FILE *f); 
void adaboost(SDL_Surface **img_set);

#endif
