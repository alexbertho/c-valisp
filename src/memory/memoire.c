#include "allocateur.h"
#include "erreur.h"


void *valisp_malloc(size_t size) {
    void *ptr = allocateur_malloc(size);
    if (ptr == NULL) {
        ERREUR_FATALE("Mémoire remplis");
    }
    return ptr;
}


