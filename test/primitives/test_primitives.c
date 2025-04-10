#include <stdio.h>
#include <string.h>
#include "allocateur.h"
#include "types.h"
#include "tests.h"
#include "primitives.h"
#include "mes_tests.h"

/* Pour les opérations binaires (add, sub, mul, div, mod) */
void afficher_test_binaire(char* nom_fonction, int val1, char* operateur, int val2, sexpr resultat) {
    printf("%s %d %s %d = ", nom_fonction, val1, operateur, val2);
    afficher(resultat);
    printf("  ");
}

/* Pour les comparaisons */
void afficher_test_comparaison(char* nom_fonction, int val1, char* operateur, int val2, sexpr resultat) {
    printf("%s %d %s %d : ", nom_fonction, val1, operateur, val2);
    afficher(resultat);
    printf("  ");
}

/* Pour les tests de type */
void afficher_test_type(char* nom_fonction, char* description, sexpr resultat) {
    printf("%s %s : ", nom_fonction, description);
    afficher(resultat);
    printf("  ");
}

/* Pour les tests sur les listes */
void afficher_test_liste(char* nom_fonction, char* description, sexpr resultat) {
    printf("%s %s : ", nom_fonction, description);
    afficher(resultat);
    printf("  ");
}

/****************/
/*              */
/*  Primitives  */
/*              */
/****************/

#ifdef TEST_PRIMITIVES_ADD
void test_add() {
    int b = 1;
    sexpr liste, env, resultat;
    
    afficher_titre("Test Additions");
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Test avec 2 paramètres : 10 + 5 */
    liste = cons(new_integer(10), cons(new_integer(5), NULL));
    resultat = add_valisp(liste, env);
    
    printf("add_valisp 10 + 5 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 15) && b;
    ok_test(b);
    
    /* Test avec 3 paramètres : 10 + 5 + 7 */
    liste = cons(new_integer(10), cons(new_integer(5), cons(new_integer(7), NULL)));
    resultat = add_valisp(liste, env);
    
    printf("add_valisp 10 + 5 + 7 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 22) && b;
    ok_test(b);
    
    /* Test avec 4 paramètres : 1 + 2 + 3 + 4 */
    liste = cons(new_integer(1), 
                cons(new_integer(2), 
                    cons(new_integer(3), 
                        cons(new_integer(4), NULL))));
    resultat = add_valisp(liste, env);
    
    printf("add_valisp 1 + 2 + 3 + 4 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 10) && b;
    ok_test(b);

    /* Test avec 0 paramètre : devrait renvoyer 0 ou une erreur */
    liste = NULL;
    resultat = add_valisp(liste, env);
    
    printf("add_valisp (sans paramètre) = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 0) && b;
    ok_test(b);
    
    
    /* Test avec 1 paramètre : devrait renvoyer le paramètre lui-même */
    liste = cons(new_integer(42), NULL);
    resultat = add_valisp(liste, env);
    
    printf("add_valisp 42 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 42) && b;
    ok_test(b);
    printf("\n");
}
#endif

#ifdef TEST_PRIMITIVES_SUB
void test_sub() {
    int b = 1;
    sexpr liste, env, resultat;
    
    afficher_titre("Test Soustractions");
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Test avec 2 paramètres : 15 - 7 */
    liste = cons(new_integer(15), cons(new_integer(7), NULL));
    resultat = sub_valisp(liste, env);
    
    printf("sub_valisp 15 - 7 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 8) && b;
    ok_test(b);
    
    /* Test avec 3 paramètres : 20 - 5 - 3 */
    liste = cons(new_integer(20), cons(new_integer(5), cons(new_integer(3), NULL)));
    resultat = sub_valisp(liste, env);
    
    printf("sub_valisp 20 - 5 - 3 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 12) && b;
    ok_test(b);
    
    /* Test avec 4 paramètres : 100 - 20 - 30 - 10 */
    liste = cons(new_integer(100), 
                cons(new_integer(20), 
                    cons(new_integer(30), 
                        cons(new_integer(10), NULL))));
    resultat = sub_valisp(liste, env);
    
    printf("sub_valisp 100 - 20 - 30 - 10 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 40) && b;
    ok_test(b);

    /* Test avec 0 paramètre : devrait renvoyer 0 ou une erreur */
    liste = NULL;
    resultat = sub_valisp(liste, env);
    
    printf("sub_valisp (sans paramètre) = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 0) && b;
    ok_test(b);

    
    /* Test avec 1 paramètre : devrait inverser le signe du paramètre */
    liste = cons(new_integer(42), NULL);
    resultat = sub_valisp(liste, env);
    
    printf("sub_valisp 42 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == -42) && b;
    ok_test(b);
    printf("\n");
}

#endif

#ifdef TEST_PRIMITIVES_PRODUIT
void test_produit() {
    int b = 1;
    sexpr liste, env, resultat;
    
    afficher_titre("Test Multiplications");
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Test avec 2 paramètres : 6 * 7 */
    liste = cons(new_integer(6), cons(new_integer(7), NULL));
    resultat = produit_valisp(liste, env);
    
    printf("produit_valisp 6 * 7 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 42) && b;
    ok_test(b);
    
    /* Test avec 3 paramètres : 2 * 3 * 4 */
    liste = cons(new_integer(2), 
                cons(new_integer(3), 
                    cons(new_integer(4), NULL)));
    resultat = produit_valisp(liste, env);
    
    printf("produit_valisp 2 * 3 * 4 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 24) && b;
    ok_test(b);
    
    /* Test avec 4 paramètres : 1 * 2 * 3 * 5 */
    liste = cons(new_integer(1), 
                cons(new_integer(2), 
                    cons(new_integer(3), 
                        cons(new_integer(5), NULL))));
    resultat = produit_valisp(liste, env);
    
    printf("produit_valisp 1 * 2 * 3 * 5 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 30) && b;
    ok_test(b);

    /* Test avec 0 paramètre : devrait renvoyer 1 (élément neutre) */
    liste = NULL;
    resultat = produit_valisp(liste, env);
    
    printf("produit_valisp (sans paramètre) = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 1) && b;
    ok_test(b);
    
    /* Test avec 1 paramètre : devrait renvoyer le paramètre lui-même */
    liste = cons(new_integer(42), NULL);
    resultat = produit_valisp(liste, env);
    
    printf("produit_valisp 42 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 42) && b;
    ok_test(b);
    printf("\n");
}
#endif

#ifdef TEST_PRIMITIVES_DIV
void test_div() {
    int b = 1;
    sexpr liste, env, resultat;
    
    afficher_titre("Test Divisions");
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Test avec 2 paramètres : 21 / 7 */
    liste = cons(new_integer(21), cons(new_integer(7), NULL));
    resultat = div_valisp(liste, env);
    
    printf("div_valisp 21 / 7 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 3) && b;
    ok_test(b);
    
    /* Test avec 3 paramètres : 100 / 5 / 2 */
    liste = cons(new_integer(100), 
                cons(new_integer(5), 
                    cons(new_integer(2), NULL)));
    resultat = div_valisp(liste, env);
    
    printf("div_valisp 100 / 5 / 2 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 10) && b;
    ok_test(b);
    
    /* Test avec 4 paramètres : 120 / 2 / 3 / 5 */
    liste = cons(new_integer(120), 
                cons(new_integer(2), 
                    cons(new_integer(3), 
                        cons(new_integer(5), NULL))));
    resultat = div_valisp(liste, env);
    
    printf("div_valisp 120 / 2 / 3 / 5 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 4) && b;
    ok_test(b);
    
    /* Test avec 1 paramètre : devrait retourner 1/paramètre */
    liste = cons(new_integer(4), NULL);
    resultat = div_valisp(liste, env);
    
    printf("div_valisp 4 = ");
    afficher(resultat);
    printf("  ");
    
    b = RUN_TEST(integer_p(resultat)) && b;
    b = RUN_TEST(get_integer(resultat) == 1/4) && b; 
    ok_test(b);
    printf("\n");
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
    
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Test 1: 10 % 3 */
    val1 = 10;
    val2 = 3;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = mod_valisp(liste, env);
    
    afficher_test_binaire("mod_valisp", val1, "%", val2, c);
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == val1 % val2) && b;

    ok_test(b);
    
    /* Test 2: 7 % 7 */
    val1 = 7;
    val2 = 7;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = mod_valisp(liste, env);
    
    afficher_test_binaire("mod_valisp", val1, "%", val2, c);
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == val1 % val2) && b;
    
    ok_test(b);
    printf("\n");
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
    
    /* Test 1: 5 < 10 */
    val1 = 5;
    val2 = 10;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = less_than_valisp(liste, env);
    
    afficher_test_comparaison("less_than_valisp", val1, "<", val2, c);
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == (val1 < val2 ? 1 : 0)) && b;

    ok_test(b);
    
    /* Test 2: 10 < 5 */
    val1 = 10;
    val2 = 5;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = less_than_valisp(liste, env);
    
    afficher_test_comparaison("less_than_valisp", val1, "<", val2, c);
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == (val1 < val2 ? 1 : 0)) && b;

    ok_test(b);
    
    /* Test equal */
    
    /* Test 1: 7 = 7 */
    val1 = 7;
    val2 = 7;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = equal_valisp(liste, env);
    
    afficher_test_comparaison("equal_valisp", val1, "=", val2, c);
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == (val1 == val2 ? 1 : 0)) && b;

    ok_test(b);
    
    /* Test 2: 8 = 9 */
    val1 = 8;
    val2 = 9;
    a = new_integer(val1);
    b_expr = new_integer(val2);
    liste = cons(a, cons(b_expr, NULL));
    c = equal_valisp(liste, env);

    afficher_test_comparaison("equal_valisp", val1, "=", val2, c);
    
    b = RUN_TEST(integer_p(c)) && b;
    b = RUN_TEST(get_integer(c) == (val1 == val2 ? 1 : 0)) && b;

    ok_test(b);
    printf("\n");
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
    
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Test avec un entier */
    val = new_integer(42);
    liste = cons(val, NULL);
    res = type_of_valisp(liste, env);
    
    afficher_test_type("type_of_valisp", "Type de 42", res);
    
    b = RUN_TEST(symbol_p(res)) && b;
    b = RUN_TEST(strcmp(get_symbol(res), "entier") == 0) && b;

    ok_test(b);
    
    /* Test avec une chaîne */
    val = new_string("Bonjour");
    liste = cons(val, NULL);
    res = type_of_valisp(liste, env);

    afficher_test_type("type_of_valisp", "Type de 'Bonjour'", res);
    
    b = RUN_TEST(symbol_p(res)) && b;
    b = RUN_TEST(strcmp(get_symbol(res), "chaine") == 0) && b;

    ok_test(b);
    
    /* Test avec un symbole */
    val = new_symbol("x");
    liste = cons(val, NULL);
    res = type_of_valisp(liste, env);

    afficher_test_type("type_of_valisp", "Type de 'x'", res);
    
    b = RUN_TEST(symbol_p(res)) && b;
    b = RUN_TEST(strcmp(get_symbol(res), "symbole") == 0) && b;

    ok_test(b);
    
    /* Test avec une liste */
    val = cons(new_integer(1), cons(new_integer(2), NULL));
    liste = cons(val, NULL);
    res = type_of_valisp(liste, env);

    afficher_test_type("type_of_valisp", "Type de '(1 2)'", res);
    
    b = RUN_TEST(symbol_p(res)) && b;
    b = RUN_TEST(strcmp(get_symbol(res), "liste") == 0) && b;
    
    ok_test(b);
    printf("\n");
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
    printf("\n\n");
    
    /* Test car */
    res = car_valisp(cons(liste, NULL), env);
    
    afficher_test_liste("car_valisp", "car de la liste", res);
    
    b = RUN_TEST(integer_p(res)) && b;
    b = RUN_TEST(get_integer(res) == 1) && b;
    
    ok_test(b);
    
    /* Test cdr */
    res = cdr_valisp(cons(liste, NULL), env);
    
    afficher_test_liste("cdr_valisp", "cdr de la liste", res);
    
    b = RUN_TEST(cons_p(res)) && b;
    b = RUN_TEST(integer_p(car(res))) && b;
    b = RUN_TEST(get_integer(car(res)) == 2) && b;
    
    ok_test(b);
    
    /* Test cons */
    val1 = new_integer(4);
    res = cons_valisp(cons(val1, cons(liste, NULL)), env);
    
    afficher_test_liste("cons_valisp", "cons 4 et la liste", res);
    
    b = RUN_TEST(cons_p(res)) && b;
    b = RUN_TEST(integer_p(car(res))) && b;
    b = RUN_TEST(get_integer(car(res)) == 4) && b;
    b = RUN_TEST(cons_p(cdr(res))) && b;
    
    ok_test(b);
    printf("\n");
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
    
    initialiser_memoire_dynamique();
    env = NULL;
    
    /* Test avec un entier */
    val = new_integer(42);
    liste = cons(val, NULL);
    
    printf("print_valisp    Affichage d'un entier : ");
    res = print_valisp(liste, env);
    
    b = RUN_TEST(res == NULL) && b;

    ok_test(b);
    
    /* Test avec une chaîne */
    val = new_string("Bonjour monde");
    liste = cons(val, NULL);
    
    printf("print_valisp    Affichage d'une chaîne : ");
    res = print_valisp(liste, env);

    b = RUN_TEST(res == NULL) && b;

    ok_test(b);
    
    /* Test avec un symbole */
    val = new_symbol("symbole");
    liste = cons(val, NULL);
    
    printf("print_valisp    Affichage d'un symbole : ");
    res = print_valisp(liste, env);
    
    b = RUN_TEST(res == NULL) && b;
    
    ok_test(b);

    /* Test avec une liste */
    val = cons(new_integer(1), cons(new_integer(2), cons(new_integer(3), NULL)));
    liste = cons(val, NULL);
    
    printf("print_valisp    Affichage d'une liste : ");
    res = print_valisp(liste, env);
    
    b = RUN_TEST(res == NULL) && b;
    
    ok_test(b);
    printf("\n");
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