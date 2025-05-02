#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "allocateur.h"
#include "memoire.h"
#include "types.h"
#include "parseur.h"
#include "primitives.h"
#include "interpreteur.h"
#include "environnement.h"
#include "erreur.h"
#include "couleurs.h"

#define TAILLE_BUFFER  10000

void afficher_banniere() {
    printf("VAΛISP V.0.0.1\n\n");

    /****************************************/
    /*                                      */
    /*  Ok je me suis un peu fait plaisir   */
    /*                                      */
    /****************************************/

    printf("%s", couleur_vert);
    printf("           %s__%s                    \n", couleur_jaune, couleur_vert);
    printf("           %s\\ \\%s   _             \n", couleur_jaune, couleur_vert);
    printf("__   ____ _ %s\\ \\%s (_)___ _ __    \n", couleur_jaune, couleur_vert);
    printf("\\ \\ / / _` |%s/  \\%s| / __| '_ \\ \n", couleur_jaune, couleur_vert);
    printf(" \\ V / (_| %s/ /\\%s | \\__ \\ |_) |\n", couleur_jaune, couleur_vert);
    printf("  \\_/ \\__,%s/_/  \\%s|_|___/ .__/  \n", couleur_jaune, couleur_vert);
    printf("                      |_|       \n");
    printf("                                 \n");
    printf("%s", couleur_defaut);
}

void repl_env() {
    afficher_env(environnement_global());
}

int repl() {
    char *invite_defaut = "\001\033[1;33m\002va\033[1;32mλ\033[1;33misp>\001\033[1;0m\002 ";
    char *invite = invite_defaut;
    char *ligne;
    char BUFFER_READ[TAILLE_BUFFER];
    int POSITION = 0;
    sexpr val;
    int res;
    jmp_buf *buf = jump_buffer();
    sexpr envg = environnement_global();

    using_history();

    while (1) { /* REPL */
        ligne = readline(invite);

        if (ligne == NULL) break;
        if (ligne[0] == '\0')  continue ;
        if (strcmp(ligne, "@env") == 0) { repl_env() ; continue; }
        if (strcmp(ligne, "@mem") == 0) { valisp_stat_memoire(); continue;}
        if (strcmp(ligne, "@mmem")== 0) { afficher_memoire(); continue;}
        if (strcmp(ligne, "@rm")== 0) { valisp_ramasse_miettes(envg); continue;}
        if (strcmp(ligne, "@exit") == 0) { free(ligne); break; }
        {
        /* code */
        }


        if (!setjmp(*buf)) {

            POSITION = ajout_buffer(BUFFER_READ, POSITION, ligne);

            free(ligne);

            res = valisp_read(BUFFER_READ, &val);		  /* READ */

            /* L’expression n’est pas finie, on refait un tour pour la finir */
            if (res == -2)  {
                invite = "";
                continue;
            }

            supprime_retour_ligne_finale_buffer(BUFFER_READ);
            add_history(BUFFER_READ);
            invite = invite_defaut;
            POSITION=0;

            if (res < 0) {
                printf("%s", couleur_rouge);
                printf("Erreur de syntaxe [%d]\n\n", res);
                printf("%s", couleur_defaut);
                continue;
            }

            if (res > 0) {
                printf("%s", couleur_rouge);
                printf("Pas plus d’une sexpr par ligne\n\n");
                printf("%s", couleur_defaut);
                continue;
            }


            /* On a réussi à lire l’expression, on peut l’évaluer */


            /* Tout ce que valisp affichera sera en bleu*/
            printf("%s", couleur_bleu);
            val = eval(val,environnement_global()); /* EVAL */
            printf("%s", couleur_defaut);

            /* Et la valeur de retour sera en vert */
            printf("%s", couleur_vert);
            afficher(val);                         /* PRINT */
            printf("%s", couleur_defaut);


            /* valisp_ramasse_miettes(envg); */
        } else {
            /* Si on rencontre une « exception » */
            printf("%s", couleur_rouge);
            afficher_erreur();
            printf("%s", couleur_defaut);
        }
        printf("\n");
    }

    return 0;
}
