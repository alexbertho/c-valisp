#ifndef LIFO_H
#define LIFO_H

#include "types.h"
#include "allocateur.h"

#define TAILLE_PILE TAILLE_MEMOIRE_DYNAMIQUE

void init_pile(sexpr env);
int pile_nouveau_cadre(void);
void pile_fin_cadre(int i);
void pile_ajout(sexpr s);


#endif