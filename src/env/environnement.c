#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "types.h"
#include "allocateur.h"
#include "couleurs.h"

sexpr ENV = NULL;


sexpr environnement_global() {
    return ENV;
}

void initialiser_memoire() {
    sexpr t;

    initialiser_memoire_dynamique();
    t = new_symbol("t");
    ENV = cons(cons(t,t), NULL);
}

sexpr parcourir_fin_env(sexpr env) {
    if (env == NULL) return NULL;
    if (cdr(env) == NULL) return env;  
    return parcourir_fin_env(cdr(env));
}

void ajouter_a_la_fin(sexpr env, sexpr variable, sexpr valeur) {
    sexpr dernier = parcourir_fin_env(env);
    if (dernier == NULL) {
        ENV = cons(cons(variable, valeur), NULL);
    } else {
        set_cdr(dernier, cons(cons(variable, valeur), NULL));
    }
}

int longeur_env(sexpr env) {
    int n;
    for (n = 0; env != NULL; env = cdr(env), n++);
    return n;
}

void valisp_stat_memoire() {
    afficher_stat_memoire();
    printf(" → %d variables\n", longeur_env(environnement_global()));
}

void afficher_env(sexpr env) {
    sexpr a;
    for (; env != NULL; env = cdr(env)) {
        a = car(env);  /* a est de la forme (nom . valeur) */
        
        printf("%s", couleur_bleu);
        afficher(car(a));    
        printf(" ");
        printf("%s", couleur_blanc);
        afficher(cdr(a));    
        printf("\n");
    }
}

int trouver_variable(sexpr env, sexpr variable, sexpr *resultat) {
    sexpr liste, a, val, nom;
    for (liste=env; liste!=NULL ; liste=cdr(liste)) {
        a = car(liste); /* a est de la forme (nom . valeur) */
        nom = car(a);
        val = cdr(a);

        if(symbol_match_p(nom, get_symbol(variable))) {
            *resultat = val;
            return 0;
        }
    }
    return -1;
}

int modifier_variable(sexpr env, sexpr variable, sexpr valeur) {
    sexpr liste, a, nom;
    for (liste=env; liste!=NULL ; liste=cdr(liste)) {
        a = car(liste); /* a est de la forme (nom . valeur) */
        nom = car(a);

        if(symbol_match_p(nom, get_symbol(variable))) {
            set_cdr(a, valeur);
            return 0;
        }
    }
    return -1;
}

void definir_variable_globale(sexpr variable, sexpr valeur) {
    sexpr env = environnement_global();
    sexpr _res;

    if(trouver_variable(env, variable, &_res) == 0) {
        modifier_variable(env, variable, valeur);
        return;
    }
    ajouter_a_la_fin(env, variable, valeur);
}

void charger_une_primitive(char* nom, sexpr (*prim)(sexpr, sexpr)) {
    sexpr variable = new_symbol(nom);
    sexpr primitive = new_primitive(prim);
    definir_variable_globale(variable, primitive);
}

void charger_une_speciale(char* nom, sexpr (*prim)(sexpr, sexpr)) {
    sexpr variable = new_symbol(nom);
    sexpr speciale = new_speciale(prim);
    definir_variable_globale(variable, speciale);
}
