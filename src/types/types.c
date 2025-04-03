#include "types.h"
#include <stdio.h>
#include "memoire.h"
#include <string.h>

typedef enum {
    entier, 
    chaine, 
    symbole, 
    couple, 
    prim, 
    spec
} valisp_types;

typedef struct {
    sexpr car;
    sexpr cdr;
} valisp_cons;

typedef union {
    int INTEGER;
    char *STRING;
    valisp_cons CONS;
    sexpr (*PRIMITIVE) (sexpr, sexpr);
} valisp_data;

struct valisp_object {
    valisp_types type;
    valisp_data data;
};

/* ==============*/
/* PARTIE ENTIERS*/
/* ==============*/

sexpr new_integer(int i) {
    sexpr new_int=valisp_malloc(sizeof(struct valisp_object));
    new_int->type = entier;
    new_int->data.INTEGER = i;
    return new_int;
}

bool integer_p(sexpr val) {
    return (bool) ((val != NULL) && (val->type == entier));
}

int get_integer(sexpr val) {
    return val->data.INTEGER;
}

/* ==========================*/
/* PARTIE CHAINES ET SYMBOLES*/
/* ==========================*/

char *chaine_vers_memoire(const char *c) {
    size_t len = strlen(c), i;
    char *new_char = (char *)valisp_malloc(len + 1); 
    
    for (i=0; i<=len; i++) { 
        new_char[i] = c[i];
    }
    
    return new_char;
}

sexpr new_string(char *c) {
    sexpr new_char=valisp_malloc(sizeof(struct valisp_object));
    new_char->type = chaine;
    new_char->data.STRING = chaine_vers_memoire(c);
    return new_char;
}

sexpr new_symbol(char *c) {
    sexpr new_symbol; 
    if (strcmp(c, "nil") == 0) {return NULL;}

    new_symbol=valisp_malloc(sizeof(struct valisp_object));
    new_symbol->type = symbole;
    new_symbol->data.STRING = chaine_vers_memoire(c);
    return new_symbol;   
}

char *get_symbol(sexpr val) {
    return val->data.STRING;
}

char *get_string(sexpr val) {
    return val->data.STRING;
}

bool string_p(sexpr val) {
    return (bool) ((val != NULL) && (val->type == chaine));
}

bool symbol_p(sexpr val) {
    return (bool) ((val != NULL) && (val->type == symbole));
}

bool symbol_match_p(sexpr val, const char *chaine) {
    return (bool) strcmp(get_symbol(val), chaine) == 0;
}

/* =============*/
/* PARTIE LISTES*/
/* =============*/


void afficher(sexpr val) {
    if (val == NULL) {
        printf("nil");
        return;
    }
    switch (val->type) {
        case entier:
            printf("%d", get_integer(val));
            break;
        case chaine:
            printf("%s", get_string(val));
            break;
        case symbole: 
            printf("%s", get_symbol(val));
            break;
        case couple:
            break;
        default:
            break;
    }
}

