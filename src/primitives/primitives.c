#include "types.h"
#include "erreur.h"
#include "primitives.h"
#include <stddef.h>
#include <stdio.h>


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
/* (car nil) => nil) */
sexpr car_valisp(sexpr liste, sexpr env) {
    sexpr a;
    test_nb_parametres(liste, "car", 1);
    a = car(liste);
    if (!cons_p(a)) erreur(TYPAGE, "car", "nécessite une liste", a);
    return car(a);
    
}

sexpr cdr_valisp(sexpr liste, sexpr env) {
    sexpr a;
    test_nb_parametres(liste, "cdr", 1);
    a = car(liste);
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
    sexpr b;

    test_nb_parametres(liste, "+", 2);

    a = car(liste);
    b = car(cdr(liste));

    if (!integer_p(a)) erreur(TYPAGE, "+", "nécessite un entier", a);
    if (!integer_p(b)) erreur(TYPAGE, "+", "nécessite un entier", b);
    
    return new_integer(get_integer(a) + get_integer(b));
}

/*
(- 10 8) => 2
(- 10)   => -10

*/
sexpr sub_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    
    test_nb_parametres(liste, "-", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    if (!integer_p(a)) erreur(TYPAGE, "-", "nécessite un entier", a);
    if (!integer_p(b)) erreur(TYPAGE, "-", "nécessite un entier", b);
    
    return new_integer(get_integer(a) - get_integer(b));
}

sexpr produit_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    
    test_nb_parametres(liste, "*", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    if (!integer_p(a)) erreur(TYPAGE, "*", "nécessite un entier", a);
    if (!integer_p(b)) erreur(TYPAGE, "*", "nécessite un entier", b);
    
    return new_integer(get_integer(a) * get_integer(b));
}


/* (/ 5 0) */
sexpr div_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    
    test_nb_parametres(liste, "/", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    if (!integer_p(a)) erreur(TYPAGE, "/", "nécessite un entier", a);
    if (!integer_p(b)) erreur(TYPAGE, "/", "nécessite un entier", b);
    
    return new_integer(get_integer(a) / get_integer(b));
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

/*

(type-of nil) => symbol

*/
sexpr type_of_valisp(sexpr liste, sexpr env) {
    sexpr a;
    
    test_nb_parametres(liste, "type-of", 1);
    
    a = car(liste);
    
    if (a == NULL) erreur(TYPAGE, "type-of", "nécessite une valeur", a);
    
    if (integer_p(a)) {
        return new_symbol("entier");
    } else if (string_p(a)) {
        return new_symbol("chaine");
    } else if (symbol_p(a)) {
        return new_symbol("symbole");
    } else if (cons_p(a)) {
        return new_symbol("liste");
    } else {
        return new_symbol("inconnu");
    }
}
