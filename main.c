#include "gen.h"
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
	T.tree_pro = init_tree();
	T.tree_det = init_tree();
	T.tree_pre = init_tree();
	
	int size;
	char** file = read_file("mots.txt", &size);

	for (int i=0; i < size; ++i) edit_tree(T, file[i]);

	int t = 0;
	// char** phrase = generate_non_flechies(T, &t);
	// for(int i=0; i<t; i++){
	// 	printf("%s ", phrase[i]);
	// }
	printf("%s ", find_flechie_tg(search_word(T, "stabilisant", &t)[0], 0, 1));

	free_file(file);
	free_all(T);

	return 0;
}

