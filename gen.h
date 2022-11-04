#ifndef _HEADER_GEN_
#define _HEADER_GEN_


#include "tree.h"

p_node* generate_nodes(trees T, int* size);
char* find_flechie_tg(p_node pn, int type, int genre);
char* generate_base(trees T);
char* generate_flechie(trees T);

#endif 