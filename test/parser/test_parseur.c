#include <stdio.h>
#include <string.h>
#include "tests.h"
#include "allocateur.h"
#include "types.h"
#include "parseur.h"
#include "mes_tests.h"

void test_parse_entier() {
    int b = 1;
    sexpr result;
    int i;
    
    afficher_titre("Test Parser - Entiers");
    initialiser_memoire_dynamique();
    
    i = parseur("42", 0, &result);
    printf("parseur \"42\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(integer_p(result)) && b;
    b = RUN_TEST(get_integer(result) == 42) && b;
    b = RUN_TEST(i == 2) && b;  /* Test position after parsing */
    
    ok_test(b);
    
    i = parseur("-123", 0, &result);
    printf("parseur \"-123\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(integer_p(result)) && b;
    b = RUN_TEST(get_integer(result) == -123) && b;
    b = RUN_TEST(i == 4) && b;  /* Test position after parsing */
    
    ok_test(b);
    
    i = parseur("42abc", 0, &result);
    printf("parseur \"42abc\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(symbol_p(result)) && b;
    b = RUN_TEST(strcmp(get_symbol(result), "42abc") == 0) && b;
    b = RUN_TEST(i == 5) && b;  /* Test position after parsing entire symbol */
    
    ok_test(b);
}

void test_parse_symbole() {
    int b = 1;
    sexpr result;
    int i;
    
    afficher_titre("Test Parser - Symboles");
    initialiser_memoire_dynamique();
    
    i = parseur("test", 0, &result);
    printf("parseur \"test\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(symbol_p(result)) && b;
    b = RUN_TEST(strcmp(get_symbol(result), "test") == 0) && b;
    b = RUN_TEST(i == 4) && b;  /* Test position after parsing */
    
    ok_test(b);
    
    i = parseur("nil", 0, &result);
    printf("parseur \"nil\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(result == NULL) && b;
    b = RUN_TEST(i == 3) && b;  /* Test position after parsing */
    
    ok_test(b);
    
    i = parseur("+", 0, &result);
    printf("parseur \"+\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(symbol_p(result)) && b;
    b = RUN_TEST(strcmp(get_symbol(result), "+") == 0) && b;
    b = RUN_TEST(i == 1) && b;  /* Test position after parsing */
    
    ok_test(b);
    
    i = parseur("t", 0, &result);
    printf("parseur \"t\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(symbol_p(result)) && b;
    b = RUN_TEST(strcmp(get_symbol(result), "t") == 0) && b;
    b = RUN_TEST(i == 1) && b;  /* Test position after parsing */
    
    ok_test(b);
}

void test_parse_chaine() {
    int b = 1;
    sexpr result;
    int i;
    
    afficher_titre("Test Parser - Chaines");
    initialiser_memoire_dynamique();
    
    i = parseur("\"hello\"", 0, &result);
    printf("parseur \"\\\"hello\\\"\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(string_p(result)) && b;
    b = RUN_TEST(strcmp(get_string(result), "hello") == 0) && b;
    b = RUN_TEST(i == 7) && b;  /* Test position after parsing */
    
    ok_test(b);
    
    i = parseur("\"test\\\"escape\"", 0, &result);
    printf("parseur \"\\\"test\\\\\\\"escape\\\"\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(string_p(result)) && b;
    b = RUN_TEST(strcmp(get_string(result), "test\"escape") == 0) && b;
    b = RUN_TEST(i == 14) && b;  /* Test position after parsing */
    
    ok_test(b);
    
    i = parseur("\"hello\\nworld\"", 0, &result);
    printf("parseur \"\\\"hello\\\\nworld\\\"\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(string_p(result)) && b;
    b = RUN_TEST(strcmp(get_string(result), "hello\nworld") == 0) && b;
    b = RUN_TEST(i == 14) && b;  /* Test position after parsing */
    
    ok_test(b);
}

void test_parse_liste() {
    int b = 1;
    sexpr result;
    int i;
    
    afficher_titre("Test Parser - Listes");
    initialiser_memoire_dynamique();
    
    i = parseur("()", 0, &result);
    printf("parseur \"()\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(result == NULL) && b;
    b = RUN_TEST(i == 2) && b;  /* Test position after parsing */
    
    ok_test(b);
    
    i = parseur("(1 2 3)", 0, &result);
    printf("parseur \"(1 2 3)\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(cons_p(result)) && b;
    b = RUN_TEST(list_p(result)) && b;
    b = RUN_TEST(integer_p(car(result))) && b;
    b = RUN_TEST(get_integer(car(result)) == 1) && b;
    b = RUN_TEST(cons_p(cdr(result))) && b;
    b = RUN_TEST(integer_p(car(cdr(result)))) && b;
    b = RUN_TEST(get_integer(car(cdr(result))) == 2) && b;
    b = RUN_TEST(integer_p(car(cdr(cdr(result))))) && b;
    b = RUN_TEST(get_integer(car(cdr(cdr(result)))) == 3) && b;
    b = RUN_TEST(cdr(cdr(cdr(result))) == NULL) && b;
    b = RUN_TEST(i == 7) && b;  /* Test position after parsing */
    
    ok_test(b);
    
    i = parseur("(a b c)", 0, &result);
    printf("parseur \"(a b c)\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(cons_p(result)) && b;
    b = RUN_TEST(symbol_p(car(result))) && b;
    b = RUN_TEST(strcmp(get_symbol(car(result)), "a") == 0) && b;
    b = RUN_TEST(symbol_p(car(cdr(result)))) && b;
    b = RUN_TEST(strcmp(get_symbol(car(cdr(result))), "b") == 0) && b;
    b = RUN_TEST(symbol_p(car(cdr(cdr(result))))) && b;
    b = RUN_TEST(strcmp(get_symbol(car(cdr(cdr(result)))), "c") == 0) && b;
    b = RUN_TEST(i == 7) && b;  /* Test position after parsing */
    
    ok_test(b);
    
    i = parseur("(+ 1 2)", 0, &result);
    printf("parseur \"(+ 1 2)\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(cons_p(result)) && b;
    b = RUN_TEST(symbol_p(car(result))) && b;
    b = RUN_TEST(strcmp(get_symbol(car(result)), "+") == 0) && b;
    b = RUN_TEST(integer_p(car(cdr(result)))) && b;
    b = RUN_TEST(get_integer(car(cdr(result))) == 1) && b;
    b = RUN_TEST(integer_p(car(cdr(cdr(result))))) && b;
    b = RUN_TEST(get_integer(car(cdr(cdr(result)))) == 2) && b;
    b = RUN_TEST(i == 7) && b;  /* Test position after parsing */
    
    ok_test(b);
}

void test_parse_quote() {
    int b = 1;
    sexpr result;
    int i;
    
    afficher_titre("Test Parser - Quotes");
    initialiser_memoire_dynamique();
    
    i = parseur("'42", 0, &result);
    printf("parseur \"'42\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(cons_p(result)) && b;
    b = RUN_TEST(symbol_p(car(result))) && b;
    b = RUN_TEST(strcmp(get_symbol(car(result)), "quote") == 0) && b;
    b = RUN_TEST(integer_p(car(cdr(result)))) && b;
    b = RUN_TEST(get_integer(car(cdr(result))) == 42) && b;
    b = RUN_TEST(i == 3) && b;  /* Test position after parsing */
    
    ok_test(b);
    
    i = parseur("'(1 2 3)", 0, &result);
    printf("parseur \"'(1 2 3)\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(cons_p(result)) && b;
    b = RUN_TEST(symbol_p(car(result))) && b;
    b = RUN_TEST(strcmp(get_symbol(car(result)), "quote") == 0) && b;
    b = RUN_TEST(cons_p(car(cdr(result)))) && b;
    b = RUN_TEST(i == 8) && b;  /* Test position after parsing */
    
    ok_test(b);
    
    i = parseur("'abc", 0, &result);
    printf("parseur \"'abc\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(cons_p(result)) && b;
    b = RUN_TEST(symbol_p(car(result))) && b;
    b = RUN_TEST(strcmp(get_symbol(car(result)), "quote") == 0) && b;
    b = RUN_TEST(symbol_p(car(cdr(result)))) && b;
    b = RUN_TEST(strcmp(get_symbol(car(cdr(result))), "abc") == 0) && b;
    b = RUN_TEST(i == 4) && b;  /* Test position after parsing */
    
    ok_test(b);
}

void test_nettoyer_espaces() {
    int b = 1;
    int i;
    
    afficher_titre("Test Parser - Nettoyage des espaces");
    
    i = nettoyer_espaces("  test", 0);
    printf("nettoyer_espaces \"  test\" = %d  ", i);
    b = RUN_TEST(i == 2) && b;
    ok_test(b);
    
    i = nettoyer_espaces("test", 0);
    printf("nettoyer_espaces \"test\" = %d  ", i);
    b = RUN_TEST(i == 0) && b;
    ok_test(b);
    
    i = nettoyer_espaces(" \t\n\r test", 0);
    printf("nettoyer_espaces \" \\t\\n\\r test\" = %d  ", i);
    b = RUN_TEST(i == 5) && b;
    ok_test(b);
    
    i = nettoyer_espaces("; ceci est un commentaire\ntest", 0);
    printf("nettoyer_espaces \"; commentaire\\ntest\" = %d  ", i);
    b = RUN_TEST(i == 26) && b;
    ok_test(b);
    
    i = nettoyer_espaces("  ; commentaire  \n  test", 0);
    printf("nettoyer_espaces \"  ; commentaire  \\n  test\" = %d  ", i);
    b = RUN_TEST(i == 19) && b;
    ok_test(b);
}

void test_parse_complexe() {
    int b = 1;
    sexpr result;
    int i;
    
    afficher_titre("Test Parser - Expressions complexes");
    initialiser_memoire_dynamique();
    
    i = parseur("(defun fact (n) (if (= n 0) 1 (* n (fact (- n 1)))))", 0, &result);
    printf("parseur \"(defun fact (n) ...)\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(cons_p(result)) && b;
    b = RUN_TEST(symbol_p(car(result))) && b;
    b = RUN_TEST(strcmp(get_symbol(car(result)), "defun") == 0) && b;
    b = RUN_TEST(i == 49) && b;  /* Test position after parsing */
    
    ok_test(b);
    
    i = parseur("(+ 1 2 (* 3 4))", 0, &result);
    printf("parseur \"(+ 1 2 (* 3 4))\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(cons_p(result)) && b;
    b = RUN_TEST(symbol_p(car(result))) && b;
    b = RUN_TEST(strcmp(get_symbol(car(result)), "+") == 0) && b;
    b = RUN_TEST(integer_p(car(cdr(result)))) && b;
    b = RUN_TEST(get_integer(car(cdr(result))) == 1) && b;
    b = RUN_TEST(integer_p(car(cdr(cdr(result))))) && b;
    b = RUN_TEST(get_integer(car(cdr(cdr(result)))) == 2) && b;
    b = RUN_TEST(cons_p(car(cdr(cdr(cdr(result)))))) && b;
    b = RUN_TEST(i == 15) && b;  /* Test position after parsing */
    
    ok_test(b);
    
    i = parseur("(let ((x 1) (y 2)) (+ x y))", 0, &result);
    printf("parseur \"(let ((x 1) (y 2)) (+ x y))\" = ");
    afficher(result);
    printf("  ");
    
    b = RUN_TEST(cons_p(result)) && b;
    b = RUN_TEST(symbol_p(car(result))) && b;
    b = RUN_TEST(strcmp(get_symbol(car(result)), "let") == 0) && b;
    b = RUN_TEST(i == 28) && b;  /* Test position after parsing */
    
    ok_test(b);
}

void test_parse_erreurs() {
    int b = 1;
    sexpr result;
    int i;
    
    afficher_titre("Test Parser - Erreurs");
    initialiser_memoire_dynamique();
    
    i = parseur(")", 0, &result);
    printf("parseur \")\" = %d  ", i);
    b = RUN_TEST(i == -4) && b;  /* Unexpected closing parenthesis */
    ok_test(b);
    
    i = parseur("(", 0, &result);
    printf("parseur \"(\" = %d  ", i);
    b = RUN_TEST(i == -2) && b;  /* Incomplete input (unclosed list) */
    ok_test(b);
    
    i = parseur("\"test", 0, &result);
    printf("parseur \"\\\"test\" = %d  ", i);
    b = RUN_TEST(i == -2) && b;  /* Incomplete input (unclosed string) */
    ok_test(b);
    
    i = parseur("", 0, &result);
    printf("parseur \"\" = %d  ", i);
    b = RUN_TEST(i == -1) && b;  /* Empty input */
    ok_test(b);
}

void test_parseur() {
    afficher_titre("Tests du Parseur");
    test_parse_entier();
    test_parse_symbole();
    test_parse_chaine();
    test_parse_liste();
    test_parse_quote();
    test_nettoyer_espaces();
    test_parse_complexe();
    test_parse_erreurs();
}