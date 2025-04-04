#include <stdio.h>
#include <string.h>
#include "allocateur.h"
#include "types.h"
#include "tests.h"
#include "primitives.h"
#include "mes_tests.h"



/****************/
/*              */
/*  Primitives  */
/*              */
/****************/

#ifdef TEST_PRIMITIVES_ADD
void test_add() {
    int b = 1;
    sexpr a;
    sexpr b_expr;
    sexpr c;
    sexpr liste;
    sexpr env;
    int val_a = 10;
    int val_b = 5;
    
    afficher_titre("Test Additions");
    printf("add_valisp    ");
    
    initialiser_memoire_dynamique();
    a = new_integer(val_a);
    b_expr = new_integer(val_b);
    liste = cons(a, cons(b_expr, NULL));
    env = NULL;
    c = add_valisp(liste, env);
    
    printf("%d + %d = ", val_a, val_b);
    afficher(c);
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == val_a + val_b) && b;
    
    ok_test(b);
}
#endif

#ifdef TEST_PRIMITIVES_SUB
void test_sub() {
    int b = 1;
    sexpr a;
    sexpr b_expr;
    sexpr c;
    sexpr liste;
    sexpr env;
    int val1, val2;
    
    afficher_titre("Test Soustractions");
    printf("sub_valisp    ");
    
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Test 1: 15 - 7 */
    val1 = 15;
    val2 = 7;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = sub_valisp(liste, env);
    
    printf("%d - %d = ", val1, val2);
    afficher(c);
    printf("  ");
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == val1 - val2) && b;
    
    /* Test 2: 3 - 10 (négatif) */
    val1 = 3;
    val2 = 10;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = sub_valisp(liste, env);
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == val1 - val2) && b;
    
    ok_test(b);
}
#endif

#ifdef TEST_PRIMITIVES_PRODUIT
void test_produit() {
    int b = 1;
    sexpr a;
    sexpr b_expr;
    sexpr c;
    sexpr liste;
    sexpr env;
    int val1, val2;
    
    afficher_titre("Test Multiplications");
    printf("produit_valisp ");
    
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Test 1: 6 * 7 */
    val1 = 6;
    val2 = 7;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = produit_valisp(liste, env);
    
    printf("%d * %d = ", val1, val2);
    afficher(c);
    printf("  ");
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == val1 * val2) && b;
    
    /* Test 2: 0 * 5 */
    val1 = 0;
    val2 = 5;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = produit_valisp(liste, env);
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == val1 * val2) && b;
    
    ok_test(b);
}
#endif

#ifdef TEST_PRIMITIVES_DIV
void test_div() {
    int b = 1;
    sexpr a;
    sexpr b_expr;
    sexpr c;
    sexpr liste;
    sexpr env;
    int val1, val2;
    
    afficher_titre("Test Divisions");
    printf("div_valisp    ");
    
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Test 1: 21 / 7 */
    val1 = 21;
    val2 = 7;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = div_valisp(liste, env);
    
    printf("%d / %d = ", val1, val2);
    afficher(c);
    printf("  ");
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == val1 / val2) && b;
    
    /* Test 2: 10 / 3 (division entière) */
    val1 = 10;
    val2 = 3;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = div_valisp(liste, env);
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == val1 / val2) && b;
    
    ok_test(b);
    
    /* Note: On ne teste pas la division par zéro 
     * car cela provoquerait une erreur fatale */
}
#endif

#ifdef TEST_PRIMITIVES_MOD
void test_mod() {
    int b = 1;
    sexpr a;
    sexpr b_expr;
    sexpr c;
    sexpr liste;
    sexpr env;
    int val1, val2;
    
    afficher_titre("Test Modulo");
    printf("mod_valisp    ");
    
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Test 1: 10 % 3 */
    val1 = 10;
    val2 = 3;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = mod_valisp(liste, env);
    
    printf("%d %% %d = ", val1, val2);
    afficher(c);
    printf("  ");
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == val1 % val2) && b;
    
    /* Test 2: 7 % 7 */
    val1 = 7;
    val2 = 7;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = mod_valisp(liste, env);
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == val1 % val2) && b;
    
    ok_test(b);
}
#endif

#ifdef TEST_PRIMITIVES_COMP
void test_comparaisons() {
    int b = 1;
    sexpr a;
    sexpr b_expr;
    sexpr c;
    sexpr liste;
    sexpr env;
    int val1, val2;
    
    afficher_titre("Test Comparaisons");
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Test less_than */
    printf("less_than_valisp ");
    
    /* Test 1: 5 < 10 */
    val1 = 5;
    val2 = 10;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = less_than_valisp(liste, env);
    
    printf("%d < %d = ", val1, val2);
    afficher(c);
    printf("  ");
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == (val1 < val2 ? 1 : 0)) && b;
    
    /* Test 2: 10 < 5 */
    val1 = 10;
    val2 = 5;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = less_than_valisp(liste, env);
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == (val1 < val2 ? 1 : 0)) && b;
    
    ok_test(b);
    
    /* Test equal */
    b = 1;
    printf("equal_valisp   ");
    
    /* Test 1: 7 = 7 */
    val1 = 7;
    val2 = 7;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = equal_valisp(liste, env);
    
    printf("%d = %d : ", val1, val2);
    afficher(c);
    printf("  ");
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == (val1 == val2 ? 1 : 0)) && b;
    
    /* Test 2: 8 = 9 */
    val1 = 8;
    val2 = 9;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = equal_valisp(liste, env);
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == (val1 == val2 ? 1 : 0)) && b;
    
    ok_test(b);
}
#endif

#ifdef TEST_PRIMITIVES_TYPEOF
void test_type_of() {
    int b = 1;
    sexpr val;
    sexpr res;
    sexpr liste;
    sexpr env;
    
    afficher_titre("Test Type-Of");
    printf("type_of_valisp ");
    
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Test avec un entier */
    val = new_integer(42);
    liste = cons(val, NULL);
    res = type_of_valisp(liste, env);
    
    printf("Type de 42 : ");
    afficher(res);
    printf("  ");
    
    b = RUN_TEST(string_p(res)) && b;
    b = RUN_TEST(strcmp(get_string(res), "entier") == 0) && b;
    
    /* Test avec une chaîne */
    val = new_string("Bonjour");
    liste = cons(val, NULL);
    res = type_of_valisp(liste, env);
    
    b = RUN_TEST(string_p(res)) && b;
    b = RUN_TEST(strcmp(get_string(res), "chaine") == 0) && b;
    
    /* Test avec un symbole */
    val = new_symbol("x");
    liste = cons(val, NULL);
    res = type_of_valisp(liste, env);
    
    b = RUN_TEST(string_p(res)) && b;
    b = RUN_TEST(strcmp(get_string(res), "symbole") == 0) && b;
    
    /* Test avec une liste */
    val = cons(new_integer(1), cons(new_integer(2), NULL));
    liste = cons(val, NULL);
    res = type_of_valisp(liste, env);
    
    b = RUN_TEST(string_p(res)) && b;
    b = RUN_TEST(strcmp(get_string(res), "liste") == 0) && b;
    
    ok_test(b);
}
#endif

#ifdef TEST_PRIMITIVES_LISTE
void test_car_cdr_cons() {
    int b = 1;
    sexpr liste;
    sexpr val1, val2, val3;
    sexpr res;
    sexpr env;
    
    afficher_titre("Test Car/Cdr/Cons");
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Création d'une liste (1 2 3) */
    val1 = new_integer(1);
    val2 = new_integer(2);
    val3 = new_integer(3);
    liste = cons(val1, cons(val2, cons(val3, NULL)));
    
    printf("Liste de test : ");
    afficher(liste);
    printf("\n");
    
    /* Test car */
    printf("car_valisp    ");
    res = car_valisp(cons(liste, NULL), env);
    
    printf("car de la liste : ");
    afficher(res);
    printf("  ");
    
    b = RUN_TEST(integer_p(res)) && b;
    b = RUN_TEST(get_integer(res) == 1) && b;
    
    ok_test(b);
    
    /* Test cdr */
    b = 1;
    printf("cdr_valisp    ");
    res = cdr_valisp(cons(liste, NULL), env);
    
    printf("cdr de la liste : ");
    afficher(res);
    printf("  ");
    
    b = RUN_TEST(cons_p(res)) && b;
    b = RUN_TEST(integer_p(car(res))) && b;
    b = RUN_TEST(get_integer(car(res)) == 2) && b;
    
    ok_test(b);
    
    /* Test cons */
    b = 1;
    printf("cons_valisp   ");
    val1 = new_integer(4);
    res = cons_valisp(cons(val1, cons(liste, NULL)), env);
    
    printf("cons 4 et la liste : ");
    afficher(res);
    printf("  ");
    
    b = RUN_TEST(cons_p(res)) && b;
    b = RUN_TEST(integer_p(car(res))) && b;
    b = RUN_TEST(get_integer(car(res)) == 4) && b;
    b = RUN_TEST(cons_p(cdr(res))) && b;
    
    ok_test(b);
}
#endif

#ifdef TEST_PRIMITIVES_PRINT
void test_print() {
    int b = 1;
    sexpr val;
    sexpr liste;
    sexpr res;
    sexpr env;
    
    afficher_titre("Test Print");
    printf("print_valisp  ");
    
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Test avec un entier */
    val = new_integer(42);
    liste = cons(val, NULL);
    res = print_valisp(liste, env);
    
    b = RUN_TEST(res == NULL) && b;
    
    /* Test avec une chaîne */
    val = new_string("Bonjour monde");
    liste = cons(val, NULL);
    res = print_valisp(liste, env);
    
    b = RUN_TEST(res == NULL) && b;
    
    /* Test avec un symbole */
    val = new_symbol("symbole");
    liste = cons(val, NULL);
    res = print_valisp(liste, env);
    
    b = RUN_TEST(res == NULL) && b;
    
    /* Test avec une liste */
    val = cons(new_integer(1), cons(new_integer(2), cons(new_integer(3), NULL)));
    liste = cons(val, NULL);
    res = print_valisp(liste, env);
    
    b = RUN_TEST(res == NULL) && b;
    
    ok_test(b);
}
#endif

#ifdef TEST_PRIMITIVES
void test_primitives() {
    test_add();
    test_sub();
    test_produit();
    test_div();
    test_mod();
    test_comparaisons();
    test_type_of();
    test_car_cdr_cons();
    test_print();
}
#endif