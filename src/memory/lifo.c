#include "types.h"
#include "environnement.h"
#include "allocateur.h"
#include "erreur.h"
#include "lifo.h"

sexpr PILE[TAILLE_PILE];  
int HAUT = 0;             

void init_pile(sexpr env) {
    PILE[0] = env;
    HAUT = 1;
}

int pile_nouveau_cadre(void) {
    return HAUT;
}

void pile_fin_cadre(int i) {
    if (i < 0 || i > HAUT) {
        ERREUR_FATALE("Position de pile invalide");
    }
    HAUT = i;
}

void pile_ajout(sexpr s) {
    if (HAUT >= TAILLE_PILE) {
        ERREUR_FATALE("Débordement de pile");
    }
    PILE[HAUT++] = s;
}