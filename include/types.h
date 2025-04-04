typedef unsigned char bool; 
struct valisp_object;
typedef struct valisp_object *sexpr;

#ifndef TYPES_H 
#define TYPES_H

sexpr new_integer(int i);
bool integer_p(sexpr val);
int get_integer(sexpr val);

char* chaine_vers_memoire(const char *c);
sexpr new_string(char * c);
sexpr new_symbol(char * c);
char* get_symbol(sexpr val);
char* get_string(sexpr val);
bool string_p(sexpr val);
bool symbol_p(sexpr val);
bool symbol_match_p(sexpr val, const char *chaine);

sexpr cons(sexpr e1, sexpr e2);
bool cons_p (sexpr e);
bool list_p(sexpr e);
sexpr car(sexpr e);
sexpr cdr(sexpr e);
void set_car(sexpr e, sexpr nouvelle);
void set_cdr(sexpr e, sexpr nouvelle);
void afficher_liste(sexpr e);

void afficher(sexpr val);



#endif



