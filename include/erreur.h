#ifndef VALISP_ERREUR_H
#define VALISP_ERREUR_H

#include "types.h"
#include <setjmp.h>

enum erreurs {
    TYPAGE,            /* Paramètre du mauvais type */
    ARITE,             /* Mauvais nombres de paramètres */
    NOM,               /* Variables non définie */
    MEMOIRE,           /* Plus de mémoire */
    DIVISION_PAR_ZERO, /* Tentative d’invocation de l’infinie */
    SYNTAXE,           /* Parseur : le code écrit n’est pas du Lisp */
    MEMOIRE_PARSEUR,   /* Parseur : la sexpr est trop grosse */
    RUNTIME            /* Vos propres erreurs lancée depuis valisp */
};

const char *get_nom_erreur(enum erreurs type);
void erreur_fatale(char *fichier, int ligne, char *causes);
#define ERREUR_FATALE(CAUSE) erreur_fatale(__FILE__, __LINE__, CAUSE)
void erreur(enum erreurs type, char *fonction, char *explication, sexpr s);
jmp_buf *jump_buffer();
void afficher_erreur();
extern int USE_LONGJMP;

#endif
