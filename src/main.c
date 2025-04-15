#include <stdio.h>

#include "allocateur.h"
#include "erreur.h"
#include "string.h"
#include "tests.h"
#include "primitives.h"
#include "mes_tests.h"
#include "environnement.h"
#include "memoire.h"

/*
int main() {
    sexpr env, env2;

    initialiser_memoire();

    env = cons(cons(new_symbol("n"), new_integer(10)),           
                cons(cons(new_symbol("msg"), new_string("hello")),     
                cons(cons(new_symbol("t"), new_symbol("t")), NULL)));
    
    env2 = cons(cons(new_symbol("n"), new_integer(10)),           
                cons(cons(new_symbol("ttt"), new_string("hello")),     
                cons(cons(new_symbol("t"), new_symbol("t")), NULL)));  
    

    printf("========== AVANT RM ========\n");
    printf("ENV 1 = ");
    afficher(env);
    printf("\n");
    printf("ENV 2 = ");
    afficher(env2);
    printf("\n");
    printf("valisp_ramasse_miettes \n");
    
    valisp_ramasse_miettes(env);
    
    printf("\n");
    printf("========== APRES RM ========\n");
    printf("ENV 1 = ");
    afficher(env);
    printf("\n");
    printf("ENV 2 = ");
    afficher(env2);
    printf("\n");

    
    return 0;
}
*/

int main(int argc, char *argv[]) {
    


    return valisp_main(argc, argv);
}
