#include <stdio.h>

#include "allocateur.h"
#include "erreur.h"
#include "types.h"


void *valisp_malloc(size_t size) {
    void *ptr = allocateur_malloc(size);
    if (ptr == NULL) {
        ERREUR_FATALE("Mémoire remplis");
    }
    return ptr;
}

void ramasse_miette_parcourir_et_marquer(sexpr s) {
    if (s == NULL || ramasse_miette_lire_marque(s)) {
        return;
    }
    
    ramasse_miette_poser_marque(s);
    
    /* En fonction du type de s, on parcourt récursivement */
    if (cons_p(s)) {
        /* Si c'est une liste/cons, on parcourt le car et le cdr */
        ramasse_miette_parcourir_et_marquer(car(s));
        ramasse_miette_parcourir_et_marquer(cdr(s));
    } else if (string_p(s) || symbol_p(s)) {
        /* Pour les chaînes et symboles, il faut marquer le pointeur vers la chaîne */
        char *str = string_p(s) ? get_string(s) : get_symbol(s);
        if (str != NULL) {
            ramasse_miette_poser_marque(str - 1); /* -1 car le bloc est avant le pointeur */
        }
    }
    /* Pour les entiers et primitives, pas besoin de parcourir davantage */
}

void valisp_ramasse_miettes(sexpr env) {
    ramasse_miette_parcourir_et_marquer(env);
    ramasse_miette_liberer();
}