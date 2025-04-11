#include "allocateur.h"
#include "erreur.h"


void *valisp_malloc(size_t size) {
    void *ptr = allocateur_malloc(size);
    if (ptr == NULL) {
        ERREUR_FATALE("Mémoire remplis");
    }
    return ptr;
}

void ramasse_miette_parcourir_et_marquer(sexpr s) {
    sexpr a;
    a = car(s);
    if(ramasse_miette_lire_marque(a)) {
        return;
    }
    ramasse_miette_poser_marque(a);
    
}

void valisp_ramasse_miettes(sexpr env) {
    ramasse_miette_parcourir_et_marquer(env);
    ramasse_miette_liberer();
}