#ifndef LOAD_FILE_H
#define LOAD_FILE_H

#include <stdio.h>

int ouvrir_fichier(char* nom_fichier, FILE** fichier_ptr);
int interpreter_fichier(FILE* fichier);
int lire_fichier(char *nom_fichier);

#endif