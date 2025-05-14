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
#include "erreur.h"

#define TAILLE_BUFFER 10000

/**
 * Ouvre un fichier et vérifie qu'il est valide
 * 
 * @param nom_fichier Le chemin du fichier à ouvrir
 * @param fichier_ptr Pointeur qui recevra le descripteur de fichier
 * @return 0 en cas de succès, 1 en cas d'erreur
 */
int ouvrir_fichier(char* nom_fichier, FILE** fichier_ptr) {
    FILE* fichier = fopen(nom_fichier, "r");
    
    if (fichier == NULL) {
        printf("%sErreur: Impossible d'ouvrir le fichier '%s'%s\n", 
               couleur_rouge, nom_fichier, couleur_defaut);
        return 1;
    }
    
    *fichier_ptr = fichier;
    return 0;
}

/**
 * Interprète et évalue le contenu du fichier
 * 
 * @param fichier Le descripteur de fichier à traiter
 * @return 0 en cas de succès, code d'erreur sinon
 */
int interpreter_fichier(FILE* fichier) {
    char ligne[256];
    sexpr val;
    int res;
    char BUFFER_READ[TAILLE_BUFFER];
    int POSITION = 0;

    int old_use_longjmp = USE_LONGJMP;
    USE_LONGJMP = 0;

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

        if (res < -1) {
            printf("%s", ligne);
            printf("%sErreur de syntaxe [%d]%s\n", couleur_rouge, res, couleur_defaut);
            return -1;
        }

        if (res > 0) {
            printf("%sErreur: Pas plus d’une sexpr par ligne%s\n", couleur_rouge, couleur_defaut);
            return -1;
        }

        printf("%s", couleur_bleu);
        val = eval(val, environnement_global()); /* EVAL */
        printf("%s", couleur_defaut);
    }

    USE_LONGJMP = old_use_longjmp;
    
    return 0;
}

/**
 * Lit et interprète un fichier Valisp
 * 
 * @param nom_fichier Le nom du fichier à ouvrir et interpréter
 * @return 0 en cas de succès, code d'erreur sinon
 */
int lire_fichier(char* nom_fichier) {
    FILE* fichier = NULL;
    int status;
    
    status = ouvrir_fichier(nom_fichier, &fichier);
    if (status != 0) {
        return 1;
    }
    
    status = interpreter_fichier(fichier);
    
    return status;
}