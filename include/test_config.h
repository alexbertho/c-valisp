/**
* Configuration des tests Valisp
* 
* Ce fichier permet d'activer/désactiver des groupes de tests
* en décommentant les définitions correspondantes.
*/

#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H
 
/* Activation des groupes de tests pour l'exécution */
#define TEST_ALLOCATEUR    
#define TEST_TYPES         
#define TEST_PRIMITIVES    
#define TEST_PARSEUR
 
/* Configuration des tests individuels pour l'allocateur */
#ifdef TEST_ALLOCATEUR
    #define TEST_ALLOCATEUR_EX1
    #define TEST_ALLOCATEUR_EX2
    #define TEST_ALLOCATEUR_EX3
#endif
 
/* Configuration des tests individuels pour les types */
#ifdef TEST_TYPES
    #define TEST_TYPES_ENTIER
    #define TEST_TYPES_CHAINE
    #define TEST_TYPES_SYMBOLE
    #define TEST_TYPES_LISTE
#endif

/* Configuration des tests individuels pour les primitives */
#ifdef TEST_PRIMITIVES
    #define TEST_PRIMITIVES_ADD
    #define TEST_PRIMITIVES_SUB
    #define TEST_PRIMITIVES_PRODUIT
    #define TEST_PRIMITIVES_DIV
    #define TEST_PRIMITIVES_MOD
    #define TEST_PRIMITIVES_COMP
    #define TEST_PRIMITIVES_TYPEOF
    #define TEST_PRIMITIVES_LISTE
    #define TEST_PRIMITIVES_PRINT
#endif

#ifdef TEST_PARSEUR
    #define TEST_PARSEUR_ENTIER
    #define TEST_PARSEUR_SYMBOLE
    #define TEST_PARSEUR_CHAINE
    #define TEST_PARSEUR_LISTE
    #define TEST_PARSEUR_QUOTE
    #define TEST_PARSEUR_ESPACE
    #define TEST_PARSEUR_COMPLEXE
    #define TEST_PARSEUR_ERREURS
#endif


/*
* Pour activer uniquement certains tests individuels sans activer tout le groupe,
* commentez la définition du groupe correspondant ci-dessus, puis décommentez
* les tests individuels souhaités ci-dessous.
*/
 
/* Tests individuels pour l'allocateur (si TEST_ALLOCATEUR est commenté) */
/* #define TEST_ALLOCATEUR_EX1 */
/* #define TEST_ALLOCATEUR_EX2 */
/* #define TEST_ALLOCATEUR_EX3 */

/* Tests individuels pour les types (si TEST_TYPES est commenté) */
/* #define TEST_TYPES_ENTIER */
/* #define TEST_TYPES_CHAINE */
/* #define TEST_TYPES_SYMBOLE */
/* #define TEST_TYPES_LISTE */
 
/* Tests individuels pour les primitives (si TEST_PRIMITIVES est commenté) */
/* #define TEST_PRIMITIVES_ADD */
/* #define TEST_PRIMITIVES_SUB */
/* #define TEST_PRIMITIVES_PRODUIT */
/* #define TEST_PRIMITIVES_DIV */
/* #define TEST_PRIMITIVES_MOD */
/* #define TEST_PRIMITIVES_COMP */
/* #define TEST_PRIMITIVES_TYPEOF */
/* #define TEST_PRIMITIVES_LISTE */
/* #define TEST_PRIMITIVES_PRINT */
 
#endif /* TEST_CONFIG_H */