#include "main.h"
#include "file.h"
#include <string.h>

#define SIZE 10

#define SIZE 10

int main(){
	trees T;
	T.tree_adj = init_tree();
	T.tree_adv = init_tree();
	T.tree_nom = init_tree();
	T.tree_ver = init_tree();
	
	int size;
	char* baseword;
	char** file = read_file("mots.txt", &size);


	for (int i=0; i < size; ++i) {
		edit_tree(T, file[i]);
	}
	
	// char mot[12] = "stabilimetre";
	// p_node ptr = T.tree_nom;
	// for(int i=0; i<12; i++){
	// 	printf("%c", ptr->alphabet[mot[i] - 'a']->letter);
	// 	ptr = ptr->alphabet[mot[i] - 'a'];
	// }

	int taille = 0;
	p_node* res = search_word(T, "stabilisant", &taille);
	
	for(int k=0; k<taille; k++){
		for(int p=0; p<res[k]->number; p++){
			printf("%s\n", res[k]->tab[p]->baseword);
		}
	}

	return 0;
}

void display_carac(char** c){
	for(int i=0; i<SIZE; i++){
		printf("%s ", c[i]);
	}
}

void display_struct(flechie f){
	printf("Mot de base : %s\n", f.baseword);
	printf("Mot fléchi : %s\n", f.word);
	display_carac(f.cara);
}


void display_file(char** file, int size){
	for(int i=0; i<size; i++){
		printf("%s\n", file[i]);
	}
}


flechie get_split(char* line){
	int size = strlen(line);
	char** tab = (char**) malloc(sizeof(char*) * 3);

	for(int p=0; p<3; p++){
		tab[p] = NULL;
	}

	int change = 0;
	int index = 0;
	for(int i=0; i<size; i++){
		if(line[i] != '\t'){
			if(tab[change] == NULL){
				tab[change] = (char*) malloc(sizeof(char));
			}
			else{
				tab[change] = realloc(tab[change], index+1);
			}
			tab[change][index] = line[i];
			index++;
		}
		else{
			change++;
			index = 0;
		}
	}

	flechie f;
	f.word = tab[0];
	f.baseword = tab[1];
	f.cara = get_split_carac(tab[2]);

	return f;


}


char** get_split_carac(char* ensemble){
	char** tab = (char**) malloc(sizeof(char*) * SIZE);
	for(int i=0; i<SIZE; i++){
		tab[i] = (char*) malloc(sizeof(char) * 5);
	}

	int change = 0;
	int index = 0;
	for(int k=0; k<strlen(ensemble); k++){
		if(ensemble[k] == ':' || ensemble[k] == '+'){
			change++;
			index = 0;
		}
		else{
			tab[change][index] = ensemble[k];
					index++;
		}
	}
	return tab;

}



node* create_node(char letter) {
	p_node pn = (p_node) malloc(sizeof(node));
	pn->alphabet = (p_node*) malloc(sizeof(p_node) * 26);
	for (int i=0; i<26; ++i) pn->alphabet[i] = NULL;
	pn->letter = letter;
	pn->number = 0;
	pn->tab = NULL;
	return pn;
}

p_node init_tree() {
	p_node tree = create_node(0);
	return tree;
}

void edit_tree(trees T, char* line) {
	flechie f = get_split(line);

	p_node tree = NULL;
	if (strcmp(f.cara[0],"Nom") == 0) tree = T.tree_nom;
	else if (strcmp(f.cara[0],"Ver")==0) tree = T.tree_ver;
	else if (strcmp(f.cara[0],"Adj")==0) tree = T.tree_adj;
	else tree = T.tree_adv;

	char* word = f.baseword;
	int size = strlen(word);
	p_node ptr = tree;
	for (int i = 0; i < size; i++) {
		int index = word[i] - 'a';
		if (ptr->alphabet[index] == NULL) {
			ptr->alphabet[index] = create_node(word[i]);
		}
		ptr = ptr->alphabet[index];
	}
	ptr->number++;
	ptr->tab = realloc(ptr->tab, ptr->number);
	ptr->tab[ptr->number - 1] = &f;
}

p_node* search_word(trees T, char* search, int* size) {
	*size = 0;
	p_node tab_t[4];
	tab_t[0] = T.tree_adj, 
	tab_t[1] = T.tree_nom, 
	tab_t[2] = T.tree_ver, 
	tab_t[3] = T.tree_adv;

	p_node* res = NULL;
	p_node ptr;
	int found;
	for (int i_tree=0; i_tree<4; i_tree++) {
		found = 1;
		ptr = tab_t[i_tree];
		for (int depth=0; depth<strlen(search); depth++) {
			ptr = ptr->alphabet[search[depth] - 'a'];
			if (ptr == NULL) {
				found = 0;
				break;
			}
		}
		if(found == 1){
			(*size)++;
			if(res == NULL){
				res = (p_node*) malloc(sizeof(p_node) * (*size));
			}
			else{
				res = realloc(res, *size);
			}
			res[*size - 1] = ptr;
		}
	}

	return res;
}
















