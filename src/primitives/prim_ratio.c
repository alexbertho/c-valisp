#include <stddef.h>

#include "types.h"
#include "erreur.h"
#include "primitives.h"
#include "environnement.h"
#include "interpreteur.h"
#include "valisp_numeric.h"

sexpr add_ratio(sexpr a, sexpr b) {
    valisp_integer_t num_a, denom_a, num_b, denom_b, num_result, denom_result;
    
    if (integer_p(a)) {
        num_a = get_integer(a);
        denom_a = 1;
    } else { 
        num_a = get_numerator(a);
        denom_a = get_denominator(a);
    }
    
    if (integer_p(b)) {
        num_b = get_integer(b);
        denom_b = 1;
    } else { 
        num_b = get_numerator(b);
        denom_b = get_denominator(b);
    }
    
    if (denom_a == denom_b) {
        num_result = num_a + num_b;
        denom_result = denom_a;
    } else {
        num_result = num_a * denom_b + num_b * denom_a;
        denom_result = denom_a * denom_b;
    }
    
    return new_ratio(num_result, denom_result);
}

sexpr sub_ratio(sexpr a, sexpr b) {
    valisp_integer_t num_a, denom_a, num_b, denom_b, num_result, denom_result;
    
    if (integer_p(a)) {
        num_a = get_integer(a);
        denom_a = 1;
    } else {
        num_a = get_numerator(a);
        denom_a = get_denominator(a);
    }
    
    if (integer_p(b)) {
        num_b = get_integer(b);
        denom_b = 1;
    } else {
        num_b = get_numerator(b);
        denom_b = get_denominator(b);
    }
    
    if (denom_a == denom_b) {
        num_result = num_a - num_b;
        denom_result = denom_a;
    } else {
        num_result = num_a * denom_b - num_b * denom_a;
        denom_result = denom_a * denom_b;
    }
    
    return new_ratio(num_result, denom_result);
}

sexpr mul_ratio(sexpr a, sexpr b) {
    valisp_integer_t num_a, denom_a, num_b, denom_b, num_result, denom_result;
    
    if (integer_p(a)) {
        num_a = get_integer(a);
        denom_a = 1;
    } else {
        num_a = get_numerator(a);
        denom_a = get_denominator(a);
    }
    
    if (integer_p(b)) {
        num_b = get_integer(b);
        denom_b = 1;
    } else {
        num_b = get_numerator(b);
        denom_b = get_denominator(b);
    }
    
    num_result = num_a * num_b;
    denom_result = denom_a * denom_b;
    
    return new_ratio(num_result, denom_result);
}

sexpr div_ratio(sexpr a, sexpr b) {
    valisp_integer_t num_a, denom_a, num_b, denom_b, num_result, denom_result;
    
    if (integer_p(a)) {
        num_a = get_integer(a);
        denom_a = 1;
    } else {
        num_a = get_numerator(a);
        denom_a = get_denominator(a);
    }
    
    if (integer_p(b)) {
        num_b = get_integer(b);
        denom_b = 1;
    } else {
        num_b = get_numerator(b);
        denom_b = get_denominator(b);
    }
    
    if (num_b == 0) {
        erreur(DIVISION_PAR_ZERO, "div_ratio", "Division par zéro", NULL);
    }
    
    num_result = num_a * denom_b;
    denom_result = denom_a * num_b;
    
    return new_ratio(num_result, denom_result);
}

int equal_ratio(sexpr a, sexpr b) {
    valisp_integer_t num_a, denom_a, num_b, denom_b;
    
    if (integer_p(a)) {
        num_a = get_integer(a);
        denom_a = 1;
    } else {
        num_a = get_numerator(a);
        denom_a = get_denominator(a);
    }
    
    if (integer_p(b)) {
        num_b = get_integer(b);
        denom_b = 1;
    } else {
        num_b = get_numerator(b);
        denom_b = get_denominator(b);
    }
    
    return (num_a * denom_b == denom_a * num_b);
}

int less_than_ratio(sexpr a, sexpr b) {
    valisp_integer_t num_a, denom_a, num_b, denom_b;
    
    if (integer_p(a)) {
        num_a = get_integer(a);
        denom_a = 1;
    } else {
        num_a = get_numerator(a);
        denom_a = get_denominator(a);
    }
    
    if (integer_p(b)) {
        num_b = get_integer(b);
        denom_b = 1;
    } else {
        num_b = get_numerator(b);
        denom_b = get_denominator(b);
    }
    
    if ((denom_a > 0 && denom_b > 0) || (denom_a < 0 && denom_b < 0)) {
        return (num_a * denom_b < denom_a * num_b);
    } else {
        return (num_a * denom_b > denom_a * num_b);
    }
}

sexpr ratio_valisp(sexpr liste, sexpr env) {
    sexpr a, b;
    valisp_integer_t num, denom;
    
    test_nb_parametres(liste, "ratio", 2);
    
    a = car(liste);
    b = car(cdr(liste));
    
    if (!integer_p(a)) {
        erreur(TYPAGE, "ratio", "Le numérateur doit être un entier", a);
    }
    
    if (!integer_p(b)) {
        erreur(TYPAGE, "ratio", "Le dénominateur doit être un entier", b);
    }
    
    num = get_integer(a);
    denom = get_integer(b);
    
    return new_ratio(num, denom);
}

sexpr numerator_valisp(sexpr liste, sexpr env) {
    sexpr a;
    
    test_nb_parametres(liste, "numerator", 1);
    
    a = car(liste);
    
    if (integer_p(a)) {
        return a; /* Pour un entier, le numérateur est l'entier lui-même */
    }
    
    if (!ratio_p(a)) {
        erreur(TYPAGE, "numerator", "L'argument doit être un ratio ou un entier", a);
    }
    
    return new_integer(get_numerator(a));
}

sexpr denominator_valisp(sexpr liste, sexpr env) {
    sexpr a;
    
    test_nb_parametres(liste, "denominator", 1);
    
    a = car(liste);
    
    if (integer_p(a)) {
        return new_integer(1); /* Pour un entier, le dénominateur est 1 */
    }
    
    if (!ratio_p(a)) {
        erreur(TYPAGE, "denominator", "L'argument doit être un ratio ou un entier", a);
    }
    
    return new_integer(get_denominator(a));
}
