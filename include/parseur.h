#ifndef PARSEUR_H
#define PARSEUR_H

#include "types.h"

int nettoyer_espaces(char *texte, int i);
int parseur(char *texte, int i, sexpr *res);
int valisp_read(char *texte, sexpr *res);

int ajout_buffer(char *buffer, int position, char *chaine);
void supprime_retour_ligne_finale_buffer(char *buffer);
void reinitialiser_buffer_parseur();
int ajouter_ligne_buffer_parseur(char *ligne);
int parser_et_evaluer_buffer(sexpr *resultat);
char* obtenir_buffer_parseur(); 

#endif
