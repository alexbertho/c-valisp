#include <stdio.h>
#include "allocateur.h"
#include "erreur.h"
#include "string.h"
#include "tests.h"
#include "primitives.h"
#include "mes_tests.h"
#include "environement.h"


int main() {
    sexpr env, res, var;
    int a;

    initialiser_memoire();

    env = cons(cons(new_symbol("n"), new_integer(10)),           
                cons(cons(new_symbol("msg"), new_string("hello")),     
                cons(cons(new_symbol("t"), new_symbol("t")), NULL)));  

    afficher(env);
    printf("\n");

    var = new_symbol("msg");

    a = trouver_variable(env,var,&res);
    printf("Trouver variable : %d\n", a);

    a = modifier_variable(env, var, new_string("hello world !"));
    afficher(env);
    printf("\n");


    return 0;
}
