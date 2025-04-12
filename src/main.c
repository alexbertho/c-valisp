#include <stdio.h>

#include "allocateur.h"
#include "erreur.h"
#include "string.h"
#include "tests.h"
#include "primitives.h"
#include "mes_tests.h"
#include "environnement.h"
#include "memoire.h"

int main() {
    sexpr env;

    initialiser_memoire();

    env = cons(cons(new_symbol("n"), new_integer(10)),           
                cons(cons(new_symbol("msg"), new_string("hello")),     
                cons(cons(new_symbol("t"), new_symbol("t")), NULL)));  

    afficher_env(env);
    afficher(env);
    printf("\n");
    valisp_stat_memoire();
    printf("Longeur de l'env %d \n", longeur_env(env));
    printf("valisp_ramasse_miettes \n");
    valisp_ramasse_miettes(env);

    printf("\n");
    printf("========== APRES RM ========\n");
    afficher(env);
    printf("\n");

    
    return 0;
}
