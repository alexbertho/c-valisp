#include <stddef.h>
#include <stdio.h>

#include "types.h"
#include "environnement.h"
#include "erreur.h"
#include "interpreteur.h"


sexpr eval_list(sexpr liste, sexpr env) {
    sexpr res = NULL;

    if (liste == NULL) return NULL;

    for(; liste !=NULL ; liste = cdr(liste) ) {
        res = cons(eval(car(liste), env), res);
    }

    return res;
}

sexpr bind(sexpr variables, sexpr liste, sexpr env) {
    int a = longueur_liste(variables), b = longueur_liste(liste);
    int i;

    if (cons_p(variables)) {
        if (a != b) {
            erreur(ARITE, "bin", "Erreur d'arité", variables);
        }
        i = a;
        while (i > 0) {
            sexpr var = car(variables);
            sexpr val = car(liste);
            
            env = cons(cons(var, val), env);

            variables = cdr(variables);
            liste = cdr(liste);
            i--;
        }
        return env;
    } else if (symbol_p(variables)){
        env = cons(cons(variables, liste), env);
        return env; 
    } else {
        erreur(TYPAGE, "bind", "Erreur de typage", variables);
        return NULL;
    }
}

sexpr apply(sexpr fonction, sexpr liste, sexpr env) {
    sexpr res;

    fonction = eval(fonction, env);

    if (spec_p(fonction)) {
        return run_prim(fonction, liste, env);
    } else if (prim_p(fonction)) {
        sexpr liste_evalue = eval_list(liste, env);
        return run_prim(fonction, liste_evalue, env);
    } else {
        erreur(TYPAGE, "apply", "Erreur de typage", fonction);
        return NULL;
    }

    if (symbol_p(fonction)) {
        trouver_variable(env, fonction, &res);
        fonction = res;
    }

    if (res == NULL) {
        erreur(NOM, "apply", "Erreur de nom", fonction);
        return NULL;
    }
    

}

sexpr eval(sexpr val, sexpr env) {
    if (val == NULL) return NULL;
    
    if (symbol_p(val)) {
        sexpr res;
        /* Gerer si la valeur n'est pas dans l'env */
        trouver_variable(env, val, &res);
        return res;
    }
    else if (list_p(val)) { 
        return apply(car(val), cdr(val), env);
    }
    else {
        return val;
    }

}
