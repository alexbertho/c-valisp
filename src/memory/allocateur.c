#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "allocateur.h"
#include "erreur.h"
#include "lifo.h"


bloc MEMOIRE_DYNAMIQUE[TAILLE_MEMOIRE_DYNAMIQUE];

/* Adaptation pour utiliser 64 bits :
 * - bit 63 : rm (ramasse-miettes)
 * - bits 32-62 : precedant (31 bits)
 * - bit 31 : libre
 * - bits 0-30 : suivant (31 bits)
 */
bloc cons_bloc(int rm, int precedant, int libre, int suivant) {
    return ((uint64_t)rm << 63) | ((uint64_t)precedant << 32) | ((uint64_t)libre << 31) | (uint64_t)suivant;
}

void initialiser_memoire_dynamique() {
    bloc dernier_index = TAILLE_MEMOIRE_DYNAMIQUE - 1;

    MEMOIRE_DYNAMIQUE[0] = cons_bloc(0, 0, 0, dernier_index);
    MEMOIRE_DYNAMIQUE[dernier_index] = cons_bloc(0, 0, 1, dernier_index);
}

int bloc_suivant(int i) {
    return MEMOIRE_DYNAMIQUE[i] & 0x7FFFFFFF;
}

int bloc_precedant(int i) {
    return (MEMOIRE_DYNAMIQUE[i] >> 32) & 0x7FFFFFFF;
}

int usage_bloc(int i) {
    return (MEMOIRE_DYNAMIQUE[i] >> 31) & 1;
}

int rm_bloc(int i) {
    return (MEMOIRE_DYNAMIQUE[i] >> 63) & 1;
}

void set_use(int i) {
    MEMOIRE_DYNAMIQUE[i] = MEMOIRE_DYNAMIQUE[i] | ((uint64_t)1 << 31);
}

void set_free(int i) {
    MEMOIRE_DYNAMIQUE[i] = MEMOIRE_DYNAMIQUE[i] & ~((uint64_t)1 << 31);
}

void set_precedent(int a, int b) {
    int rm = rm_bloc(a);
    int libre = usage_bloc(a);
    int suivant = bloc_suivant(a);

    MEMOIRE_DYNAMIQUE[a] = cons_bloc(rm, b, libre, suivant);
}

void set_successeur(int a, int b) {
    int rm = rm_bloc(a);
    int precedent = bloc_precedant(a);
    int libre = usage_bloc(a);

    MEMOIRE_DYNAMIQUE[a] = cons_bloc(rm, precedent, libre, b);
}

int taille_bloc(int i) {
    int suivant = bloc_suivant(i);

    if(suivant==i){return 0;} /* S'il pointe sur lui meme */
    return suivant - i - 1;
}

int rechercher_bloc_libre(size_t size) {
    int i, n;

    for(i=0; bloc_suivant(i) != i; i = bloc_suivant(i)){
        if (!usage_bloc(i)) {
            n = taille_bloc(i);
            if (n*TAILLE_BLOC_OCTETS >= size) {
                return i;
            }
        }
    }

    return -1;
}

int pointeur_vers_indice(void *ptr) {
    int i = ((bloc *)ptr) - MEMOIRE_DYNAMIQUE;
    
    if (i <= 0 || i >= TAILLE_MEMOIRE_DYNAMIQUE) {
        ERREUR_FATALE("pointeur_vers_indice: pointeur invalide");
    }

    return i-1;
}

void *allocateur_malloc(size_t size) {
    int taille_dispo, suivant_original, nouveau_bloc;
    int nb_cases_necessaires = (size + TAILLE_BLOC_OCTETS - 1) / TAILLE_BLOC_OCTETS;
    int i = rechercher_bloc_libre(size);

    if (i == -1) {
        /* Pas de bloc libre trouvé */
        return NULL;
    }
    
    taille_dispo = taille_bloc(i);
    suivant_original = bloc_suivant(i);
    
    if (taille_dispo > nb_cases_necessaires + 1) {
        nouveau_bloc = i + nb_cases_necessaires + 1;
        
        MEMOIRE_DYNAMIQUE[nouveau_bloc] = cons_bloc(0, i, 0, suivant_original);
        
        MEMOIRE_DYNAMIQUE[i] = cons_bloc(0, bloc_precedant(i), 1, nouveau_bloc);
        
        if (suivant_original != i) { 
            MEMOIRE_DYNAMIQUE[suivant_original] = cons_bloc(
                rm_bloc(suivant_original),
                nouveau_bloc,
                usage_bloc(suivant_original),
                bloc_suivant(suivant_original)
            );
        }
    } else {
        /* Sinon, utiliser tout le bloc */
        set_use(i);
    }
    
    return &MEMOIRE_DYNAMIQUE[i + 1];
}

/* 
 * valeur de retour :
    1 : Le bloc est marqué, il sera sauvé
    0 : Le bloc n'est pas marqué, il sera libéré (free/suprimmé)
 */
int ramasse_miette_lire_marque(void *ptr) {
    int i = pointeur_vers_indice(ptr);
    
    return rm_bloc(i);
}

void ramasse_miette_poser_marque(void *ptr) {
    int i = pointeur_vers_indice(ptr);
    bloc *bloc_ptr = &MEMOIRE_DYNAMIQUE[i];

    if(ramasse_miette_lire_marque(ptr)) {
        ERREUR_FATALE("LE BLOC EST DEJA MARQUE");
    }

    *bloc_ptr |= ((uint64_t)1 << 63);  /* Activation du bit 63 */
}

int bloc_libre(int i) {
    if (i == bloc_suivant(i)) return 0;
    return !usage_bloc(i) && !rm_bloc(i); 
}

int free_fusion(int i) {
    int j, k;
    
    for (j = i; j != bloc_precedant(j); j = bloc_precedant(j)) {
        if (usage_bloc(bloc_precedant(j))) break;
    }
    
    for (k = bloc_suivant(i); k != bloc_suivant(k); k = bloc_suivant(k)) {
        if (usage_bloc(k)) break;
    }
    
    set_free(j);
    set_successeur(j, k);
    set_precedent(k, j);
    
    return k;
}

void reinitialiser_marques() {
    int i = 0;
    
    while (i != bloc_suivant(i)) {
        MEMOIRE_DYNAMIQUE[i] &= ~((uint64_t)1 << 63);
        i = bloc_suivant(i);
    }

    MEMOIRE_DYNAMIQUE[i] &= ~((uint64_t)1 << 63);
}

void ramasse_miette_liberer() {
    int i = 0;
    
    while (bloc_suivant(i) != i) {
        if (usage_bloc(i) && !rm_bloc(i)) {
            set_free(i);  /* Marquer comme libre */
            i = free_fusion(i);  
        } else {
            i = bloc_suivant(i);
        }
    }
}

void allocateur_free_bloc(int i) {
    free_fusion(i);
}

void allocateur_free(void *ptr) {
    int bloc_indice = (bloc *) ptr - MEMOIRE_DYNAMIQUE;
    int i;
    
    /*Maintenant on doit trouvé le bloc courrespondant c'est ne pas forcemment i-1*/
    for(i=0; bloc_indice <= bloc_suivant(i); i=bloc_suivant(i));
    allocateur_free_bloc(i);
}