#ifndef INTERPRETEUR_H
#define INTERPRETEUR_H

#include "types.h"

sexpr apply(sexpr fonction, sexpr liste, sexpr env);
sexpr eval(sexpr val, sexpr env);
sexpr eval_list(sexpr V, sexpr env);
sexpr bind(sexpr variables, sexpr liste, sexpr env);

#endif
