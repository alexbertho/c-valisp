#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "valisp_numeric.h"
#include "erreur.h"
#include "memoire.h"

/* 
 * Pour l'instant, ces fonctions sont de simples wrappers autour des
 * opérations natives sur int64_t. Si nous passons à une implémentation
 * de grands nombres, ces fonctions contiendront la logique nécessaire.
 */

valisp_integer_t valisp_add(valisp_integer_t a, valisp_integer_t b) {
    return a + b;
}

valisp_integer_t valisp_sub(valisp_integer_t a, valisp_integer_t b) {
    return a - b;
}

valisp_integer_t valisp_mul(valisp_integer_t a, valisp_integer_t b) {
    return a * b;
}

valisp_integer_t valisp_div(valisp_integer_t a, valisp_integer_t b) {
    if (b == 0) {
        erreur(DIVISION_PAR_ZERO, "valisp_div", "Division par zéro", NULL);
    }
    return a / b;
}

valisp_integer_t valisp_mod(valisp_integer_t a, valisp_integer_t b) {
    if (b == 0) {
        erreur(DIVISION_PAR_ZERO, "valisp_mod", "Modulo par zéro", NULL);
    }
    return a % b;
}

int valisp_eq(valisp_integer_t a, valisp_integer_t b) {
    return a == b;
}

int valisp_lt(valisp_integer_t a, valisp_integer_t b) {
    return a < b;
}

int valisp_gt(valisp_integer_t a, valisp_integer_t b) {
    return a > b;
}

valisp_integer_t valisp_from_string(const char *str) {
    valisp_integer_t result = 0;
    int sign = 1;
    const char* p = str;
    
    if (*p == '-') {
        sign = -1;
        p++;
    } else if (*p == '+') {
        p++;
    }
    
    /* Convertir les chiffres */
    while (*p >= '0' && *p <= '9') {
        result = result * 10 + (*p - '0');
        p++;
    }
    
    return result * sign;
}

/*******************************************************************************
 * ATTENTION: Cette fonction alloue de la mémoire avec malloc!
 * L'appelant est responsable de libérer cette mémoire avec free()
 * après utilisation pour éviter les fuites de mémoire.
 *
 * Exemple d'utilisation correcte:
 *   char* str = int_to_str(123);
 *   printf("%s\n", str);
 *   free(str);  // IMPORTANT: libérer la mémoire!
 *
 * Le non-respect de cette règle entraînera des fuites de mémoire.
 *******************************************************************************
 */
char *int_to_str(valisp_integer_t num) {
    char buffer[32]; /* Assez grand pour un int64_t */
    char* p = buffer + sizeof(buffer) - 1;
    int is_negative = 0;
    size_t len;
    char* result;
    
    if (num == 0) {
        result = (char*)malloc(2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    
    *p = '\0';
    p--;
    
    /* Convertir les chiffres de droite à gauche */
    while (num > 0) {
        *p = '0' + (num % 10);
        num /= 10;
        p--;
    }
    
    if (is_negative) {
        *p = '-';
        p--;
    }
    
    len = (buffer + sizeof(buffer) - 1) - (p + 1);
    result = (char*)malloc(len + 1);
    
    strcpy(result, p + 1);
    
    return result;
}

/*******************************************************************************
 * ATTENTION: Cette fonction alloue de la mémoire avec malloc!
 * L'appelant est responsable de libérer cette mémoire avec free()
 * après utilisation pour éviter les fuites de mémoire.
 *******************************************************************************
 */
char *valisp_to_string(valisp_integer_t num) {
    return int_to_str(num);
}

/*******************************************************************************
 * ATTENTION: Cette fonction alloue de la mémoire avec malloc!
 * L'appelant est responsable de libérer cette mémoire avec free()
 * après utilisation pour éviter les fuites de mémoire.
 *******************************************************************************
 */
char *valisp_ratio_to_string(valisp_integer_t num, valisp_integer_t denom) {
    char *num_str, *denom_str;
    char *result;
    size_t len_num, len_denom, len_total;
    
    /* Gérer le cas où le dénominateur est 1 */
    if (denom == 1) {
        return int_to_str(num);
    }
    
    /* Gérer le cas où le numérateur est 0 */
    if (num == 0) {
        result = (char*)malloc(2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    
    /* Appliquer le signe au numérateur si le dénominateur est négatif */
    if (denom < 0) {
        num = -num;
        denom = -denom;
    }
    
    num_str = int_to_str(num);
    denom_str = int_to_str(denom);
    
    len_num = strlen(num_str);
    len_denom = strlen(denom_str);
    len_total = len_num + len_denom + 2; /* +2 pour '/' et '\0' */
    
    result = (char*)malloc(len_total);
    
    strcpy(result, num_str);
    strcat(result, "/");
    strcat(result, denom_str);
    
    free(num_str);
    free(denom_str);
    
    return result;
}