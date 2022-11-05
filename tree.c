#include "tree.h"

void free_tree(p_node tree) {
	if (tree == NULL) return;
	if (tree->alphabet != NULL) {
		for (int i=0; i<28; ++i) if (tree->alphabet[i] != NULL) free_tree(tree->alphabet[i]);
		free(tree->alphabet);
	}
	for (int flechi=0; flechi<tree->n_flechies; ++flechi) {
		flechie* temp = tree->tab[flechi];
		free(temp->baseword);
		free(temp->word);
		if (temp->tab_cara != NULL){
			for (int cara=0; cara < temp->n_cara; ++cara) free(temp->tab_cara[cara]);
			free(temp->tab_cara);
		}
		free(temp);
	}
	free(tree->tab);
	free(tree);
	tree = NULL;
}

void free_all(trees T) {
	p_node* tab_t = (p_node*) malloc(sizeof(p_node) * 4);
	tab_t[0] = T.tree_adj;
	tab_t[1] = T.tree_nom; 
	tab_t[2] = T.tree_ver; 
	tab_t[3] = T.tree_adv;

	for (int i=0; i<4; ++i) free_tree(tab_t[i]);
	free(tab_t);
}

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

p_node sample_tree() {
	p_node stree = create_node(0);
	stree->alphabet[0] = create_node('a');
	p_node temp = stree->alphabet[0];
	temp->n_flechies = 1;
	temp->tab = malloc(sizeof(flechie*));
	temp->tab[0]->word = malloc(sizeof(char) * 5);
	temp->tab[0]->word = "aaab";
	temp->tab[0]->baseword = malloc(sizeof(char) * 3);
	temp->tab[0]->baseword = "aa";
	temp->tab[0]->tab_cara = malloc(sizeof(char*) * 4);
	temp->tab[0]->tab_cara = get_split_carac("Ver:aaaa:b:cc", &temp->tab[0]->n_cara);

	temp->alphabet[0] = create_node('a');
	temp = temp->alphabet[0];
	temp->n_flechies = 2;
	temp->tab = malloc(sizeof(flechie*) * 2);
	temp->tab[0]->word = malloc(sizeof(char) * 5);
	temp->tab[0]->word = "aaab";
	temp->tab[0]->baseword = malloc(sizeof(char) * 3);
	temp->tab[0]->baseword = "aa";
	temp->tab[0]->tab_cara = malloc(sizeof(char*) * 4);
	temp->tab[0]->tab_cara = get_split_carac("Ver:aaaa:b:cc", &temp->tab[0]->n_cara);
	temp->tab[1]->word = malloc(sizeof(char) * 3);
	temp->tab[1]->word = "ab";
	temp->tab[1]->baseword = malloc(sizeof(char) * 6);
	temp->tab[1]->baseword = "aabbc";
	temp->tab[1]->tab_cara = malloc(sizeof(char*) * 3);
	temp->tab[1]->tab_cara = get_split_carac("Nom:b:cc", &temp->tab[1]->n_cara);

	return stree;
}

flechie* get_split(char* line){
	if (line == NULL || line[0] == '\n') return NULL;
	int size = strlen(line);
	char** tab = (char**) malloc(sizeof(char*) * 3);

	for(int p=0; p<3; p++){
		tab[p] = (char*) malloc(sizeof(char));
		tab[p][0] = '\0';
	}

	int change = 0, index = 0;
	for(int i=0; i<size; i++){
		if(line[i] != '\t') {
			index++; // including the last null char
			char* temp = realloc(tab[change], index+1);
			if (temp == NULL) printf("bug get_split");
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
	pn->alphabet = (p_node*) malloc(sizeof(p_node) * 28);
	for (int i=0; i<28; ++i) pn->alphabet[i] = NULL;
	pn->letter = letter;
	pn->n_flechies = 0;
	pn->tab = NULL;
	return pn;
}

p_node init_tree() {
	p_node tree = create_node(0);
	return tree;
}

int get_index(char prompt) {
	if (prompt == '-') return 26;
	if (prompt == '\'') return 27;
	/*
	if (prompt == '\351' || prompt == '\350' || prompt == '\352' || prompt == '\353') return 'e' - 'a';
	if (prompt == '\340') return 0;
	if (prompt == '\371') return 'u' - 'a';
	if (prompt == '\366') return 'o' - 'a';
	if (prompt == '\357') return 'i' - 'a';
	*/
	return prompt - 'a';
}

void edit_tree(trees T, char* line) {
	flechie* pf = get_split(line);
	if (pf == NULL) return;

	p_node ptr = NULL;
	if (strcmp(pf->tab_cara[0], "Nom") == 0) ptr = T.tree_nom;
	else if (strcmp(pf->tab_cara[0], "Ver") == 0) ptr = T.tree_ver;
	else if (strcmp(pf->tab_cara[0], "Adj") == 0) ptr = T.tree_adj;
	else if (strcmp(pf->tab_cara[0], "Adv") == 0) ptr = T.tree_adv;
	else if (strcmp(pf->tab_cara[0], "Pro") == 0) ptr = T.tree_pro;
	else if (strcmp(pf->tab_cara[0], "Det") == 0) ptr = T.tree_det;
	else if (strcmp(pf->tab_cara[0], "Pre") == 0) ptr = T.tree_pre;
	else if (strcmp(pf->tab_cara[0], "Int") == 0) ptr = T.tree_int;
	else if (strcmp(pf->tab_cara[0], "Con") == 0) ptr = T.tree_con;
	else if (strcmp(pf->tab_cara[0], "QPro") == 0) ptr = T.tree_qpro;
	else {
		// if (strcmp(pf->tab_cara[0], "Abr") == 0) return;
		// if (strcmp(pf->tab_cara[0], "Conj") == 0) return;
		return;
	}

	int size = strlen(pf->baseword);
	for (int i = 0; i < size; i++) {
		int index = get_index(pf->baseword[i]);
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
	int temp_size = 0;
	int length = strlen(search);
	p_node* tab_t = (p_node*) malloc(sizeof(p_node) * NB_TREES);

	tab_t[0] = T.tree_adj;
	tab_t[1] = T.tree_nom;
	tab_t[2] = T.tree_ver;
	tab_t[3] = T.tree_adv;
	tab_t[4] = T.tree_pro;
	tab_t[5] = T.tree_pre;
	tab_t[6] = T.tree_det;
	tab_t[7] = T.tree_int;
	tab_t[8] = T.tree_con;
	tab_t[9] = T.tree_qpro;

	p_node* res = NULL;
	p_node ptr;
	for (int i_tree=0; i_tree<NB_TREES; i_tree++) {
		int found = 1;
		ptr = tab_t[i_tree];
		for (int depth=0; depth<length; depth++) {
			ptr = ptr->alphabet[get_index(search[depth])];
			if (ptr == NULL) {
				found = 0;
				break;
			}
		}
		if (ptr != NULL && ptr->n_flechies == 0) found = 0;
		if (found == 1) {
			(temp_size)++;
			if(res == NULL) res = (p_node*) malloc(sizeof(p_node));
			else res = realloc(res, temp_size * sizeof(p_node));
			res[temp_size - 1] = ptr;
		}
	}

	free(tab_t);
	if (size != NULL) *size = temp_size;

	return res;
}

int is_alphabet_empty(p_node* alphabet) {
	for (int i=0; i<28; ++i) {
		if (alphabet[i] != NULL) return 0;
	}
	return 1;
}

p_node random_word(tree t) {
	if (t == NULL || is_alphabet_empty(t->alphabet) == 1) {
		printf("cannot find a random word in empty tree\n");
		return NULL;
		}

	p_node temp = t;
	int a = 0, r = 0, found = 0;
	while (found == 0) {
		r = rand() % 28;
		while (temp->alphabet[r] == NULL) r = rand() % 28;
		temp = temp->alphabet[r];
		if (temp->n_flechies > 0) {
			a = rand() % 2;
			if (a > 0 || (a == 0 && is_alphabet_empty(temp->alphabet) == 1)) found = 1;
		}
	}

	return temp;
}

void display_flechie(flechie* fl) {
	if (fl == NULL) return;

	int s_cara = fl->n_cara;
	if (strcmp(fl->tab_cara[0], "Ver") == 0){
		if ((int) s_cara / 3 == 0) printf("%s : %s %s, temps %s\n", fl->word, fl->baseword, fl->tab_cara[0], fl->tab_cara[1]);
		else for (int i_cara=0; i_cara < (int) s_cara / 3; i_cara++){
			printf("%s : %s %s, temps %s, %s %s\n", 
				fl->word, 
				fl->tab_cara[0],
				fl->baseword, 
				fl->tab_cara[(i_cara * 3) + 1], 
				fl->tab_cara[(i_cara * 3 + 2) + 1], 
				fl->tab_cara[(i_cara * 3 + 1) + 1]
			);
		}
	}
	else if (strcmp(fl->tab_cara[0], "Adj") == 0 || strcmp(fl->tab_cara[0], "Nom") == 0 || strcmp(fl->tab_cara[0], "Det") == 0) {
		for (int i_cara=0; i_cara < (int) s_cara / 2; i_cara++){
			printf("%s : %s %s, %s %s\n", 
				fl->word, 
				fl->tab_cara[0],
				fl->baseword, 
				fl->tab_cara[(i_cara * 2) + 1], 
				fl->tab_cara[(i_cara * 2 + 1) + 1]
			);
		}
	}
	else printf("%s : %s %s\n", 
			fl->word,
			fl->tab_cara[0],
			fl->baseword
		);
}



p_node verif_flechies(p_node pn, char* search, int* i_cara) {
	if (pn == NULL || pn->n_flechies == 0) return NULL;
	for (int ind=0; ind < pn->n_flechies; ++ind) {
		if (strcmp(search, pn->tab[ind]->word) == 0) {
			*i_cara = ind;
			return pn;
		}
	}
	return NULL;
}

void find_flechie_res(p_node cur, char* search, flechie*** res, int* size_res) { 
	if (cur == NULL) return;
	int i_cara = -1;
	p_node temp = verif_flechies(cur, search, &i_cara);
	if (temp != NULL) {
		(*size_res)++;
		if (res == NULL) *res = (flechie**) malloc(sizeof(flechie*));
		else *res = realloc(*res, (*size_res) * sizeof(flechie*));
		(*res)[(*size_res) - 1] = temp->tab[i_cara];
	}

	for (int letter=0; letter < 28; letter++) {
		if (cur->alphabet[letter] == NULL) continue;

		find_flechie_res(cur->alphabet[letter], search, res, size_res);
	}

	return;
}

flechie** search_flechie(trees T, char* search, int* size_res) {
	*size_res = 0;
	p_node* tab_t = (p_node*) malloc(sizeof(p_node) * NB_TREES);

	tab_t[0] = T.tree_adj;
	tab_t[1] = T.tree_nom;
	tab_t[2] = T.tree_ver;
	tab_t[3] = T.tree_adv;
	tab_t[4] = T.tree_pro;
	tab_t[5] = T.tree_pre;
	tab_t[6] = T.tree_det;
	tab_t[7] = T.tree_int;
	tab_t[8] = T.tree_con;
	tab_t[9] = T.tree_qpro;

	flechie** res = NULL;
	for (int i_tree=0; i_tree<NB_TREES; i_tree++) {
		find_flechie_res(tab_t[i_tree], search, &res, size_res);
	}

	free(tab_t);

	return res;
}