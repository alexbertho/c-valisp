/**
 * Configuration des tests Valisp
 * 
 * Ce fichier permet d'activer/désactiver des groupes de tests
 * en décommentant les définitions correspondantes.
 */

 #ifndef TEST_CONFIG_H
 #define TEST_CONFIG_H
 
 /* Activation de tous les tests individuels pour la compilation */
 #define TEST_ALLOCATEUR_EX1
 #define TEST_ALLOCATEUR_EX2
 #define TEST_ALLOCATEUR_EX3
 #define TEST_TYPES_ENTIER
 #define TEST_TYPES_CHAINE
 #define TEST_TYPES_SYMBOLE
 #define TEST_TYPES_LISTE
 #define TEST_PRIMITIVES_ADD
 #define TEST_PRIMITIVES_SUB
 #define TEST_PRIMITIVES_PRODUIT
 #define TEST_PRIMITIVES_DIV
 #define TEST_PRIMITIVES_MOD
 #define TEST_PRIMITIVES_COMP
 #define TEST_PRIMITIVES_TYPEOF
 #define TEST_PRIMITIVES_LISTE
 #define TEST_PRIMITIVES_PRINT
 
 /* Activation des groupes de tests pour l'exécution */
 #define TEST_ALLOCATEUR    /* Active tous les tests d'allocateur */
 #define TEST_TYPES         /* Active tous les tests de types */
 #define TEST_PRIMITIVES    /* Active tous les tests de primitives */
 
 #endif /* TEST_CONFIG_H */