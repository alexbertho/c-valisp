/*
 * Ce fichier décrit tous les tests à votre disposition pour tester
 * vos fonctions.
 *
 * Pour pouvoir lancer un test, il faut d’abord le décommenter daans
 * ce fichier ainsi que le #define le précédant puis de l’ajouter dans
 * votre fonction main.
 *
 */





/****************************************/
/*                                      */
/*  Tests pour le fichier allocateur.c  */
/*                                      */
/****************************************/



#define TEST_ALLOCATEUR_EX1
void test_memoire_vide();



#define TEST_ALLOCATEUR_EX2
void test_allocateurs_fonctions_de_base();



#define TEST_ALLOCATEUR_EX3
void test_allocateur_malloc();


/* Pour lancer les trois tests précédents */
#define TEST_ALLOCATEUR
void test_allocateur();



/************************************/
/*                                  */
/*  Tests pour le fichier types.c   */
/*                                  */
/************************************/


#define TEST_TYPES_ENTIER
void test_entiers();



#define TEST_TYPES_CHAINE
void test_chaines();



#define TEST_TYPES_SYMBOLE
void test_symboles();



#define TEST_TYPES_LISTE
void test_cons();
void test_listes();
void test_affichage_liste_cons();


/* Tous les tests précédents sur les types en une fonction*/

#define TEST_TYPES
void test_types();





/****************************************/
/*                                      */
/*  Tests pour le fichier primitives.c  */
/*                                      */
/****************************************/

/*
#define TEST_PRIMITIVES_ADD
void test_add();
*/
