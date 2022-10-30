#include "tree.h"
#include "file.h"
#include <string.h>


int main(){
	trees T;
	T.tree_adj = init_tree();
	T.tree_adv = init_tree();
	T.tree_nom = init_tree();
	T.tree_ver = init_tree();
	
	int size;
	char** file = read_file("mots.txt", &size);

	for (int i=0; i < size; ++i) edit_tree(T, file[i]);

	int taille = 0;
	p_node* res = search_word(T, "stabiliser", &taille);
	
	printf("%s\n", res[0]->tab[0]->word);

	return 0;
}

