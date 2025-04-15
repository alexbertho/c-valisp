#include <stddef.h>
#include <stdio.h>

#include "types.h"
#include "erreur.h"
#include "primitives.h"
#include "environnement.h"
#include "interpreteur.h"

void test_nb_parametres(sexpr liste, char* fonction, int taille) {
    int compteur = 0;
    sexpr tmp = liste;
    
    while (tmp != NULL) {
        compteur++;
        tmp = cdr(tmp);
    }
    
    if (compteur != taille) {
        erreur(ARITE, "test_nb_parametres", "Erreur d'Arité", liste);
    }
}

sexpr car_valisp(sexpr liste, sexpr env) {
    sexpr a;
    test_nb_parametres(liste, "car", 1);
    a = car(liste);
    if (a == NULL) return NULL;
    if (!cons_p(a)) erreur(TYPAGE, "car", "nécessite une liste", a);
    return car(a);
}

sexpr cdr_valisp(sexpr liste, sexpr env) {
    sexpr a;
    test_nb_parametres(liste, "cdr", 1);
    a = car(liste);
    if (a == NULL) return NULL;
    if (!cons_p(a)) erreur(TYPAGE, "cdr", "nécessite une liste", a);
    return cdr(a);
}

sexpr cons_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    
    test_nb_parametres(liste, "cons", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    return cons(a, b);
}

sexpr add_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr courant = liste;
    int somme=0;

    if (liste == NULL) return new_integer(0);

    while (courant != NULL){
        a = car(courant);
        if (!integer_p(a)) erreur(TYPAGE, "+", "nécessite un entier", a);

        somme += get_integer(a);
        courant = cdr(courant);
        
    }
    return new_integer(somme);
} 

/*
(- 10 8) => 2
(- 10)   => -10

*/
sexpr sub_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr courant = liste;
    int diff;

    if (liste == NULL) return new_integer(0);


    /*A ameliorer !*/
    a = car(courant);
    if (!integer_p(a)) erreur(TYPAGE, "-", "nécessite un entier", a);
    diff = get_integer(a);
    courant = cdr(courant);
    if (courant == NULL) return new_integer(-diff);

    while (courant != NULL){
        a = car(courant);
        if (!integer_p(a)) erreur(TYPAGE, "-", "nécessite un entier", a);

        diff -= get_integer(a);
        courant = cdr(courant);
        
    }
    return new_integer(diff);
}

sexpr produit_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr courant = liste;
    int produit=1;

    if (liste == NULL) return new_integer(1);

    while (courant != NULL){
        a = car(courant);
        if (!integer_p(a)) erreur(TYPAGE, "*", "nécessite un entier", a);

        produit *= get_integer(a);
        courant = cdr(courant);
        
    }
    return new_integer(produit);
}

/*A ameliore et div_valisp 4 renvoie 0 au lieux de 1/4 ne gere pas les floatants*/
sexpr div_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr courant = liste;
    int quotient;

    /*A ameliorer !*/
    a = car(courant);
    if (!integer_p(a)) erreur(TYPAGE, "-", "nécessite un entier", a);
    quotient = get_integer(a);
    courant = cdr(courant);
    if (courant == NULL) return new_integer(1/quotient);

    while (courant != NULL){
        a = car(courant);
        if (!integer_p(a)) erreur(TYPAGE, "/", "nécessite un entier", a);

        quotient /= get_integer(a);
        courant = cdr(courant);
        
    }
    return new_integer(quotient);
}

sexpr mod_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    
    test_nb_parametres(liste, "mod", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    if (!integer_p(a)) erreur(TYPAGE, "mod", "nécessite un entier", a);
    if (!integer_p(b)) erreur(TYPAGE, "mod", "nécessite un entier", b);
    
    return new_integer(get_integer(a) % get_integer(b));
}

/*

False => nil (NULL)
new_symbol("t") 

(defun > (a b)
    (if (< a b) b a))
*/
sexpr less_than_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    
    test_nb_parametres(liste, "<", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    if (!integer_p(a)) erreur(TYPAGE, "<", "nécessite un entier", a);
    if (!integer_p(b)) erreur(TYPAGE, "<", "nécessite un entier", b);
    
    return new_integer(get_integer(a) < get_integer(b));
}

sexpr equal_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    
    test_nb_parametres(liste, "=", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    if (!integer_p(a)) erreur(TYPAGE, "=", "nécessite un entier", a);
    if (!integer_p(b)) erreur(TYPAGE, "=", "nécessite un entier", b);
    
    return new_integer(get_integer(a) == get_integer(b));
}

/**
 * (print "x+y=" 12 "+" (+ 2 3) ) ")
 *  faut que la fonction print interprète les arguments, par exemple: (+ 2 3) se transforme en "5"
 * 
 */
sexpr print_valisp(sexpr liste, sexpr env) {
    sexpr a;
    
    test_nb_parametres(liste, "print", 1);
    
    a = car(liste);
    
    if (a == NULL) erreur(TYPAGE, "print", "nécessite une valeur", a);
    
    afficher(a);
    
    return NULL;
}

sexpr println_valisp(sexpr liste, sexpr env) {
    sexpr a;
    
    test_nb_parametres(liste, "println", 1);
    
    a = car(liste);
    
    if (a == NULL) erreur(TYPAGE, "println", "nécessite une valeur", a);
    
    afficher(a);
    printf("\n");
    
    return NULL;
}


sexpr type_of_valisp(sexpr liste, sexpr env) {
    sexpr a;
    
    test_nb_parametres(liste, "type-of", 1);
    
    a = car(liste);
    
    if (a == NULL) return new_symbol("nil");
    
    if (integer_p(a)) {
        return new_symbol("entier");
    } else if (string_p(a)) {
        return new_symbol("chaine");
    } else if (symbol_p(a)) {
        return new_symbol("symbole");
    } else if (cons_p(a)) {
        return new_symbol("liste");
    } else { /*Symbole inconnu*/
        return new_symbol("nil");
    }
}

sexpr defvar_valisp(sexpr liste, sexpr env) {
    sexpr nom;
    sexpr exp;
    sexpr res;

    test_nb_parametres(liste,"defvar",2);
    nom = car(liste);
    exp = car(cdr(liste));

    if (!symbol_p(nom)) {
        erreur(TYPAGE,"defvar",
            "Le 1er paramètre doit être un symbole",
            nom);
    }

    res = (sexpr) eval(exp, env); 
    definir_variable_globale(nom, res); 
    return res;
}

sexpr setq_valisp(sexpr liste, sexpr env) {
    sexpr nom;
    sexpr exp;
    sexpr res;

    test_nb_parametres(liste,"setq",2);
    nom = car(liste);
    exp = car(cdr(liste));

    if (!symbol_p(nom)) {
        erreur(TYPAGE,"defvar",
            "Le 1er paramètre doit être un symbole",
            nom);
    }
    
    res = (sexpr) eval(exp, env); 
    modifier_variable(env, nom, res);
    return res;
}
