#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "couleurs.h"
#include "erreur.h"


/**********************/
/*                    */
/*  Erreurs Fatales   */
/*                    */
/**********************/

/* Pour s’arrêter lorsque le développeur tombe sur cas qui ne devrait
   jamais arriver. Normalement, si le programme est écrit sans bugs,
   les erreurs fatales ne devrait jamais être rencontrées. */


enum erreurs TYPE_ERREUR;
char * MESSAGE_ERREUR;
char * FONCTION_ERREUR;
sexpr SEXPR_ERREUR;

const char* get_nom_erreur(enum erreurs type) {
    switch(type) {
        case TYPAGE: return "TYPAGE";
        case ARITE: return "ARITE";
        case NOM: return "NOM";
        case MEMOIRE: return "MEMOIRE";
        case DIVISION_PAR_ZERO: return "DIVISION_PAR_ZERO";
        case SYNTAXE: return "SYNTAXE";
        case MEMOIRE_PARSEUR: return "MEMOIRE_PARSEUR";
        case RUNTIME: return "RUNTIME";
        default: return "ERREUR_INCONNUE";
    }
}

void afficher_erreur() {
    printf("%s", couleur_rouge);
    printf("Erreur d’exécution [%s] : %s\n", get_nom_erreur(TYPE_ERREUR), MESSAGE_ERREUR);
    printf("Fonction fautive : « %s »\n", FONCTION_ERREUR);
    printf("Valeur fautive : «\"");
    afficher(SEXPR_ERREUR);
    printf("\"»\n");
    printf("%s", couleur_defaut);
}

void erreur(enum erreurs type, char* fonction, char * explication, sexpr s) {
    TYPE_ERREUR = type;
    MESSAGE_ERREUR = explication;
    FONCTION_ERREUR = fonction;
    SEXPR_ERREUR = s;
    afficher_erreur();
    exit(1);
}

void erreur_fatale(char  *fichier, int ligne, char* causes) {
    fprintf(stderr,"%s", couleur_rouge);
    fprintf(stderr,"\n   /!\\ Erreur fatale /!\\");
    fprintf(stderr,"%s", couleur_defaut);
    fprintf(stderr,"   %s ligne %d\n\n", fichier, ligne);
    fprintf(stderr,"%s\n", causes);
    exit(1);
}
