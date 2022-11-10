#ifndef _HEADER_GEN_
#define _HEADER_GEN_


#include "tree.h"

p_node* gen_phrase_nodes(trees T, int* size);
char* find_flechie_typegenre(p_node pn, int type, int genre);
char* find_flechie_verb(p_node pn, char temps, int genre, int pers);
char* gen_phrase_base(trees T);
char* gen_phrase_flechie(trees T);

#endif 