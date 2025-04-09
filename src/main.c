#include <stdio.h>
#include "allocateur.h"
#include "erreur.h"
#include "string.h"
#include "tests.h"
#include "primitives.h"
#include "mes_tests.h"


int main() {
    sexpr a,b,c,liste;

    initialiser_memoire_dynamique();
    
    a = new_integer(5);
    b = new_integer(3);
    c = new_integer(2);
    liste = cons(a, cons(b, cons(c, NULL)));
    
    afficher(add_valisp(liste, NULL));

    printf("\n");
    
    return 0;
}
