#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "valisp_numeric.h"
#include "memoire.h"
#include "erreur.h"

typedef enum {
    entier,
    ratio, 
    chaine,
    symbole, 
    couple, 
    prim, 
    spec
} valisp_types;

typedef struct {
    valisp_integer_t numerateur;
    valisp_integer_t denominateur;
} valisp_ratio;

typedef struct {
    sexpr car;
    sexpr cdr;
} valisp_cons;

typedef union {
    valisp_integer_t INTEGER;
    valisp_ratio RATIO;
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

sexpr new_integer(valisp_integer_t i) {
    sexpr new_int=valisp_malloc(sizeof(struct valisp_object));

    new_int->type = entier;
    new_int->data.INTEGER = i;

    return new_int;
}

bool integer_p(sexpr val) {
    return (bool) ((val != NULL) && (val->type == entier));
}

valisp_integer_t get_integer(sexpr val) {
    if (!integer_p(val)) {
        ERREUR_FATALE("get_integer: l'argument n'est pas un entier");
    }
    return val->data.INTEGER;
}

/* ==============*/
/* PARTIE RATIOS */
/* ==============*/

static valisp_integer_t gcd(valisp_integer_t a, valisp_integer_t b) {
    valisp_integer_t temp;
    
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}

static int simplify_ratio(valisp_integer_t numerateur, valisp_integer_t denominateur,
                          valisp_integer_t *num_result, valisp_integer_t *denom_result) {
    valisp_integer_t diviseur_commun;
    
    if (denominateur == 0) {
        return -1;
    }
    
    if (numerateur == 0) {
        *num_result = 0;
        *denom_result = 1;
        return 0;
    }
    
    if (denominateur < 0) {
        numerateur = -numerateur;
        denominateur = -denominateur;
    }
    
    /* Calculer le PGCD et simplifier la fraction */
    diviseur_commun = gcd(numerateur, denominateur);
    *num_result = numerateur / diviseur_commun;
    *denom_result = denominateur / diviseur_commun;
    
    if (*denom_result == 1) {
        return 0; 
    }
    
    return 1; 
}

sexpr new_ratio(valisp_integer_t numerateur, valisp_integer_t denominateur) {
    sexpr new_rat;
    valisp_integer_t num_result, denom_result;
    int type;
    
    type = simplify_ratio(numerateur, denominateur, &num_result, &denom_result);
    
    if (type == -1) {
        erreur(DIVISION_PAR_ZERO, "new_ratio", "Dénominateur nul", NULL);
    }
    
    if (type == 0) {
        return new_integer(num_result);
    }
    
    new_rat = valisp_malloc(sizeof(struct valisp_object));
    new_rat->type = ratio;
    new_rat->data.RATIO.numerateur = num_result;
    new_rat->data.RATIO.denominateur = denom_result;
    
    return new_rat;
}

bool ratio_p(sexpr val) {
    return (bool) ((val != NULL) && (val->type == ratio));
}

valisp_integer_t get_numerator(sexpr val) {
    if (!ratio_p(val)) {
        ERREUR_FATALE("get_numerator: l'argument n'est pas un ratio");
    }
    return val->data.RATIO.numerateur;
}

valisp_integer_t get_denominator(sexpr val) {
    if (!ratio_p(val)) {
        ERREUR_FATALE("get_denominator: l'argument n'est pas un ratio");
    }
    return val->data.RATIO.denominateur;
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

bool string_p(sexpr val) {
    return (bool) ((val != NULL) && (val->type == chaine));
}

bool symbol_p(sexpr val) {
    return (bool) ((val != NULL) && (val->type == symbole));
}

char *get_symbol(sexpr val) {
    if (!symbol_p(val)) {
        ERREUR_FATALE("get_symbol: l'argument n'est pas un symbole");
    }
    return val->data.STRING;
}

char *get_string(sexpr val) {
    if (!string_p(val)) {
        ERREUR_FATALE("get_string: l'argument n'est pas une chaine");
    }
    return val->data.STRING;
}

bool symbol_match_p(sexpr val, const char *chaine) {
    if (!symbol_p(val)) {
        ERREUR_FATALE("symbol_match_p: l'argument n'est pas un symbole");
    }
    return (bool) (strcmp(val->data.STRING, chaine) == 0);
}

/* =============*/
/* PARTIE LISTES*/
/* =============*/

sexpr cons(sexpr e1, sexpr e2) {
    sexpr new_cons = valisp_malloc(sizeof(struct valisp_object));

    new_cons->type = couple;
    new_cons->data.CONS.car = e1;
    new_cons->data.CONS.cdr = e2;

    return new_cons;
}

bool cons_p(sexpr e) {
    return (e != NULL && e->type == couple);
}

bool list_p(sexpr e) {
    if (e == NULL) return (bool) 1;
    if (!cons_p(e)) return (bool) 0;
    if (e->data.CONS.cdr == NULL) return (bool) 1;
    if (cons_p(e->data.CONS.cdr)) return (bool) 1;
    
    return (bool) 0;
}

sexpr car(sexpr e) {
    if (!cons_p(e)) {
        ERREUR_FATALE("car: l'argument n'est pas une liste");
    }
    return (e->data.CONS.car);
} 

sexpr cdr(sexpr e) {
    if (!cons_p(e)) {
        ERREUR_FATALE("cdr: l'argument n'est pas une liste");
    }
    return (e->data.CONS.cdr);
}

void set_car(sexpr e, sexpr nouvelle) {
    e->data.CONS.car = nouvelle;
}

void set_cdr(sexpr e, sexpr nouvelle) {
    e->data.CONS.cdr = nouvelle;
}

int longueur_liste(sexpr e) {
    int n;
    for (n = 0; e != NULL; e = cdr(e), n++);
    return n;
}

void afficher_liste(sexpr e) {
    sexpr x = car(e), y = cdr(e);

    afficher(x);

    if (y==NULL) {
        return;
    } else if (cons_p(y) || list_p(y)) {
        printf(" ");
        afficher_liste(y);
    } else {
        printf(" . ");
        afficher(y);
    }
}

/* =================*/
/* PARTIE PRIMITIVES*/
/* =================*/

sexpr new_primitive(sexpr (*p)(sexpr, sexpr)) {
    sexpr new_prim = valisp_malloc(sizeof(struct valisp_object));

    new_prim->type = prim;
    new_prim->data.PRIMITIVE = p;

    return new_prim;
}

sexpr new_speciale(sexpr (*p)(sexpr, sexpr)) {
    sexpr new_spec = valisp_malloc(sizeof(struct valisp_object));

    new_spec->type = spec;
    new_spec->data.PRIMITIVE = p;
    
    return new_spec;
}

bool prim_p(sexpr val) {
    return (bool) (val != NULL && val->type == prim);
}

bool spec_p(sexpr val) {
    return (bool) (val != NULL && val->type == spec);
}

sexpr run_prim(sexpr p, sexpr liste, sexpr env) {
    return p->data.PRIMITIVE(liste, env);
}

void afficher(sexpr val) {
    if (val == NULL) {
        printf("nil");
        return;
    }

    switch (val->type) {
        case entier: {
            /* Utiliser la fonction d'affichage abstraite */
            char* num_str = valisp_to_string(get_integer(val));
            printf("%s", num_str);
            free(num_str); 
            break;
        }
        case ratio: {
            char* ratio_str = valisp_ratio_to_string(
                get_numerator(val), 
                get_denominator(val)
            );
            printf("%s", ratio_str);
            free(ratio_str); 
            break;
        }
        case chaine:
            printf("%s", get_string(val));
            break;
        case symbole: 
            printf("%s", get_symbol(val));
            break;
        case couple:
            printf("(");
            afficher_liste(val);
            printf(")");
            break;
        case prim:
            printf("#<primitive>");
            break;
        case spec:
            printf("#<speciale>");
            break;
        default:
            break;
    }
}