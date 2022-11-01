#include "tree.h"
#include "file.h"
#include <string.h>
#include <time.h>


int main(){
	srand(time(NULL));
	trees T;
	T.tree_adj = init_tree();
	T.tree_adv = init_tree();
	T.tree_nom = init_tree();
	T.tree_ver = init_tree();
	
	int size;
	char** file = read_file("dictionnaire_non_accentue.txt", &size);

	for (int i=0; i < size; ++i) edit_tree(T, file[i]);
	int taille = 0;
	int r = rand() % 4;
	// p_node res;
	// switch (r){
	// 	case 0:
	// 		res = random_word(T.tree_nom);
	// 		break;
	// 	case 1:
	// 		res = random_word(T.tree_ver);
	// 		break;
	// 	case 2:
	// 		res = random_word(T.tree_adj);
	// 		break;
	// 	default:
	// 		res = random_word(T.tree_adv);
	// 		break;
	// }
	
	// printf("%s\n", res->tab[0]->baseword);

	int t = 0;
	p_node* res = search_word(T, "stabiliser", &t);
	printf("%d\n", t);

	free_file(file);
	free_all(T);

	return 0;
}

