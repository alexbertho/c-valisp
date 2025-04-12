#include <stdio.h>
#include <stddef.h>

#include "allocateur.h"

/* Accès aux définitions et variables externes de l'allocateur */
extern bloc MEMOIRE_DYNAMIQUE[];
extern int bloc_suivant(int i);
extern int bloc_precedant(int i);
extern int usage_bloc(int i);
extern int taille_bloc(int i);


void info_bloc(size_t i) {
    int t = taille_bloc(i);
    int p = bloc_precedant(i);
    int s = bloc_suivant(i);
    char * u = usage_bloc(i) ? "[x]" : "[ ]";

    printf("%-7s %-18p %7d → %7ld → %-7d (%6d)\n",
           u, (void *) &MEMOIRE_DYNAMIQUE[i], p, i, s, t);
}

void afficher_memoire() {
    int i;
    printf("%-7s %-7s %-18s %7s → %7s → %-7s %7s\n", 
           "[Indice]", "Reservé", "Adresse", "Precedent", "Courant", "Suivant", "(Taille)");
    printf("------------------------------------------------------------------------\n");
    
    for (i=0; bloc_suivant(i) != i; i = bloc_suivant(i)) {
        printf("[%5d] ", i);
        info_bloc(i);
    }
    printf("[%5d] ", i);
    info_bloc(i);
}

void afficher_stat_memoire() {
    size_t i = 0;
    int t = TAILLE_MEMOIRE_DYNAMIQUE;
    int n = 0;
    int b = 0;
    int a = 0;
    for (i=0; bloc_suivant(i) != i; i = bloc_suivant(i)) {
        n+=1;
        if (usage_bloc(i)) {
            a += taille_bloc(i) + 1;
            b += 1;
        }
    }
    printf("%d/%d (%.2f %%) %d/%d blocs alloués", a, t, (100.*a)/t, b,n);
}

void afficher_stat_memoire_bref() {
    size_t i = 0;
    int t = TAILLE_MEMOIRE_DYNAMIQUE;
    int n = 0;
    int b = 0;
    int a = 0;
    for (i=0; bloc_suivant(i) != i; i = bloc_suivant(i)) {
        n+=1;
        if (usage_bloc(i)) {
            a += taille_bloc(i) + 1;
            b += 1;
        }
    }
    printf("%.2f%%\n", (100.*a)/t);
}