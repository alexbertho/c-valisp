#include <stdio.h>

#include "allocateur.h"
#include "erreur.h"
#include "types.h"

void *valisp_malloc(size_t size) {
    void *ptr = allocateur_malloc(size);

    if (ptr == NULL) {
        ramasse_miette_liberer();
        ptr = allocateur_malloc(size);
        if (ptr == NULL) {
            erreur(MEMOIRE, "malloc", "Allocation de mémoire échouée",NULL);
        }
    }
    
    return ptr;
}

void ramasse_miette_parcourir_et_marquer(sexpr s) {
    if (s == NULL) {
        return;
    }
    
    if (ramasse_miette_lire_marque(s)) {
        return;
    }
   
    ramasse_miette_poser_marque(s);
   
    if (cons_p(s)) {
        ramasse_miette_parcourir_et_marquer(car(s));
        ramasse_miette_parcourir_et_marquer(cdr(s));
    } else if (string_p(s) || symbol_p(s)) {
        char *str = string_p(s) ? get_string(s) : get_symbol(s);
        if (str != NULL) {
            ramasse_miette_poser_marque(str - 1);
        }
    } 
    /* Pour les entiers et primitives, il n'y a rien à faire */
}

void valisp_ramasse_miettes(sexpr env) {
    ramasse_miette_parcourir_et_marquer(env);
    ramasse_miette_liberer();
}