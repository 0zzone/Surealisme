#include "gen.h"

p_node* generate_nodes(trees T, int* size) {
	int model = rand() % 2;
	int l = 0, index = 0;
	p_node* res = NULL;
	if(model == 0){
		l = 4;
		res = (p_node*) malloc(sizeof(p_node*) * l);

		res[index++] = random_word(T.tree_nom);
		res[index++] = random_word(T.tree_adj);
		res[index++] = random_word(T.tree_ver);
		res[index++] = random_word(T.tree_nom);
	}
	else{
		l=6;
		res = (p_node*) malloc(sizeof(p_node) * l);

		res[index++] = random_word(T.tree_nom);
		res[index++] = search_word(T, "qui", NULL)[0];
		res[index++] = random_word(T.tree_ver);
		res[index++] = random_word(T.tree_ver);
		res[index++] = random_word(T.tree_nom);
		res[index++] = random_word(T.tree_adj);
	}
	*size = index;
	return res;
}

char* find_flechie_tg(p_node pn, int type, int genre) {
	// model: [Nom, Mas, SG, Fem, PL]
	char* tab_type[] = {"Mas", "Fem", "InvGen"};
	char* tab_genre[] = {"SG", "PL"};
	flechie** tab = pn->tab;
	
	for (int i=0; i < pn->n_flechies; ++i) {
		for (int i_cara=0; i_cara < (int) tab[i]->n_cara / 2; ++i_cara) {
			int cond_type = (strcmp(tab[i]->tab_cara[i_cara * 2 + 1], tab_type[type]) == 0 ||
			strcmp(tab[i]->tab_cara[i_cara * 2 + 1], tab_type[2]) == 0);
			int cond_genre = strcmp(tab[i]->tab_cara[i_cara * 2 + 2], tab_genre[genre]) == 0 ||
			strcmp(tab[i]->tab_cara[i_cara * 2 + 2], tab_genre[2]) == 0;

			if (cond_type && cond_genre) {
				return tab[i]->word;
			}
		}
	}
	return NULL;
}

char* find_flechie_verb(p_node pn, int genre, int pers) {
	// models: [Ver:PPre] | [Ver:IImp+SG+P1:IImp+SG+P2]
	char* tab_genre[] = {"SG", "PL", "InvPL"};
	char* tab_pers[] = {"P1", "P2", "P3"};
	flechie** tab = pn->tab;
	
	for (int i=0; i < pn->n_flechies; ++i) {
		for (int i_cara=0; i_cara < (int) tab[i]->n_cara / 3; ++i_cara) {
			int cond_genre = (strcmp(tab[i]->tab_cara[(i_cara * 3 + 1) + 1], tab_genre[genre]) == 0 || strcmp(tab[i]->tab_cara[(i_cara * 3 + 1) + 1], tab_genre[2]) == 0);
			int cond_pers = strcmp(tab[i]->tab_cara[(i_cara * 3 + 2) + 1], tab_pers[pers]) == 0;

			if (cond_genre && cond_pers) return tab[i]->word;
		}
	}
	return NULL;
}

char* generate_base(trees T) {
	int size_tnode = 0;
	p_node* nodes = generate_nodes(T, &size_tnode);
	int index = 0;
	int size_fl = size_tnode;
	char** tab_flechies = malloc(sizeof(char*) * size_fl);

	for (int i=0; i<size_tnode; ++i) tab_flechies[i] = nodes[i]->tab[0]->baseword;

	char* res = NULL;
	int size_res = 0;
	for (int i=0; i<size_fl; ++i) {
		if (tab_flechies[i] == NULL) continue;

		res = realloc(res, size_res + strlen(tab_flechies[i]) + 1);
		for (int j=0; j < (int) strlen(tab_flechies[i]); ++j) res[j + size_res] = tab_flechies[i][j];
		res[size_res + strlen(tab_flechies[i]) - 1] = ' ';
		res[size_res + strlen(tab_flechies[i])] = '\0';
		size_res += strlen(tab_flechies[i]);
	}
	free(tab_flechies);
	free(nodes);
	return res;
}


char* generate_flechie(trees T){
	int size_tnode = 0;
	p_node* nodes = generate_nodes(T, &size_tnode);
	int index = 0;
	int size_fl = size_tnode;
	char** tab_flechies = malloc(sizeof(char*) * size_fl);

	int type, number;

	for (int i=0; i<size_tnode; ++i) {
		if (strcmp(nodes[i]->tab[0]->tab_cara[0], "Nom") == 0) {
			p_node rnd_det = random_word(T.tree_det);

			type = rand() % 3, number = rand() % 2;
			size_fl++;

			// déterminant
			tab_flechies = realloc(tab_flechies, sizeof(char*) * size_fl);
			char* temp = find_flechie_tg(rnd_det, type, number);
			if (temp == NULL) {
				printf("missing flechie form for det %s with type %d and genre %d\n", nodes[i]->tab[0]->baseword, type, number);
				}
			tab_flechies[index++] = temp;

			// nom
			temp = find_flechie_tg(nodes[i], type, number);
			if (temp == NULL) {
				printf("missing flechie form for nom %s with type %d and genre %d\n", nodes[i]->tab[0]->baseword, type, number);
			}
			tab_flechies[index] = temp;
			
		}
		else if (strcmp(nodes[i]->tab[0]->tab_cara[0], "Adj") == 0) {
				char* temp = find_flechie_tg(nodes[i], type, number);
				if (temp == NULL) {
					printf("missing flechie form for adj %s with type %d and genre %d\n", nodes[i]->tab[0]->baseword, type, number);
				}
				tab_flechies[index] = temp;
			}
		else if (strcmp(nodes[i]->tab[0]->tab_cara[0], "Ver") == 0) {
			char* temp = find_flechie_verb(nodes[i], number, 2);
			if (temp == NULL) {
				printf("missing flechie form for ver %s with number %d and pers 3\n", nodes[i]->tab[0]->baseword, number);
			}
			tab_flechies[index] = temp;
		}
		else { // préposition ou pronom
			tab_flechies[index] = nodes[i]->tab[0]->word;
		}
		}

		index++;
	
	char* res = NULL;
	int size_res = 0;
	for (int i=0; i<size_fl; ++i) {
		if (tab_flechies[i] == NULL) continue;

		res = realloc(res, size_res + strlen(tab_flechies[i] + 1));
		for (int j=0; j < (int) strlen(tab_flechies[i]); ++j) res[j + size_res] = tab_flechies[i][j];
		res[size_res + strlen(tab_flechies[i])] = ' ';
		res[size_res + strlen(tab_flechies[i]) + 1] = '\0';
		size_res += strlen(tab_flechies[i]);
	}
	free(tab_flechies);
	free(nodes);
	return res;
}