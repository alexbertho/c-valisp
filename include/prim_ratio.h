#ifndef PRIM_RATIO_H
#define PRIM_RATIO_H

#include "types.h"

sexpr ratio_valisp(sexpr liste, sexpr env);
sexpr numerator_valisp(sexpr liste, sexpr env); 
sexpr denominator_valisp(sexpr liste, sexpr env);

sexpr add_ratio(sexpr a, sexpr b);
sexpr sub_ratio(sexpr a, sexpr b);
sexpr mul_ratio(sexpr a, sexpr b);
sexpr div_ratio(sexpr a, sexpr b);
int equal_ratio(sexpr a, sexpr b);
int less_than_ratio(sexpr a, sexpr b);

#endif