#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "types.h"

void test_nb_parametres(sexpr liste, char* fonction, int taille);

/* Primitives de base */
sexpr car_valisp(sexpr liste, sexpr env);
sexpr cdr_valisp(sexpr liste, sexpr env);
sexpr cons_valisp(sexpr liste, sexpr env);
sexpr add_valisp(sexpr liste, sexpr env);
sexpr less_than_valisp(sexpr liste, sexpr env);
sexpr sub_valisp(sexpr liste, sexpr env);
sexpr produit_valisp(sexpr liste, sexpr env);
sexpr div_valisp(sexpr liste, sexpr env);
sexpr mod_valisp(sexpr liste, sexpr env);
sexpr equal_valisp(sexpr liste, sexpr env);
sexpr print_valisp(sexpr liste, sexpr env);
sexpr println_valisp(sexpr liste, sexpr env);
sexpr type_of_valisp(sexpr liste, sexpr env);
sexpr defvar_valisp(sexpr liste, sexpr env);
sexpr setq_valisp(sexpr liste, sexpr env);

sexpr eval_valisp(sexpr liste, sexpr env);
sexpr apply_valisp(sexpr liste, sexpr env);

/* Formes speciales */
sexpr quote_valisp(sexpr liste, sexpr env);
sexpr lambda_valisp(sexpr liste, sexpr env);
sexpr macro_valisp(sexpr liste, sexpr env);
sexpr if_valisp(sexpr liste, sexpr env);

#endif