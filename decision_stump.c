#include "decision_stump.h"

/* Pour la fonction d'appel : 
 * int threshold = ... ; 
 * int toggle = ... ; 
 * int error = ... ; 
 * int margin = ... ; 
 * decision_stump(list_feature, &threshold, &toggle, &error, &margin */

/* "n training examples arranged in ascending order of feature pi_fx_i..." = on prend n images et pour chaque image on prend la feature f dans le vecteur des features. */

void decision_stump(t_list *list_feature, int *threshold, int *toggle, int *error, int *margin){
	/* *threshold = min(...) - 1;*/

	*margin = 0; 
	*error = 2; 


}
