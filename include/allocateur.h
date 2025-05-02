#ifndef ALLOCATEUR_H 
#define ALLOCATEUR_H

#include <stddef.h>
#include <stdint.h>

#define TAILLE_MEMOIRE_DYNAMIQUE (1<<24) 
#define TAILLE_BLOC_OCTETS sizeof(bloc) 

typedef uint64_t bloc;

void initialiser_memoire_dynamique();
void *allocateur_malloc(size_t size);
void afficher_memoire();
void afficher_stat_memoire();
void afficher_stat_memoire_bref();
int pointeur_vers_indice(void *ptr);
int ramasse_miette_lire_marque(void *ptr);
void reinitialiser_marques();
void ramasse_miette_poser_marque(void *ptr);
void ramasse_miette_liberer();
void allocateur_free (void *ptr);

#endif