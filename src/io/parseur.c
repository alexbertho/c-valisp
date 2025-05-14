#include <stddef.h>
#include <stdlib.h>

#include "parseur.h"
#include "types.h"
#include "memoire.h"

#define TAILLE_BUFFER 10000

static char BUFFER_PARSEUR[TAILLE_BUFFER];
static int POSITION_PARSEUR = 0;

int est_espace(char c) {
    return (c == ' ' || c == '\t' || c == '\n') || 
           (c == '\r' || c == '\f' || c == '\v');
}

int est_chiffre(char c) {
    return (c >= '0' && c <= '9');
}

int est_symbole(char c) {
    if (c == '\0' || c == '(' || c == ')' || c == '\'' || c == ';' || est_espace(c)) {
        return 0;
    }
    return 1;
}

int fin_mot(char c) {
    return (est_espace(c) || c == ')' || c == ';');
}

int longueur_chaine(char *texte, int deb, int fin) {
    int i, count = 0;
    
    for (i = deb; i < fin; i++) {
        if (texte[i] == '\\' && i + 1 < fin) {
            i++;
        }
        count++;
    }
    
    return count;
}

char *sous_chaine(char *texte, int deb, int fin) {
    int i, j = 0;
    int len = longueur_chaine(texte, deb, fin);
    char *result = (char *)valisp_malloc(len + 1);
    
    for (i = deb; i < fin; i++) {
        if (texte[i] == '\\' && i + 1 < fin) {
            i++;
            switch (texte[i]) {
                case 'n': result[j++] = '\n'; break;
                case 't': result[j++] = '\t'; break;
                case '\\': result[j++] = '\\'; break;
                default: result[j++] = texte[i]; break;
            }
        } else {
            result[j++] = texte[i];
        }
    }
    
    result[j] = '\0'; 
    return result;
}

int nettoyer_espaces(char *texte, int i) {
    while (texte[i] != '\0') {
        if (est_espace(texte[i])) {
            i++;
        } else if (texte[i] == ';') {
            for(; texte[i] != '\0' && texte[i] != '\n'; i++);
        } else {
            break;
        }
    }
    
    return i;
}

int parse_chaine(char *texte, int i, sexpr *res) {
    int deb;
    
    if (texte[i] != '"') {
        return -3; 
    }
    
    deb = i + 1; 
    i++;
    
    while (texte[i] != '\0') {
        if (texte[i] == '\\') {
            i += 2;
            if (texte[i-1] == '\0') {
                return -2; 
            }
        } else if (texte[i] == '"') {
            break; 
        } else {
            i++;
        }
    }
    
    if (texte[i] == '\0') {
        return -2;
    }
    
    *res = new_string(sous_chaine(texte, deb, i));
    return i + 1;
}

int parse_ratio(char *texte, int start, sexpr *res) {
    int i = start;
    int sign = 1;
    valisp_integer_t numerateur = 0;
    valisp_integer_t denominateur = 0;
    
    if (texte[i] == '-') {
        sign = -1;
        i++;
    } else if (texte[i] == '+') {
        i++;
    }
    
    while (est_chiffre(texte[i])) {
        numerateur = numerateur * 10 + (texte[i] - '0');
        i++;
    }
    
    if (texte[i] != '/') {
        return -3;
    }
    
    i++;
    
    if (!est_chiffre(texte[i])) {
        return -3;
    }
    
    while (est_chiffre(texte[i])) {
        denominateur = denominateur * 10 + (texte[i] - '0');
        i++;
    }
    
    if (!fin_mot(texte[i]) && texte[i] != '\0' && texte[i] != ')') {
        *res = new_symbol(sous_chaine(texte, start, i));
        return i;
    }
    
    *res = new_ratio(sign * numerateur, denominateur);
    
    return i;
}

int parse_entier(char *texte, int i, sexpr *res) {
    int sign = 1;
    int value = 0;
    int start = i;
    int j;
    
    if (texte[i] == '-') {
        sign = -1;
        i++;
    } else if (texte[i] == '+') {
        i++;
    }
    
    if (!est_chiffre(texte[i])) {
        return -3; 
    }
    
    for (j = i; texte[j] != '\0' && !fin_mot(texte[j]) && texte[j] != ')'; j++) {
        if (texte[j] == '/') {
            return parse_ratio(texte, start, res);
        }
    }
    
    while (est_chiffre(texte[i])) {
        value = value * 10 + (texte[i] - '0');
        i++;
    }
    
    if (!fin_mot(texte[i]) && texte[i] != '\0' && texte[i] != ')') {
        while (!fin_mot(texte[i]) && texte[i] != '\0' && texte[i] != ')') {
            i++;
        }
        *res = new_symbol(sous_chaine(texte, start, i));
    } else {
        *res = new_integer(sign * value);
    }
    
    return i;
}

int parse_symbole(char *texte, int i, sexpr *res) {
    int deb = i;
    
    if (!est_symbole(texte[i])) {
        return -3; 
    }
    
    while (!fin_mot(texte[i]) && texte[i] != '\0' && texte[i] != ')') {
        i++;
    }
    
    *res = new_symbol(sous_chaine(texte, deb, i));
    return i;
}

int parse_liste(char *texte, int i, sexpr *res) {
    sexpr e = NULL;
    sexpr tete = NULL, queue = NULL;
    
    i = nettoyer_espaces(texte, i);
    
    if (texte[i] == ')') {
        *res = NULL;
        return i + 1;
    }
    
    while (texte[i] != ')') {
        if (texte[i] == '\0') {
            return -2; 
        }
        
        i = parseur(texte, i, &e);
        if (i < 0) {
            return i; 
        }
        
        if (tete == NULL) {
            tete = cons(e, NULL);
            queue = tete;
        } else {
            set_cdr(queue, cons(e, NULL));
            queue = cdr(queue);
        }
        
        i = nettoyer_espaces(texte, i);
        if (texte[i] == '\0') {
            return -2; 
        }
    }
    
    *res = tete;
    return i + 1; 
}

int parseur(char *texte, int i, sexpr *res) {
    sexpr e = NULL;
    i = nettoyer_espaces(texte, i);
    
    if (texte[i] == '\0') {
        return -1; 
    }
    if (texte[i] == '(') {
        i++; 
        return parse_liste(texte, i, res);
    } 
    else if (texte[i] == '\'') {
        i++;
        i = parseur(texte, i, &e);
        if (i < 0) {
            return i; 
        }
        *res = cons(new_symbol("quote"), cons(e, NULL));
        return i;
    } 
    else if (texte[i] == '"') {
        return parse_chaine(texte, i, res);
    } 
    else if (est_chiffre(texte[i]) || (texte[i] == '-' && texte[i+1] != '\0' && est_chiffre(texte[i+1]))) {
        return parse_entier(texte, i, res);
    } 
    else if (est_symbole(texte[i])) {
        return parse_symbole(texte, i, res);
    } 
    else if (texte[i] == ')') {
        return -4;
    } 
    else {
        return -3; 
    }
}

int valisp_read(char *texte, sexpr *res) {
    int i;
    *res = NULL;

    i = nettoyer_espaces(texte, 0);
    
    if (texte[i] == '\0') {
        return -1;
    }

    i = parseur(texte, 0, res);
    i = nettoyer_espaces(texte,i);

    if (i>0 && texte[i] == '\0') return 0;

    return i;
}

void reinitialiser_buffer_parseur() {
    POSITION_PARSEUR = 0;
    BUFFER_PARSEUR[0] = '\0';
}

int ajout_buffer(char *buffer, int position, char *chaine) {
    int i;
    for (i=0; chaine[i] != '\0'; i++) {
        buffer[position+i] = chaine[i];
    }
    buffer[position+i] = '\n';
    buffer[position+i+1] = '\0';
    return position+i+1;
}

void supprime_retour_ligne_finale_buffer(char *buffer) {
    int i;
    for (i=0; buffer[i] != '\0'; i++);
    if (buffer[i-1] == '\n') buffer[i-1] = '\0';
}

int ajouter_ligne_buffer_parseur(char *ligne) {
    POSITION_PARSEUR = ajout_buffer(BUFFER_PARSEUR, POSITION_PARSEUR, ligne);
    return POSITION_PARSEUR;
}

int parser_et_evaluer_buffer(sexpr *resultat) {
    int res;
    
    res = valisp_read(BUFFER_PARSEUR, resultat);
    
    if (res == -2) {
        return -2;
    }
    
    supprime_retour_ligne_finale_buffer(BUFFER_PARSEUR);
    
    return res;
}

char* obtenir_buffer_parseur() {
    return BUFFER_PARSEUR;
}
