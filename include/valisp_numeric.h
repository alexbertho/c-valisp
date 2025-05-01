#ifndef VALISP_NUMERIC_H
#define VALISP_NUMERIC_H

#include <stdint.h>

typedef int64_t valisp_integer_t;

/*
 * Fonctions arithmétiques de base
 * Si nous passons à une implémentation de grands nombres personnalisée,
 * ces fonctions peuvent être modifiées sans changer l'interface.
 */
valisp_integer_t valisp_add(valisp_integer_t a, valisp_integer_t b);
valisp_integer_t valisp_sub(valisp_integer_t a, valisp_integer_t b);
valisp_integer_t valisp_mul(valisp_integer_t a, valisp_integer_t b);
valisp_integer_t valisp_div(valisp_integer_t a, valisp_integer_t b);
valisp_integer_t valisp_mod(valisp_integer_t a, valisp_integer_t b);

int valisp_eq(valisp_integer_t a, valisp_integer_t b);
int valisp_lt(valisp_integer_t a, valisp_integer_t b);
int valisp_gt(valisp_integer_t a, valisp_integer_t b);

valisp_integer_t valisp_from_string(const char *str);
char* valisp_to_string(valisp_integer_t num);

#endif 