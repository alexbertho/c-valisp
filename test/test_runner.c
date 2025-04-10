#include <stdio.h>
#include "allocateur.h"
#include "erreur.h"
#include "string.h"
#include "types.h"
#include "tests.h"
#include "primitives.h"
#include "mes_tests.h"
#include "test_config.h"

/* Fonction principale pour exécuter tous les tests */
int main() {
    printf("\n============================================\n");
    printf("=              TESTS VALISP               =\n");
    printf("============================================\n\n");

    /* Tests de l'allocateur de mémoire */
    #ifdef TEST_ALLOCATEUR
    /*test_allocateur();*/
    #else
    #ifdef TEST_ALLOCATEUR_EX1
    test_memoire_vide();
    #endif
    #ifdef TEST_ALLOCATEUR_EX2
    test_allocateurs_fonctions_de_base();
    #endif
    #ifdef TEST_ALLOCATEUR_EX3
    test_allocateur_malloc();
    #endif
    #endif

    /* Tests des types */
    #ifdef TEST_TYPES
    /*test_types();*/
    #else
    #ifdef TEST_TYPES_ENTIER
    test_entiers(); 
    #endif
    #ifdef TEST_TYPES_CHAINE
    test_chaines();
    #endif
    #ifdef TEST_TYPES_SYMBOLE
    test_symboles(); 
    #endif
    #ifdef TEST_TYPES_LISTE
    test_listes();
    test_cons();
    test_affichage_liste_cons();
    #endif
    #endif

    /* Tests des primitives */
    #ifdef TEST_PRIMITIVES
    test_primitives();
    #else
    #ifdef TEST_PRIMITIVES_ADD
    test_add();
    #endif
    #ifdef TEST_PRIMITIVES_SUB
    test_sub();
    #endif
    #ifdef TEST_PRIMITIVES_PRODUIT
    test_produit();
    #endif
    #ifdef TEST_PRIMITIVES_DIV
    test_div();
    #endif
    #ifdef TEST_PRIMITIVES_MOD
    test_mod();
    #endif
    #ifdef TEST_PRIMITIVES_COMP
    test_comparaisons();
    #endif
    #ifdef TEST_PRIMITIVES_TYPEOF
    test_type_of();
    #endif
    #ifdef TEST_PRIMITIVES_LISTE
    test_car_cdr_cons();
    #endif
    #ifdef TEST_PRIMITIVES_PRINT
    test_print();
    #endif
    #endif

    printf("\n============================================\n");
    printf("=          TOUS LES TESTS PASSÉS          =\n");
    printf("============================================\n\n");

    return 0;
}