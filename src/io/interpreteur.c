#include <stddef.h>
#include <stdio.h>

#include "types.h"
#include "environnement.h"
#include "erreur.h"
#include "interpreteur.h"


sexpr eval_list(sexpr liste, sexpr env) {
    if (liste == NULL) return NULL;
    return cons (eval (car(liste),env) , eval_list(cdr(liste), env));
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
    sexpr result;
    sexpr nouvel_env;
    sexpr expansion;
    
    eval_fonction = eval(fonction, env);
    
    if (spec_p(eval_fonction)) {
        return run_prim(eval_fonction, liste, env);
    } 
    else if (prim_p(eval_fonction)) {
        args_evalues = eval_list(liste, env);
        return run_prim(eval_fonction, args_evalues, env);
    }
    else if (cons_p(eval_fonction)) {
        lambda_symbol = car(eval_fonction);
        
        if (symbol_p(lambda_symbol)) {
            if (symbol_match_p(lambda_symbol, "lambda")) {
                params = car(cdr(eval_fonction));
                body = cdr(cdr(eval_fonction));
                
                args_evalues = eval_list(liste, env);
                
                nouvel_env = bind(params, args_evalues, env);
                
                result = NULL;

                /* 
                 * Parcourir séquentiellement toutes les expressions du corps
                 * Exemple: pour (lambda (x y) (print x) (print y) (+ x y))
                 * body = ((print x) (print y) (+ x y))
                 * La boucle traite une à une ces expressions
                 */
                while (body != NULL) {
                    result = eval(car(body), nouvel_env);
                    body = cdr(body);
                }
                
                return result;
            }
            else if (symbol_match_p(lambda_symbol, "macro")) {
                params = car(cdr(eval_fonction));
                body = cdr(cdr(eval_fonction));
                
                nouvel_env = bind(params, liste, env);
                
                expansion = NULL;
                while (body != NULL) {
                    expansion = eval(car(body), nouvel_env);
                    body = cdr(body);
                }
                /* 
                 * Étape supplémentaire pour les macros:
                 * Évaluer l'expansion dans l'environnement original
                 * 
                 * Exemple: si expansion = (if (> x 0) (progn (print "x est positif") (* x 2)) nil)
                 * on évalue cette forme pour obtenir le résultat final
                 */
                return eval(expansion, env);
            }
        }
    }
        
    erreur(TYPAGE, "apply", "Ne peut pas appliquer cette expression comme une fonction", eval_fonction);
    return NULL;
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
