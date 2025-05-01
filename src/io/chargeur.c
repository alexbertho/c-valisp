#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "environnement.h"
#include "interpreteur.h"
#include "parseur.h"
#include "couleurs.h"
#include "primitives.h"
#include "valisp.h"


#define TAILLE_BUFFER  10000


int lire_fichier(char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    char ligne[256];
    sexpr val;
    int res;
    char BUFFER_READ[TAILLE_BUFFER];
    int POSITION = 0;
    
    if (fichier == NULL) {
        return 1;
    }

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        POSITION = ajout_buffer(BUFFER_READ, POSITION, ligne);

        res = valisp_read(BUFFER_READ, &val);

        if (res == -2) {
            continue;
        }

        supprime_retour_ligne_finale_buffer(BUFFER_READ);
        POSITION = 0;

        /* Tout ce que valisp affichera sera en bleu*/
        printf("%s", couleur_bleu);
        val = eval(val,environnement_global()); /* EVAL */
        printf("%s", couleur_defaut);
    }
    fclose(fichier);
    return 0;
}
