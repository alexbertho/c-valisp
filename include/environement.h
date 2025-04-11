#ifndef ENVIRONEMENT_H
#define ENVIRONEMENT_H

#include "types.h"

sexpr environnement_global(void);
void initialiser_memoire(void);
int trouver_variable(sexpr env, sexpr variable, sexpr *resultat);
int modifier_variable(sexpr env, sexpr variable, sexpr valeur);
void definir_variable_globale(sexpr variable, sexpr valeur);
void charger_une_primitive(char* nom, sexpr (*prim)(sexpr, sexpr));
void charger_une_speciale(char* nom, sexpr (*prim)(sexpr, sexpr));

#endif