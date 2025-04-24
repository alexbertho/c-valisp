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
    bool res;
    
    test_nb_parametres(liste, "<", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    if (!integer_p(a)) erreur(TYPAGE, "<", "nécessite un entier", a);
    if (!integer_p(b)) erreur(TYPAGE, "<", "nécessite un entier", b);

    res = (bool) get_integer(a) < get_integer(b);
    if (res) {
        return new_symbol("t");
    } else {
        return NULL;
    }
}

sexpr sup_than_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    bool res;
    
    test_nb_parametres(liste, ">", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    if (!integer_p(a)) erreur(TYPAGE, ">", "nécessite un entier", a);
    if (!integer_p(b)) erreur(TYPAGE, ">", "nécessite un entier", b);

    res = (bool) get_integer(a) > get_integer(b);
    if (res) {
        return new_symbol("t");
    } else {
        return NULL;
    }
}

sexpr equal_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    bool res;
    
    test_nb_parametres(liste, "=", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    if (!integer_p(a)) erreur(TYPAGE, "=", "nécessite un entier", a);
    if (!integer_p(b)) erreur(TYPAGE, "=", "nécessite un entier", b);

    res = (bool) get_integer(a) == get_integer(b);
    if (res) {
        return new_symbol("t");
    } else {
        return NULL;
    }
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

sexpr eval_valisp(sexpr liste, sexpr env) {
    sexpr a;
    test_nb_parametres(liste, "eval", 1);
    
    a = car(liste);
    
    if (a == NULL) return NULL;
    if (!cons_p(a)) erreur(TYPAGE, "eval", "nécessite une liste", a);
    
    return eval(a, env);
}

sexpr apply_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    
    test_nb_parametres(liste, "apply", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    if (a == NULL) return NULL;
    if (!cons_p(a)) erreur(TYPAGE, "apply", "nécessite une liste", a);
    
    return apply(a, b, env);
}

/* Formes speciales */
sexpr quote_valisp(sexpr liste, sexpr env) {
    test_nb_parametres(liste, "quote", 1);
    
    return car(liste);
}

sexpr lambda_valisp(sexpr liste, sexpr env) {      
    return cons(new_symbol("lambda"), liste);
}

sexpr macro_valisp(sexpr liste, sexpr env) {
    return cons(new_symbol("macro"), liste);
}

sexpr if_valisp(sexpr liste, sexpr env) {
    sexpr condition, alors, sinon;
    
    test_nb_parametres(liste, "if", 3);
    
    condition = car(liste);
    alors = car(cdr(liste));
    
    condition = eval(condition, env);
    
    if (condition != NULL) {
        return eval(alors, env);
    } else {
        if (cdr(cdr(liste)) != NULL) {
            sinon = car(cdr(cdr(liste)));
            return eval(sinon, env);
        } else {
            return NULL;
        }
    }
}