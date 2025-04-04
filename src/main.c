#include <stdio.h>
#include "allocateur.h"
#include "erreur.h"
#include "string.h"
#include "tests.h"
#include "primitives.h"
#include "mes_tests.h"


int main() {


    /* Pour tester les fonctions de la première séance */
    test_memoire_vide();
    test_allocateurs_fonctions_de_base();
    test_allocateur_malloc();


    /* Pour tester les fonctions de la seconde séance */
    test_entiers(); 
    test_chaines();
    test_symboles(); 
    test_listes();
    test_cons();

    test_affichage_liste_cons(); 
    test_add(); 


    /* Pour tester */

    /* afficher_titre("Test erreur fatale"); */
    /* ERREUR_FATALE("Aaaaaarrgh… l’erreur fatale m’a tuer"); */
    /* printf("Si je m‘affiche, c’est qu’il y a un problème avec mon erreur fatale"); */
    return 0;
}
