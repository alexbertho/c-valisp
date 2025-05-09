#include <stddef.h>
#include <stdio.h>

#include "types.h"
#include "erreur.h"
#include "primitives.h"
#include "environnement.h"
#include "interpreteur.h"
#include "valisp_numeric.h"
#include "prim_ratio.h"

void test_nb_parametres(sexpr liste, char *fonction, int taille) {
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

void test_calculable(sexpr expression, char *f) {
    if (expression == NULL) {
        erreur(ARITE, f, "nécessite au moins un argument", NULL);
    }

    if (!integer_p(expression) && !ratio_p(expression)) {
        erreur(TYPAGE, f,"necessite un nombre", expression);
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
    sexpr resultat = NULL;
    
    if (liste == NULL) return new_integer(0);
    
    a = car(courant);
    test_calculable(a, "+");
    resultat = a;
    courant = cdr(courant);
    
    while (courant != NULL) {
        a = car(courant);
        
        test_calculable(a, "+");

        if (integer_p(a)) {
            resultat = new_integer(valisp_add(get_integer(resultat), 
                                            get_integer(a)));
        } else {
            resultat = add_ratio(resultat, a);
        }
        
        courant = cdr(courant);
    }
    
    return resultat;
} 

sexpr sub_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr courant = liste;
    sexpr resultat = NULL;
    
    if (liste == NULL) return new_integer(0);
    
    a = car(courant);
    test_calculable(a, "-");
    resultat = a;
    courant = cdr(courant);
    
    if (courant == NULL) {
        if (integer_p(resultat)) {
            return new_integer(-get_integer(resultat));
        } else {
            return new_ratio(-get_numerator(resultat), 
                                    get_denominator(resultat));
        }
    }
    
    while (courant != NULL) {
        a = car(courant);
        test_calculable(a, "-");
        
        if (integer_p(resultat) && integer_p(a)) {
            resultat = new_integer(valisp_sub(get_integer(resultat), 
                                            get_integer(a)));
        } else {
            resultat = sub_ratio(resultat, a);
        }
        
        courant = cdr(courant);
    }
    
    return resultat;
}

sexpr produit_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr courant = liste;
    sexpr resultat = NULL;
    
    if (liste == NULL) return new_integer(1);
    
    a = car(courant);
    test_calculable(a, "*");
    resultat = a;
    courant = cdr(courant);
    
    while (courant != NULL) {
        a = car(courant);
        test_calculable(a, "*");
        
        if (integer_p(resultat) && integer_p(a)) {
            resultat = new_integer(valisp_mul(get_integer(resultat),
                                                get_integer(a)));
        } else {
            resultat = mul_ratio(resultat, a);
        }
        
        courant = cdr(courant);
    }
    
    return resultat;
}

sexpr div_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr courant = liste;
    sexpr resultat = NULL;
    
    if (liste == NULL) {
        erreur(ARITE, "/", "nécessite au moins un argument", NULL);
    }
    
    a = car(courant);
    test_calculable(a, "/");
    resultat = a;
    courant = cdr(courant);
    
    if (courant == NULL) {
        if (integer_p(resultat)) {
            if (get_integer(resultat) == 0) {
                erreur(DIVISION_PAR_ZERO, "/", "Division par zéro", NULL);
            }
            return new_ratio(1, get_integer(resultat));
        } else {
            if (get_numerator(resultat) == 0) {
                erreur(DIVISION_PAR_ZERO, "/", "Division par zéro", NULL);
            }
            return new_ratio(get_denominator(resultat), get_numerator(resultat));
        }
    }
    
    while (courant != NULL) {
        a = car(courant);
        test_calculable(a, "/");
        
        if ((integer_p(a) && get_integer(a) == 0) || 
            (ratio_p(a) && get_numerator(a) == 0)) {
            erreur(DIVISION_PAR_ZERO, "/", "Division par zéro", NULL);
        }
        
        if (integer_p(resultat) && integer_p(a)) {
            valisp_integer_t num = get_integer(resultat);
            valisp_integer_t den = get_integer(a);
            
            if (num % den == 0) {
                resultat = new_integer(valisp_div(num, den));
            } else {
                resultat = new_ratio(num, den);
            }
        } else {
            resultat = div_ratio(resultat, a);
        }
        
        courant = cdr(courant);
    }
    
    return resultat;
}

sexpr mod_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    valisp_integer_t diviseur;
    
    test_nb_parametres(liste, "mod", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    if (!integer_p(a)) erreur(TYPAGE, "mod", "nécessite un entier", a);
    if (!integer_p(b)) erreur(TYPAGE, "mod", "nécessite un entier", b);
    
    diviseur = get_integer(b);
    if (diviseur == 0) {
        erreur(DIVISION_PAR_ZERO, "mod", "Modulo par zéro", NULL);
    }

    return new_integer(valisp_mod(get_integer(a), diviseur));
}

sexpr less_than_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    
    test_nb_parametres(liste, "<", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    test_calculable(a, "<");
    test_calculable(b, "<");
    
    if (integer_p(a) && integer_p(b)) {
        if (valisp_lt(get_integer(a), get_integer(b))) {
            return new_symbol("t");
        } else {
            return NULL;
        }
    }
    
    if (less_than_ratio(a, b)) {
        return new_symbol("t");
    } else {
        return NULL;
    }
}

sexpr sup_than_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    
    test_nb_parametres(liste, ">", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    test_calculable(a, ">");
    test_calculable(b, ">");
    
    if (integer_p(a) && integer_p(b)) {
        if (valisp_gt(get_integer(a), get_integer(b))) {
            return new_symbol("t");
        } else {
            return NULL;
        }
    }
    
    if (less_than_ratio(b, a)) {
        return new_symbol("t");
    } else {
        return NULL;
    }
}

sexpr equal_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    
    test_nb_parametres(liste, "=", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    test_calculable(a, "=");
    test_calculable(b, "=");
    
    if (integer_p(a) && integer_p(b)) {
        if (valisp_eq(get_integer(a), get_integer(b))) {
            return new_symbol("t");
        } else {
            return NULL;
        }
    }
    
    if (equal_ratio(a, b)) {
        return new_symbol("t");
    } else {
        return NULL;
    }
}

sexpr print_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr courant = liste;
        
    a = car(liste);
    
    if (a == NULL) erreur(TYPAGE, "print", "nécessite une valeur", a);

    while (courant != NULL) {
        a = car(courant);

        if (a == NULL) erreur(TYPAGE, "print", "nécessite une valeur", a);
        
        afficher(a);
        courant = cdr(courant);
    }
    
    return a;
}

sexpr println_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr courant = liste;
        
    a = car(liste);
    
    if (a == NULL) erreur(TYPAGE, "println", "nécessite une valeur", a);
    
    while (courant != NULL) {
        a = car(courant);

        if (a == NULL) erreur(TYPAGE, "println", "nécessite une valeur", a);
        
        afficher(a);
        courant = cdr(courant);
    }

    printf("\n");
    
    return a;
}

sexpr type_of_valisp(sexpr liste, sexpr env) {
    sexpr a;
    
    test_nb_parametres(liste, "type-of", 1);
    
    a = car(liste);
    
    if (a == NULL) return new_symbol("nil");
    
    if (integer_p(a)) {
        return new_symbol("entier");
    } else if (ratio_p(a)) {
        return new_symbol("ratio");
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