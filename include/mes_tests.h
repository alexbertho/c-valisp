/*
 * Ce fichier décrit tous les tests à votre disposition pour tester
 * vos fonctions.
 *
 * Pour pouvoir lancer un test, il faut activer la définition correspondante
 * dans le fichier test_config.h.
 *
 */

 #ifndef MES_TESTS_H
 #define MES_TESTS_H
 
 #include "test_config.h"
 
 /****************************************/
 /*                                      */
 /*  Tests pour le fichier allocateur.c  */
 /*                                      */
 /****************************************/
 
 void test_memoire_vide();
 void test_allocateurs_fonctions_de_base();
 void test_allocateur_malloc();
 void test_allocateur();
 
 /************************************/
 /*                                  */
 /*  Tests pour le fichier types.c   */
 /*                                  */
 /************************************/
 
 void test_entiers();
 void test_chaines();
 void test_symboles();
 void test_listes();
 void test_cons();
 void test_affichage_liste_cons();
 void test_types();
 
 /****************************************/
 /*                                      */
 /*  Tests pour le fichier primitives.c  */
 /*                                      */
 /****************************************/
 
 void test_add();
 void test_sub();
 void test_produit();
 void test_div();
 void test_mod();
 void test_comparaisons();
 void test_type_of();
 void test_car_cdr_cons();
 void test_print();
 void test_primitives();
 
 #endif /* MES_TESTS_H */