#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "types.h"
#include "primitives.h"
#include "prim_ratio.h"
#include "environnement.h"
#include "chargeur.h"
#include "repl.h"
#include "couleurs.h"
#include "lifo.h"

/********************************/
/*                              */
/*  Chargement des primitives   */
/*                              */
/********************************/

void charger_primitives() {
    charger_une_primitive("eval",     eval_valisp);
    charger_une_primitive("apply",    apply_valisp);
    charger_une_primitive("car",      car_valisp);
    charger_une_primitive("cdr",      cdr_valisp);
    charger_une_primitive("cons",     cons_valisp);
    charger_une_primitive("+",        add_valisp);
    charger_une_primitive("-",        sub_valisp);
    charger_une_primitive("*",        produit_valisp);
    charger_une_primitive("/",        div_valisp);
    charger_une_primitive("%",        mod_valisp);
    charger_une_primitive("=",        equal_valisp);
    charger_une_primitive("<",        less_than_valisp);
    charger_une_primitive(">",        sup_than_valisp);
    charger_une_primitive("print",    print_valisp);
    charger_une_primitive("println",  println_valisp);
    charger_une_primitive("type-of",  type_of_valisp);

    charger_une_primitive("ratio",       ratio_valisp);
    charger_une_primitive("numerator",   numerator_valisp);
    charger_une_primitive("denominator", denominator_valisp);

    charger_une_speciale("defvar",  defvar_valisp);
    charger_une_speciale("setq",    setq_valisp);
    charger_une_speciale("quote",   quote_valisp);
    charger_une_speciale("lambda",  lambda_valisp);
    charger_une_speciale("macro",   macro_valisp);
    charger_une_speciale("if",      if_valisp);
}

struct option long_options[] = {
    {"debug", no_argument, 0, 'd'},
    {"help", no_argument, 0, 'h'},
    {"load", required_argument, 0, 'l'},
    {"no-stdlib", no_argument, 0, 'n'},
    {"script", required_argument, 0, 's'},
    { NULL, 0, NULL, 0 }
};

char aide[] = "Usage %s [OPTIONS]\n\
\t-l, --load <fichier> (plus tard)\n\
\t-s, --script <fichier> (plus tard)\n\
\t-n, --no-stdlib (plus tard)\n\
\t-h, --help\n\
\t-d, --debug (plus tard)\n";

int init_valisp(load_stdlib, verbose) {
    if (verbose) {
        afficher_banniere();
        printf("Initialisation mémoire");
    }

    initialiser_memoire();

    if (verbose) {
        printf("%s [OK]\n%s", couleur_vert, couleur_defaut);
        printf("Chargement des primitives");
    }

    charger_primitives();

    if (verbose) {
        printf("%s [OK]\n%s", couleur_vert, couleur_defaut);
    }

    init_pile(environnement_global());

    if (load_stdlib) {
        printf("Chargement de la blibliothèque standard");
        if (lire_fichier("lib/stdlib.val") != 0) {
            printf("%s [KO]\n%s", couleur_rouge, couleur_defaut);
        } else {
            printf("%s [OK]\n%s", couleur_vert, couleur_defaut);
        }
    }

    if (verbose) {
        printf("\n");
    }

    return 0;
}

int valisp_main(int argc, char *argv[]) {
    int c;
    int option_index = 0;
    bool load_stdlib = 1;

    while ((c = getopt_long(argc, argv, "l:s:hn", long_options, &option_index)) != -1) {
        switch (c) {
        case 'h':
            printf(aide, argv[0]);
            exit(EXIT_SUCCESS);
        case 'n':
            load_stdlib = 0;
            break;
        case 'l': {
            FILE *loaded_file = NULL;
            init_valisp(load_stdlib, 1);
            printf("Chargement du fichier %s", optarg);      
            if (ouvrir_fichier(optarg, &loaded_file) == 0) {
                printf("%s [OK]\n%s", couleur_vert, couleur_defaut);
                interpreter_fichier(loaded_file);
                fclose(loaded_file);
            } else {
                printf("%s [KO]\n%s", couleur_rouge, couleur_defaut);
            }
            c = repl();
            printf("À bientôt\n");
            return c; 
        }
        case 's':
            init_valisp(0, 0);
            if (lire_fichier(optarg) != 0) {
                printf("%sLe fichier n'a pas pu être chargé\n%s", couleur_rouge, couleur_defaut);
                return 1;
            } else {
                return 0;
            }
        default: /* '?' */
            fprintf(stderr, aide, argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    init_valisp(load_stdlib, 1);

    c = repl();
    printf("À bientôt\n");

    return c;
}
