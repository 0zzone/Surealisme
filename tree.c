#include "tree.h"

void display_carac(char** c){
	for(int i=0; i<SIZE; i++){
		printf("%s ", c[i]);
	}
}

void display_struct(flechie f){
	printf("Mot de base : %s\n", f.baseword);
	printf("Mot fléchi : %s\n", f.word);
	display_carac(f.tab_cara);
}


flechie* get_split(char* line){
	if (line[0] == '\0') return NULL;
	int size = strlen(line);
	char** tab = (char**) malloc(sizeof(char*) * 3);

	for(int p=0; p<3; p++){
		tab[p] = (char*) malloc(sizeof(char));
		tab[p][0] = '\0';
	}

	int change = 0, index = 0;
	for(int i=0; i<size; i++){
		if(line[i] != '\t') {
			index++;
			char* temp = realloc(tab[change], index+1);
			if (temp == NULL) printf("bug l31");
			else tab[change] = temp;
			tab[change][index-1] = line[i];
			tab[change][index] = '\0';

		} else {
			change++;
			index = 0;
		}
	}

	flechie* f = malloc(sizeof(flechie));
	f->word = tab[0];
	f->baseword = tab[1];
	f->tab_cara = get_split_carac(tab[2], &f->n_cara);

	free(tab[2]);
    free(tab);

	return f;


}


char** get_split_carac(char* set_char, int* n_tab){
	if (strlen(set_char) == 0) return NULL;
	char** tab = (char**) malloc(sizeof(char*));
	tab[0] = (char*) malloc(sizeof(char));
	tab[0][0] = '\0';

	int change = 0;
	int index = 0;
	int length = strlen(set_char);
	for(int k=0; k<length; k++){
		if(set_char[k] == ':' || set_char[k] == '+'){
			change++;
			char** temp = (char**) realloc(tab, sizeof(char*) * (change + 1));
			if (temp == NULL) printf("error get_split_carac\n");
			else tab = temp;
			
			tab[change] = (char*) malloc(sizeof(char));
			tab[change][0] = '\0';
			index = 0;
		}
		else {
			index++;
			char* temp = realloc(tab[change], sizeof(char) * (index + 1));
			if (temp == NULL) printf("error get_split_carac\n");
			else tab[change] = temp;
			tab[change][index-1] = set_char[k];
			tab[change][index] = '\0';
		}
	}
	*n_tab = change + 1;
	return tab;

}



node* create_node(char letter) {
	p_node pn = (p_node) malloc(sizeof(node));
	pn->alphabet = (p_node*) malloc(sizeof(p_node) * 26);
	for (int i=0; i<26; ++i) pn->alphabet[i] = NULL;
	pn->letter = letter;
	pn->n_flechies = 0;
	pn->tab = NULL;
	return pn;
}

p_node init_tree() {
	p_node tree = create_node(0);
	return tree;
}

void edit_tree(trees T, char* line) {
	flechie* pf = get_split(line);
	if (pf == NULL) return;

	p_node ptr = NULL;
	if (strcmp(pf->tab_cara[0], "Nom") == 0) ptr = T.tree_nom;
	else if (strcmp(pf->tab_cara[0], "Ver") == 0) ptr = T.tree_ver;
	else if (strcmp(pf->tab_cara[0], "Adj") == 0) ptr = T.tree_adj;
	else ptr = T.tree_adv;

	int size = strlen(pf->baseword);
	for (int i = 0; i < size; i++) {
		int index = pf->baseword[i] - 'a';
		if (ptr->alphabet[index] == NULL) ptr->alphabet[index] = create_node(pf->baseword[i]);
		ptr = ptr->alphabet[index];
	}
	ptr->n_flechies++;
	flechie** temp = (flechie**) realloc(ptr->tab, ptr->n_flechies * sizeof(flechie*));
	if (temp == NULL) printf("error l146");
	else ptr->tab = temp;
	
	ptr->tab[ptr->n_flechies - 1] = pf;
}

p_node* search_word(trees T, char* search, int* size) {
	int length = strlen(search);
	*size = 0;
	p_node* tab_t = (p_node*) malloc(sizeof(p_node) * 4);

	tab_t[0] = T.tree_adj;
	tab_t[1] = T.tree_nom; 
	tab_t[2] = T.tree_ver; 
	tab_t[3] = T.tree_adv;

	p_node* res = NULL;
	p_node ptr;
	for (int i_tree=0; i_tree<4; i_tree++) {
		int found = 1;
		ptr = tab_t[i_tree];
		for (int depth=0; depth<length; depth++) {
			ptr = ptr->alphabet[search[depth] - 'a'];
			if (ptr == NULL) {
				found = 0;
				break;
			}
		}
		if (found == 1) {
			(*size)++;
			if(res == NULL) res = (p_node*) malloc(sizeof(p_node));
			else res = realloc(res, *size);
			res[*size - 1] = ptr;
		}
	}

	free(tab_t);

	return res;
}
