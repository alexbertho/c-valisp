#include <stddef.h>
#include <stdio.h>

#include "types.h"
#include "environnement.h"
#include "erreur.h"
#include "interpreteur.h"
#include "lifo.h"

sexpr eval_list(sexpr liste, sexpr env) {
    if (liste == NULL) return NULL;
    return cons(eval (car(liste),env), eval_list(cdr(liste), env));
}

sexpr bind(sexpr variables, sexpr liste, sexpr env) {
    int a, b, i;
    sexpr nouvel_env = env;
    sexpr var, val;
    
    if (cons_p(variables)) {
        a = longueur_liste(variables);
        b = longueur_liste(liste);
        
        if (a != b) {
            erreur(ARITE, "bind", "Nombre d'arguments incorrect", variables);
        }

        for (i = a; i > 0; i--) {
            var = car(variables);
            val = car(liste);
            
            nouvel_env = cons(cons(var, val), nouvel_env);
            
            variables = cdr(variables);
            liste = cdr(liste);
        }
        return nouvel_env;
    } else if (symbol_p(variables)) {
        env = cons(cons(variables, liste), env);
        return env; 
    } else {
        erreur(TYPAGE, "bind", "Les paramètres doivent être une liste ou un symbole", variables);
        return NULL;
    }
}

sexpr apply(sexpr fonction, sexpr liste, sexpr env) {
    sexpr eval_fonction;
    sexpr lambda_symbol;
    sexpr params;
    sexpr body;
    sexpr args_evalues;
    sexpr result = NULL;
    sexpr nouvel_env;
    sexpr expansion;
    int cadre_pile;
    
    /* Sauvegarder l'indice du haut de la pile */
    cadre_pile = pile_nouveau_cadre();
    
    eval_fonction = eval(fonction, env);
    pile_ajout(eval_fonction); /* Empiler pour protéger contre le GC */
    
    if (spec_p(eval_fonction)) {
        result = run_prim(eval_fonction, liste, env);
        goto fin;
    } 
    else if (prim_p(eval_fonction)) {
        args_evalues = eval_list(liste, env);
        pile_ajout(args_evalues); /* Protéger les arguments évalués */
        result = run_prim(eval_fonction, args_evalues, env);
        goto fin;
    }
    else if (cons_p(eval_fonction)) {
        lambda_symbol = car(eval_fonction);
        
        if (symbol_p(lambda_symbol)) {
            if (symbol_match_p(lambda_symbol, "lambda")) {
                params = car(cdr(eval_fonction));
                body = cdr(cdr(eval_fonction));
                
                args_evalues = eval_list(liste, env);
                pile_ajout(args_evalues);
                
                nouvel_env = bind(params, args_evalues, env);
                pile_ajout(nouvel_env);
                
                /* Parcourir séquentiellement le corps de la fonction */
                while (body != NULL) {
                    if (result != NULL) {
                        /* On ne conserve pas les résultats intermédiaires */
                        result = eval(car(body), nouvel_env);
                    } else {
                        result = eval(car(body), nouvel_env);
                    }
                    pile_ajout(result);
                    body = cdr(body);
                }
                
                goto fin;
            }
            else if (symbol_match_p(lambda_symbol, "macro")) {
                params = car(cdr(eval_fonction));
                body = cdr(cdr(eval_fonction));
                
                nouvel_env = bind(params, liste, env);
                pile_ajout(nouvel_env);
                
                expansion = NULL;
                while (body != NULL) {
                    expansion = eval(car(body), nouvel_env);
                    pile_ajout(expansion);
                    body = cdr(body);
                }
                
                /* Évaluer l'expansion dans l'environnement original */
                result = eval(expansion, env);
                goto fin;
            }
        }
    }
    
    erreur(TYPAGE, "apply", "Ne peut pas appliquer cette expression comme une fonction", eval_fonction);
    
fin:
    /* Restaurer la pile à son état initial */
    pile_fin_cadre(cadre_pile);
    return result;
}


sexpr eval(sexpr val, sexpr env) {
    sexpr res;
    
    if (val == NULL) return NULL;
    
    if (symbol_p(val)) {
        if (trouver_variable(env, val, &res) != 0) {
            erreur(NOM, "eval", "Variable non définie", val);
        }
        return res;
    }
    else if (list_p(val)) {
        return apply(car(val), cdr(val), env);
    }
    else {
        return val;
    }
}
