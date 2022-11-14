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

	int end = 1;
	do {	
		int prompt;
		printf("0) Leave \n1) Generate a complete sentence \n2) Search with flechi words \n 3) Other");
		scanf("%d", &prompt);
		switch (prompt) {
			case 0:
				end = 0;
				break;
			case 1:
				char* phrase = gen_phrase_flechie(T);
				printf("%s\n", phrase);
				free(phrase);
				break;
			case 2:
				printf("search:\t");
				scanf("%s", search);

				flechi** res_fl = search_flechie(T, search, &t);
				if (res_fl != NULL){
					for (int i=0; i<t; ++i) display_flechie(res_fl[i]);
					free(res_fl);
				}
				else printf("No results found\n");
				break;
			case 3:
				printf("0) Back to main menu \n1) Search with base words \n2) Random search \n 3) ");
				scanf("%d", &prompt);
				switch (prompt) {
					case 0:
						break;
					case 1:
						printf("search:\t");
						scanf("%s", search);
						
						p_node res_pn = search_word(T, search, &t);
						if (res_pn != NULL){
							for (int i=0; i<t; ++i) display_flechie(res_pn[i]);
							free(res_pn);
						}
						else printf("No results found\n");
						break;
				}
			default:
				break;
		}

	} while (end == 0);

	free_file(file);
	free_all(T);

	return 0;
}

