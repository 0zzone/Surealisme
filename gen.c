#include "gen.h"

p_node* gen_phrase_nodes(trees T, int* size) {
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
        p_node* temp = search_word(T, "qui", NULL);
        if (temp == NULL) {
            printf("cannot find the word 'qui'\n");
            res[index++] = NULL;
        }
		else {
			res[index++] = temp[0];
			free(temp);
		}
		res[index++] = random_word(T.tree_ver);
		res[index++] = random_word(T.tree_ver);
		res[index++] = random_word(T.tree_nom);
		res[index++] = random_word(T.tree_adj);
	}
	*size = index;
	return res;
}

char* find_flechie_typegenre(p_node pn, int type, int genre) {
	// model: [Nom, Mas, SG, Fem, PL]
	char* tab_type[] = {"Mas", "Fem", "InvGen"};
	char* tab_genre[] = {"SG", "PL", "InvPL"};
	flechi** tab = pn->tab_flechis;
	
	for (int i=0; i < pn->nb_flechis; ++i) {
		for (int i_cara=0; i_cara < (int) tab[i]->nb_cara / 2; ++i_cara) {
			int cond_type = (strcmp(tab[i]->tab_caracteristics[i_cara * 2 + 1], tab_type[type]) == 0 ||
			strcmp(tab[i]->tab_caracteristics[i_cara * 2 + 1], tab_type[2]) == 0);
			int cond_genre = strcmp(tab[i]->tab_caracteristics[i_cara * 2 + 2], tab_genre[genre]) == 0 ||
			strcmp(tab[i]->tab_caracteristics[i_cara * 2 + 2], tab_genre[2]) == 0;

			if (cond_type && cond_genre) {
				return tab[i]->word;
			}
		}
	}
	return NULL;
}

char* find_flechie_verb(p_node pn, char temps, int genre, int pers) {
	// models: [Ver:PPre] | [Ver:IImp+SG+P1:IImp+SG+P2]
	char* tab_genre[] = {"SG", "PL", "InvPL"};
	char* tab_pers[] = {"P1", "P2", "P3"};
	flechi** tab = pn->tab_flechis;
	
	for (int i=0; i < pn->nb_flechis; ++i) {
		for (int i_cara=0; i_cara < (int) tab[i]->nb_cara / 3; ++i_cara) {
			int cond_temps = (tab[i]->tab_caracteristics[(i_cara * 3) + 1])[0] == temps;
            int cond_genre = (strcmp(tab[i]->tab_caracteristics[(i_cara * 3 + 1) + 1], tab_genre[genre]) == 0 || strcmp(tab[i]->tab_caracteristics[(i_cara * 3 + 1) + 1], tab_genre[2]) == 0);
			int cond_pers = strcmp(tab[i]->tab_caracteristics[(i_cara * 3 + 2) + 1], tab_pers[pers]) == 0;

			if (cond_temps && cond_genre && cond_pers) return tab[i]->word;
		}
	}
	return NULL;
}

char* gen_phrase_base(trees T) {
	int size_tnode = 0;
	p_node* nodes = gen_phrase_nodes(T, &size_tnode);
	int size_fl = size_tnode;
	char** tab_flechies = malloc(sizeof(char*) * size_fl);

	for (int i=0; i<size_tnode; ++i) if (nodes[i] != NULL) tab_flechies[i] = nodes[i]->tab_flechis[0]->baseword;

	char* res = NULL;
	int size_res = 0;
	for (int i=0; i<size_fl; ++i) {
		if (tab_flechies[i] == NULL) continue;
        int taille = strlen(tab_flechies[i]);

		res = realloc(res, size_res + taille + 2); // include space and null char
		for (int j=0; j < taille; ++j) res[size_res + j] = tab_flechies[i][j];
		res[size_res + taille] = ' ';
		res[size_res + taille + 1] = '\0';
		size_res += taille + 1; // include space char 
	}
    res[size_res - 1] = '\0';
	free(tab_flechies);
	free(nodes);
	return res;
}


char* gen_phrase_flechie(trees T){
	int size_tnode = 0;
	p_node* nodes = gen_phrase_nodes(T, &size_tnode);
	int index = 0;
	int size_fl = size_tnode;
	char** tab_flechies = malloc(sizeof(char*) * size_fl);

	int type, number;

	for (int i=0; i<size_tnode; ++i) {
        char* temp = NULL;
		if (strcmp(nodes[i]->tab_flechis[0]->tab_caracteristics[0], "Nom") == 0) {
			p_node rnd_det = random_word(T.tree_det);

			type = rand() % 2, number = rand() % 2;
			size_fl++;

			// déterminant
			tab_flechies = realloc(tab_flechies, sizeof(char*) * size_fl);
            
            do {
                temp = find_flechie_typegenre(rnd_det, type, number);
			    if (temp == NULL) {
				printf("missing flechi form for det %s with type %d and genre %d\n", nodes[i]->tab_flechis[0]->baseword, type, number);
                rnd_det = random_word(T.tree_det);
                }
            } while (temp == NULL);
			tab_flechies[index++] = temp;

			// nom
            do {
			    temp = find_flechie_typegenre(nodes[i], type, number);
			    if (temp == NULL) {
				    printf("missing flechi form for nom %s with type %d and genre %d\n", nodes[i]->tab_flechis[0]->baseword, type, number);
                    nodes[i] = random_word(T.tree_nom);
                }
            } while (temp == NULL);
			tab_flechies[index] = temp;
			
		}
		else if (strcmp(nodes[i]->tab_flechis[0]->tab_caracteristics[0], "Adj") == 0) {
            do {
				temp = find_flechie_typegenre(nodes[i], type, number);
				if (temp == NULL) {
					printf("missing flechi form for adj %s with type %d and genre %d\n", nodes[i]->tab_flechis[0]->baseword, type, number);
                    nodes[i] = random_word(T.tree_adj);
                }} while (temp == NULL);
				tab_flechies[index] = temp;
			
        }
		else if (strcmp(nodes[i]->tab_flechis[0]->tab_caracteristics[0], "Ver") == 0) {
            do {
			    temp = find_flechie_verb(nodes[i], 'I', number, 2);
			    if (temp == NULL) {
			    	printf("missing flechi form for ver %s with time I, number %d and pers 2\n", nodes[i]->tab_flechis[0]->baseword, number);
                    nodes[i] = random_word(T.tree_ver);
			    }} while (temp == NULL);
			    tab_flechies[index] = temp;
            
		}
		else { // préposition ou pronom
			tab_flechies[index] = nodes[i]->tab_flechis[0]->word;
		}
    index++;
    }

		
	
	char* res = NULL;
	int size_res = 0;
	for (int i=0; i<size_fl; ++i) {
		if (tab_flechies[i] == NULL) continue;
        int taille = strlen(tab_flechies[i]);

		res = realloc(res, size_res + taille + 2); // include space and null char
		for (int j=0; j < taille; ++j) res[size_res + j] = tab_flechies[i][j];
		res[size_res + taille] = ' ';
		res[size_res + taille + 1] = '\0';
		size_res += taille + 1; // include space char 
	}
    res[size_res - 1] = '\0';
	free(tab_flechies);
	free(nodes);
	return res;
}