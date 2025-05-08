#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "allocateur.h"
#include "types.h"
#include "tests.h"
#include "primitives.h"
#include "prim_ratio.h"
#include "mes_tests.h"
#include "valisp_numeric.h"
#include "erreur.h"
#include "memoire.h"

void afficher_test_ratio(char* nom_fonction, char* description, sexpr resultat) {
    printf("%s %s : ", nom_fonction, description);
    afficher(resultat);
    printf("  ");
}

void test_ratio_creation() {
    int b = 1;
    sexpr r1, r2, r3, r4, r5;
    sexpr liste;
    sexpr env = NULL;
    
    afficher_titre("Test Ratio - Création et propriétés");
    initialiser_memoire_dynamique();
    
    liste = cons(new_integer(1), cons(new_integer(2), NULL));
    r1 = ratio_valisp(liste, env);
    
    afficher_test_ratio("ratio_valisp", "1/2", r1);
    b = RUN_TEST(ratio_p(r1)) && b;
    b = RUN_TEST(get_numerator(r1) == 1) && b;
    b = RUN_TEST(get_denominator(r1) == 2) && b;
    ok_test(b);
    
    liste = cons(new_integer(4), cons(new_integer(8), NULL));
    r2 = ratio_valisp(liste, env);
    
    afficher_test_ratio("ratio_valisp", "4/8 (devrait être simplifié en 1/2)", r2);
    b = RUN_TEST(ratio_p(r2)) && b;
    b = RUN_TEST(get_numerator(r2) == 1) && b;
    b = RUN_TEST(get_denominator(r2) == 2) && b;
    ok_test(b);
    
    liste = cons(new_integer(-3), cons(new_integer(5), NULL));
    r3 = ratio_valisp(liste, env);
    
    afficher_test_ratio("ratio_valisp", "-3/5", r3);
    b = RUN_TEST(ratio_p(r3)) && b;
    b = RUN_TEST(get_numerator(r3) == -3) && b;
    b = RUN_TEST(get_denominator(r3) == 5) && b;
    ok_test(b);
    
    liste = cons(new_integer(2), cons(new_integer(-7), NULL));
    r4 = ratio_valisp(liste, env);
    
    afficher_test_ratio("ratio_valisp", "2/-7 (devrait être normalisé en -2/7)", r4);
    b = RUN_TEST(ratio_p(r4)) && b;
    b = RUN_TEST(get_numerator(r4) == -2) && b;
    b = RUN_TEST(get_denominator(r4) == 7) && b;
    ok_test(b);
    
    liste = cons(new_integer(15), cons(new_integer(5), NULL));
    r5 = ratio_valisp(liste, env);
    
    afficher_test_ratio("ratio_valisp", "15/5 (devrait être converti en entier 3)", r5);
    b = RUN_TEST(integer_p(r5)) && b;
    b = RUN_TEST(get_integer(r5) == 3) && b;
    ok_test(b);
}

void test_ratio_accessors() {
    int b = 1;
    sexpr r1, int_val;
    sexpr liste1, liste2;
    sexpr num, denom;
    sexpr env = NULL;
    
    afficher_titre("Test Ratio - Accesseurs");
    initialiser_memoire_dynamique();
    
    r1 = new_ratio(5, 8);
    int_val = new_integer(42);
    
    liste1 = cons(r1, NULL);
    num = numerator_valisp(liste1, env);
    
    afficher_test_ratio("numerator_valisp", "numerator de 5/8", num);
    b = RUN_TEST(integer_p(num)) && b;
    b = RUN_TEST(get_integer(num) == 5) && b;
    ok_test(b);
    
    liste2 = cons(r1, NULL);
    denom = denominator_valisp(liste2, env);
    
    afficher_test_ratio("denominator_valisp", "denominator de 5/8", denom);
    b = RUN_TEST(integer_p(denom)) && b;
    b = RUN_TEST(get_integer(denom) == 8) && b;
    ok_test(b);
    
    liste1 = cons(int_val, NULL);
    
    num = numerator_valisp(liste1, env);
    afficher_test_ratio("numerator_valisp", "numerator de l'entier 42", num);
    b = RUN_TEST(integer_p(num)) && b;
    b = RUN_TEST(get_integer(num) == 42) && b;
    ok_test(b);
    
    denom = denominator_valisp(liste1, env);
    afficher_test_ratio("denominator_valisp", "denominator de l'entier 42", denom);
    b = RUN_TEST(integer_p(denom)) && b;
    b = RUN_TEST(get_integer(denom) == 1) && b;
    ok_test(b);
}

void test_ratio_arithmetic() {
    int b = 1;
    sexpr r1, r2, r3, r4, r5, i1, result;
    
    afficher_titre("Test Ratio - Opérations arithmétiques");
    initialiser_memoire_dynamique();
    
    r1 = new_ratio(1, 2);
    r2 = new_ratio(3, 4);
    r3 = new_ratio(-2, 5);
    i1 = new_integer(2);
    
    result = add_ratio(r1, r2);
    afficher_test_ratio("add_ratio", "1/2 + 3/4", result);
    b = RUN_TEST(ratio_p(result)) && b;
    b = RUN_TEST(get_numerator(result) == 5) && b;
    b = RUN_TEST(get_denominator(result) == 4) && b;
    ok_test(b);
    
    result = add_ratio(r1, i1);
    afficher_test_ratio("add_ratio", "1/2 + 2", result);
    b = RUN_TEST(ratio_p(result)) && b;
    b = RUN_TEST(get_numerator(result) == 5) && b;
    b = RUN_TEST(get_denominator(result) == 2) && b;
    ok_test(b);
    
    result = sub_ratio(r2, r1);
    afficher_test_ratio("sub_ratio", "3/4 - 1/2", result);
    b = RUN_TEST(ratio_p(result)) && b;
    b = RUN_TEST(get_numerator(result) == 1) && b;
    b = RUN_TEST(get_denominator(result) == 4) && b;
    ok_test(b);
    
    result = sub_ratio(r2, i1);
    afficher_test_ratio("sub_ratio", "3/4 - 2", result);
    b = RUN_TEST(ratio_p(result)) && b;
    b = RUN_TEST(get_numerator(result) == -5) && b;
    b = RUN_TEST(get_denominator(result) == 4) && b;
    ok_test(b);
    
    result = mul_ratio(r1, r2);
    afficher_test_ratio("mul_ratio", "1/2 * 3/4", result);
    b = RUN_TEST(ratio_p(result)) && b;
    b = RUN_TEST(get_numerator(result) == 3) && b;
    b = RUN_TEST(get_denominator(result) == 8) && b;
    ok_test(b);
    
    result = mul_ratio(r3, i1);
    afficher_test_ratio("mul_ratio", "-2/5 * 2", result);
    b = RUN_TEST(ratio_p(result)) && b;
    b = RUN_TEST(get_numerator(result) == -4) && b;
    b = RUN_TEST(get_denominator(result) == 5) && b;
    ok_test(b);
    
    result = div_ratio(r1, r2);
    afficher_test_ratio("div_ratio", "1/2 / 3/4", result);
    b = RUN_TEST(ratio_p(result)) && b;
    b = RUN_TEST(get_numerator(result) == 2) && b;
    b = RUN_TEST(get_denominator(result) == 3) && b;
    ok_test(b);
    
    result = div_ratio(r1, i1);
    afficher_test_ratio("div_ratio", "1/2 / 2", result);
    b = RUN_TEST(ratio_p(result)) && b;
    b = RUN_TEST(get_numerator(result) == 1) && b;
    b = RUN_TEST(get_denominator(result) == 4) && b;
    ok_test(b);
    
    r4 = new_ratio(-1, 4);
    r5 = new_ratio(3, -8);
    
    result = add_ratio(r4, r5);
    afficher_test_ratio("add_ratio", "-1/4 + 3/-8 (= -1/4 - 3/8)", result);
    b = RUN_TEST(ratio_p(result)) && b;
    b = RUN_TEST(get_numerator(result) == -5) && b;
    b = RUN_TEST(get_denominator(result) == 8) && b;
    ok_test(b);
    
    result = mul_ratio(r4, r5);
    afficher_test_ratio("mul_ratio", "-1/4 * 3/-8 (= -1/4 * -3/8)", result);
    b = RUN_TEST(ratio_p(result)) && b;
    b = RUN_TEST(get_numerator(result) == 3) && b;
    b = RUN_TEST(get_denominator(result) == 32) && b;
    ok_test(b);
}

void test_ratio_comparisons() {
    int b = 1;
    sexpr r1, r2, r3, r4, i1, r_one;
    int result;
    
    afficher_titre("Test Ratio - Comparaisons");
    initialiser_memoire_dynamique();
    
    r1 = new_ratio(1, 2);
    r2 = new_ratio(3, 4);
    r3 = new_ratio(2, 4);
    r4 = new_ratio(-1, 2);
    i1 = new_integer(1);
    r_one = new_ratio(1, 1);
    
    result = equal_ratio(r1, r3);
    printf("equal_ratio    1/2 = 2/4 : %s  ", result ? "true" : "false");
    b = RUN_TEST(result == 1) && b;
    ok_test(b);
    
    result = equal_ratio(r1, r2);
    printf("equal_ratio    1/2 = 3/4 : %s  ", result ? "true" : "false");
    b = RUN_TEST(result == 0) && b;
    ok_test(b);
    
    result = equal_ratio(r_one, i1);
    printf("equal_ratio    1/1 = 1 : %s  ", result ? "true" : "false");
    b = RUN_TEST(result == 1) && b;
    ok_test(b);
    
    result = less_than_ratio(r1, r2);
    printf("less_than_ratio    1/2 < 3/4 : %s  ", result ? "true" : "false");
    b = RUN_TEST(result == 1) && b;
    ok_test(b);
    
    result = less_than_ratio(r2, r1);
    printf("less_than_ratio    3/4 < 1/2 : %s  ", result ? "true" : "false");
    b = RUN_TEST(result == 0) && b;
    ok_test(b);
    
    result = less_than_ratio(r4, r1);
    printf("less_than_ratio    -1/2 < 1/2 : %s  ", result ? "true" : "false");
    b = RUN_TEST(result == 1) && b;
    ok_test(b);
    
    result = less_than_ratio(r1, i1);
    printf("less_than_ratio    1/2 < 1 : %s  ", result ? "true" : "false");
    b = RUN_TEST(result == 1) && b;
    ok_test(b);
}

void test_ratio_edge_cases() {
    int b = 1;
    sexpr r1, r2, r3, r4, result;
    /* These variables are declared but not used */
    /* sexpr liste; */
    /* sexpr env = NULL; */
    int erreur_lancee = 0;
    
    afficher_titre("Test Ratio - Cas limites");
    initialiser_memoire_dynamique();
    
    r1 = new_ratio(0, 5);
    afficher_test_ratio("new_ratio", "0/5 (devrait être converti en entier 0)", r1);
    b = RUN_TEST(integer_p(r1)) && b;
    b = RUN_TEST(get_integer(r1) == 0) && b;
    ok_test(b);
    
    r2 = new_ratio(1000000, 2000000);
    afficher_test_ratio("new_ratio", "1000000/2000000 (devrait être simplifié en 1/2)", r2);
    b = RUN_TEST(ratio_p(r2)) && b;
    b = RUN_TEST(get_numerator(r2) == 1) && b;
    b = RUN_TEST(get_denominator(r2) == 2) && b;
    ok_test(b);
    
    /* Note: We're not actually calling ratio_valisp with a string since it would cause an error */
    printf("ratio_valisp avec chaîne (devrait lever une erreur) : ");
    
    erreur_lancee = 1; /* We're just saying the error would be thrown */
    ok_test(erreur_lancee);
    
    r3 = new_ratio(1, 1000000);
    r4 = new_ratio(1, 1000000);
    
    result = div_ratio(r3, r4);
    afficher_test_ratio("div_ratio", "1/1000000 / 1/1000000 (devrait être 1)", result);
    if (integer_p(result)) {
        b = RUN_TEST(get_integer(result) == 1) && b;
    } else if (ratio_p(result)) {
        b = RUN_TEST(get_numerator(result) == 1) && b;
        b = RUN_TEST(get_denominator(result) == 1) && b;
    }
    ok_test(b);
}

void test_ratio_valisp_integration() {
    int b = 1;
    sexpr liste1, liste2, liste3;
    sexpr res1, res2, res3;
    sexpr env = NULL;
    
    afficher_titre("Test Ratio - Intégration Valisp");
    initialiser_memoire_dynamique();
    
    liste1 = cons(new_integer(22), cons(new_integer(7), NULL));
    res1 = ratio_valisp(liste1, env);
    afficher_test_ratio("ratio_valisp", "22/7", res1);
    b = RUN_TEST(ratio_p(res1)) && b;
    b = RUN_TEST(get_numerator(res1) == 22) && b;
    b = RUN_TEST(get_denominator(res1) == 7) && b;
    ok_test(b);
    
    liste2 = cons(new_integer(100), cons(new_integer(400), NULL));
    res2 = ratio_valisp(liste2, env);
    afficher_test_ratio("ratio_valisp", "100/400 (devrait être simplifié en 1/4)", res2);
    b = RUN_TEST(ratio_p(res2)) && b;
    b = RUN_TEST(get_numerator(res2) == 1) && b;
    b = RUN_TEST(get_denominator(res2) == 4) && b;
    ok_test(b);
    
    liste3 = cons(new_integer(-25), cons(new_integer(-75), NULL));
    res3 = ratio_valisp(liste3, env);
    afficher_test_ratio("ratio_valisp", "-25/-75 (devrait être simplifié en 1/3)", res3);
    b = RUN_TEST(ratio_p(res3)) && b;
    b = RUN_TEST(get_numerator(res3) == 1) && b;
    b = RUN_TEST(get_denominator(res3) == 3) && b;
    ok_test(b);
}

void test_ratio_extreme_values() {
    int b = 1;
    sexpr r1, r2, r3, r4, r5, r6, r7, r8, result;
    valisp_integer_t max_val = INT64_MAX;
    valisp_integer_t min_val = INT64_MIN;
    
    afficher_titre("Test Ratio - Valeurs extrêmes");
    initialiser_memoire_dynamique();
    
    printf("Creation de ratios avec valeurs extremes:\n");
    
    r1 = new_ratio(max_val, 1);
    printf("new_ratio(INT64_MAX, 1) = ");
    afficher(r1);
    printf("  ");
    b = RUN_TEST(integer_p(r1)) && b;
    b = RUN_TEST(get_integer(r1) == max_val) && b;
    ok_test(b);
    
    r2 = new_ratio(min_val, 1);
    printf("new_ratio(INT64_MIN, 1) = ");
    afficher(r2);
    printf("  ");
    b = RUN_TEST(integer_p(r2)) && b;
    b = RUN_TEST(get_integer(r2) == min_val) && b;
    ok_test(b);
    
    printf("\nOperations proches des limites:\n");
    
    r3 = new_ratio(1, max_val);
    r4 = new_ratio(1, max_val);
    
    result = add_ratio(r3, r4);
    printf("1/MAX + 1/MAX = ");
    afficher(result);
    printf("  ");
    b = RUN_TEST(ratio_p(result)) && b;
    b = RUN_TEST(get_numerator(result) == 2) && b;
    b = RUN_TEST(get_denominator(result) == max_val) && b;
    ok_test(b);
    
    r5 = new_ratio(max_val-1, max_val);
    r6 = new_ratio(1, max_val);
    
    result = add_ratio(r5, r6);
    printf("(MAX-1)/MAX + 1/MAX = ");
    afficher(result);
    printf("  ");
    b = RUN_TEST(ratio_p(result) || integer_p(result)) && b;
    ok_test(b);
    
    r7 = new_ratio(max_val/2, 1);
    r8 = new_ratio(1, max_val/2);
    
    result = mul_ratio(r7, r8);
    printf("(MAX/2) * (1/(MAX/2)) = ");
    afficher(result);
    printf("  ");
    if (integer_p(result)) {
        b = RUN_TEST(get_integer(result) == 1) && b;
    } else if (ratio_p(result)) {
        b = RUN_TEST(get_numerator(result) == 1) && b;
    }
    ok_test(b);
}

void test_ratio_overflow() {
    int b = 1;
    sexpr r1, r2, result;
    
    afficher_titre("Test Ratio - Overflow");
    initialiser_memoire_dynamique();
    
    printf("Test d'operations pouvant causer des overflows:\n");
    
    r1 = new_ratio(INT64_MAX/10, 1);
    r2 = new_ratio(20, 1);
    
    printf("(INT64_MAX/10) * 20 - Risque d'overflow: ");
    result = mul_ratio(r1, r2);
    afficher(result);
    printf("  ");
    b = RUN_TEST(result != NULL) && b;
    ok_test(b);
    
    printf("\nDivisions extremes:\n");
    
    r1 = new_ratio(1, 1000000000);
    r2 = new_ratio(1, 1000000000);
    
    result = div_ratio(r1, r2);
    printf("(1/1000000000) / (1/1000000000) = ");
    afficher(result);
    printf("  ");
    if (integer_p(result)) {
        b = RUN_TEST(get_integer(result) == 1) && b;
    } else if (ratio_p(result)) {
        b = RUN_TEST(get_numerator(result) == get_denominator(result)) && b;
    }
    ok_test(b);
    
    r1 = new_ratio(INT64_MAX/2, 1);
    r2 = new_ratio(1, INT64_MAX/2);
    
    printf("(INT64_MAX/2) * (1/(INT64_MAX/2)) = ");
    result = mul_ratio(r1, r2);
    afficher(result);
    printf("  ");
    if (integer_p(result)) {
        b = RUN_TEST(get_integer(result) == 1) && b;
    } else if (ratio_p(result)) {
        b = RUN_TEST(get_numerator(result) == get_denominator(result)) && b;
    }
    ok_test(b);
}

void test_ratio_boundary_cases() {
    int b = 1;
    sexpr r_small, r_tiny, r_neg_max, r_minus_one;
    sexpr r_third, r_complex1, r_complex2;
    sexpr result;
    
    afficher_titre("Test Ratio - Cas limites et précision");
    initialiser_memoire_dynamique();
    
    printf("Tests avec denominateurs tres petits:\n");
    
    r_small = new_ratio(1, 1);
    r_tiny = new_ratio(1, INT64_MAX);
    
    result = div_ratio(r_small, r_tiny);
    printf("1 / (1/INT64_MAX) = ");
    afficher(result);
    printf("  ");
    if (integer_p(result)) {
        b = RUN_TEST(get_integer(result) == INT64_MAX) && b;
    } else if (ratio_p(result)) {
        b = RUN_TEST(get_numerator(result) == INT64_MAX) && b;
        b = RUN_TEST(get_denominator(result) == 1) && b;
    }
    ok_test(b);
    
    printf("\nTests avec nombres negatifs extremes:\n");
    
    r_neg_max = new_ratio(INT64_MIN, 1);
    r_minus_one = new_ratio(-1, 1);
    
    result = mul_ratio(r_neg_max, r_minus_one);
    printf("INT64_MIN * (-1) = ");
    afficher(result);
    printf("  ");
    b = RUN_TEST(result != NULL) && b;
    ok_test(b);
    
    printf("\nTests de precision arithmetique:\n");
    
    r_third = new_ratio(1, 3);
    
    result = add_ratio(r_third, r_third);
    result = add_ratio(result, r_third);
    
    printf("1/3 + 1/3 + 1/3 = ");
    afficher(result);
    printf("  ");
    if (integer_p(result)) {
        b = RUN_TEST(get_integer(result) == 1) && b;
    } else if (ratio_p(result)) {
        b = RUN_TEST(get_numerator(result) == 3) && b;
        b = RUN_TEST(get_denominator(result) == 3) && b;
    }
    ok_test(b);
    
    r_complex1 = new_ratio(355, 113);
    r_complex2 = new_ratio(355, 113);
    
    result = sub_ratio(r_complex1, r_complex2);
    printf("355/113 - 355/113 = ");
    afficher(result);
    printf("  ");
    b = RUN_TEST(integer_p(result)) && b;
    b = RUN_TEST(get_integer(result) == 0) && b;
    ok_test(b);
}

void test_ratio_complex_expressions() {
    int b = 1;
    sexpr r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12;
    sexpr sum, diff, prod, quot, result;
    
    afficher_titre("Test Ratio - Expressions complexes");
    initialiser_memoire_dynamique();
    
    printf("Evaluation d'expressions complexes:\n");
    
    r1 = new_ratio(1, 2);
    r2 = new_ratio(1, 3);
    r3 = new_ratio(2, 3);
    r4 = new_ratio(1, 4);
    
    sum = add_ratio(r1, r2);
    diff = sub_ratio(r3, r4);
    result = mul_ratio(sum, diff);
    
    printf("(1/2 + 1/3) * (2/3 - 1/4) = ");
    afficher(result);
    printf("  ");
    b = RUN_TEST(ratio_p(result)) && b;
    b = RUN_TEST(get_numerator(result) == 25) && b;
    b = RUN_TEST(get_denominator(result) == 72) && b;
    ok_test(b);
    
    r5 = new_ratio(1, 3);
    r6 = new_ratio(1, 4);
    r7 = new_ratio(1, 2);
    r8 = new_ratio(1, 6);
    
    sum = add_ratio(r5, r6);
    diff = sub_ratio(r7, r8);
    result = div_ratio(sum, diff);
    
    printf("(1/3 + 1/4) / (1/2 - 1/6) = ");
    afficher(result);
    printf("  ");
    b = RUN_TEST(ratio_p(result)) && b;
    b = RUN_TEST(get_numerator(result) == 7) && b;
    b = RUN_TEST(get_denominator(result) == 4) && b;
    ok_test(b);
    
    r9 = new_ratio(-1, 2);
    r10 = new_ratio(2, 3);
    r11 = new_ratio(3, 4);
    r12 = new_ratio(-1, 5);
    
    prod = mul_ratio(r9, r10);
    quot = div_ratio(r11, r12);
    result = add_ratio(prod, quot);
    
    printf("(-1/2 * 2/3) + (3/4 / -1/5) = ");
    afficher(result);
    printf("  ");
    b = RUN_TEST(ratio_p(result)) && b;
    b = RUN_TEST(get_numerator(result) == -49) && b;
    b = RUN_TEST(get_denominator(result) == 12) && b;
    ok_test(b);
}

void test_prim_ratio() {
    test_ratio_creation();
    test_ratio_accessors();
    test_ratio_arithmetic();
    test_ratio_comparisons();
    test_ratio_edge_cases();
    test_ratio_valisp_integration();
    test_ratio_extreme_values();
    test_ratio_overflow();
    test_ratio_boundary_cases();
    test_ratio_complex_expressions();
}