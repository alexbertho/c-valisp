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

/****************************************/
/*                                      */
/*  Tests pour le fichier prim_ratio.c  */
/*                                      */
/****************************************/

void test_prim_ratio();

/******************************************/
/*                                        */
/*  Tests pour le fichier environnement.c */
/*                                        */
/******************************************/

void test_initialiser_environnement();
void test_manipuler_environnement();


/***************************************/
/*                                     */
/*  Tests pour le fichier parseur.c    */
/*                                     */
/***************************************/

void test_parse_entier();
void test_parse_symbole();
void test_parse_chaine();
void test_parse_liste();
void test_parse_quote();
void test_nettoyer_espaces();
void test_parse_complexe();
void test_parse_erreurs();
void test_parseur();
 
#endif