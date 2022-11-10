#include "gen.h"
#include "file.h"
#include <string.h>
#include <time.h>


int main(){
	srand(time(NULL));
	trees T = init_trees();
	
	int size;
	char** file = read_file("dictionnaire_non_accentue.txt", &size);
	for (int i=0; i < size; ++i) edit_tree(T, file[i]);

	char* phrase = gen_phrase_flechie(T);
	printf("%s\n", phrase);
	int t = -1;

	flechi** res = search_flechie(T, "belle", &t);
	if (res != NULL){
		for (int i=0; i<t; ++i) display_flechie(res[i]);
		free(res);
	}
	free(phrase);
	free_file(file);
	free_all(T);

	return 0;
}

