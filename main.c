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

	char search[20];
	int t;
	char* phrase;

	int end = 0;
	do {
		int prompt;
		printf("0) Leave \n1) Generate a complete sentence \n2) Search with flechi words \n3) Other \n");
		scanf("%d", &prompt);
		if (prompt == 0) {
			end = 1;
			break;
		}
		else if (prompt == 1){
			phrase = gen_phrase_flechie(T);
			printf("%s\n", phrase);
			free(phrase);
		}
		else if (prompt == 2) {
			printf("search:\t");
			scanf("%s", search);

			flechi** res_fl = search_flechie(T, search, &t);
			if (res_fl != NULL){
				for (int i=0; i<t; ++i) display_flechie(res_fl[i]);
				free(res_fl);
			}
			else printf("No results found\n");
		}
		else if (prompt == 3){
			printf("0) Back to main menu \n1) Search with base words \n2) Random search into noun tree\n3) Generate a sentence with base words \n");
			scanf("%d", &prompt);
			if (prompt == 1) {
				printf("search:\t");
				scanf("%s", search);
				
				p_node* res_pn = search_word(T, search, &t);
				if (res_pn != NULL){
					for (int i=0; i<t; ++i) display_node(res_pn[i]);
					free(res_pn);
				}
				else printf("No results found\n");
			}
			else if (prompt == 2) display_node(random_word(T.tree_nom));
			else if (prompt == 3){
				phrase = gen_phrase_base(T);
				printf("%s\n", phrase);
				free(phrase);
			}
		}
	} while (end == 0);

	free_file(file);
	free_all(T);

	return 0;
}

