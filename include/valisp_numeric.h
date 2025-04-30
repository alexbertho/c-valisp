#ifndef VALISP_NUMERIC_H
#define VALISP_NUMERIC_H

#include <stdint.h>

/* 
 * Type d'entier utilisé dans Valisp.
 * Actuellement défini comme int64_t, mais pourrait être remplacé
 * ultérieurement par une structure pour les grands nombres.
 * 
 * Note: Nous utilisons int64_t même en C90, car c'est défini dans stdint.h 
 * qui est inclus ici. En interne, nous éviterons d'utiliser des fonctionnalités
 * C99 comme printf("%lld") ou long long.
 */
typedef int64_t valisp_integer_t;

/*
 * Fonctions arithmétiques de base
 * Si nous passons à une implémentation de grands nombres personnalisée,
 * ces fonctions peuvent être modifiées sans changer l'interface.
 */

/* Addition de deux entiers Valisp */
valisp_integer_t valisp_add(valisp_integer_t a, valisp_integer_t b);

/* Soustraction de deux entiers Valisp */
valisp_integer_t valisp_sub(valisp_integer_t a, valisp_integer_t b);

/* Multiplication de deux entiers Valisp */
valisp_integer_t valisp_mul(valisp_integer_t a, valisp_integer_t b);

/* Division de deux entiers Valisp */
valisp_integer_t valisp_div(valisp_integer_t a, valisp_integer_t b);

/* Modulo de deux entiers Valisp */
valisp_integer_t valisp_mod(valisp_integer_t a, valisp_integer_t b);

/* Comparaison d'égalité */
int valisp_eq(valisp_integer_t a, valisp_integer_t b);

/* Comparaison inférieur */
int valisp_lt(valisp_integer_t a, valisp_integer_t b);

/* Comparaison supérieur */
int valisp_gt(valisp_integer_t a, valisp_integer_t b);

/* Conversion d'une chaîne en entier Valisp (compatible ANSI C) */
valisp_integer_t valisp_from_string(const char* str);

/* Conversion d'un entier Valisp en chaîne (compatible ANSI C) */
char* valisp_to_string(valisp_integer_t num);

#endif /* VALISP_NUMERIC_H */