#include <stddef.h>
#include <stdint.h>

#ifndef ALLOCATEUR_H 
#define ALLOCATEUR_H

void initialiser_memoire_dynamique();
void *allocateur_malloc(size_t size);
void afficher_memoire();
void afficher_stat_memoire();
void afficher_stat_memoire_bref();
int ramasse_miette_lire_marque(void * ptr);
int ramasse_miette_poser_marque(void * ptr);
void ramasse_miette_liberer();
void allocateur_free (void * ptr);

#endif
