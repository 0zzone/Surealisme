#include "gen.h"

p_node* gen_phrase_nodes(trees T, int* size) {
	int model = rand() % 3;
	int l, index = 0;
	p_node* res = NULL;
	p_node* temp = NULL;
	switch (model){
		case 0: // nom – adjectif – verbe – nom
			l = 4;
			res = (p_node*) malloc(sizeof(p_node*) * l);

			res[index++] = random_word(T.tree_nom);
			res[index++] = random_word(T.tree_adj);
			res[index++] = random_word(T.tree_ver);
			res[index++] = random_word(T.tree_nom);
			break;

		case 1: // nom – ‘qui’ – verbe – verbe – nom – adjectif
			l = 6;
			res = (p_node*) malloc(sizeof(p_node) * l);

			res[index++] = random_word(T.tree_nom);
			temp = search_word(T, "qui", NULL);
			if (temp != NULL) {
				res[index++] = temp[0];
				free(temp);
			} else {
				printf("cannot find the word 'qui'\n");
				res[index++] = NULL;
			}
			res[index++] = random_word(T.tree_ver);
			res[index++] = random_word(T.tree_ver);
			res[index++] = random_word(T.tree_nom);
			res[index++] = random_word(T.tree_adj);
			break;

		case 2: // interjection – nom – adverbe – adjectif – verbe – adjectif – nom – adjectif – 'et' – adverbe – adjectif 
			l = 11;
			res = (p_node*) malloc(sizeof(p_node) * l);

			res[index++] = random_word(T.tree_int);
			res[index++] = random_word(T.tree_nom);
			res[index++] = random_word(T.tree_adv);
			res[index++] = random_word(T.tree_adj);
			res[index++] = random_word(T.tree_ver);
			res[index++] = random_word(T.tree_adj);
			res[index++] = random_word(T.tree_nom);
			res[index++] = random_word(T.tree_adj);
			temp = search_word(T, "et", NULL);
			if (temp != NULL) {
				res[index++] = temp[0];
				free(temp);
			} else {
				printf("cannot find the word 'et'\n");
				res[index++] = NULL;
			}

			res[index++] = random_word(T.tree_adv);
			res[index++] = random_word(T.tree_adj);
			break;

		default:
			break;
		}
	*size = index;
	return res;
}

char* find_flechie_genrenumber(p_node pn, int gender, int number) {
	// model: [Nom, Mas, SG, Fem, PL]
	char* tab_gender[] = {"Mas", "Fem", "InvGen"};
	char* tab_number[] = {"SG", "PL", "InvPL"};
	flechi** tab = pn->tab_flechis;
	
	for (int i=0; i < pn->nb_flechis; ++i) {
		for (int i_cara=0; i_cara < (int) tab[i]->nb_cara / 2; ++i_cara) {
			int cond_genre = (gender == 2 ||
				strcmp(tab[i]->tab_caracteristics[i_cara * 2 + 1], tab_gender[gender]) == 0 ||
				strcmp(tab[i]->tab_caracteristics[i_cara * 2 + 1], tab_gender[2]) == 0);
			int cond_type = (number == 2 ||
				strcmp(tab[i]->tab_caracteristics[i_cara * 2 + 2], tab_number[number]) == 0 ||
				strcmp(tab[i]->tab_caracteristics[i_cara * 2 + 2], tab_number[2]) == 0);

			if (cond_type && cond_genre) {
				return tab[i]->word;
			}
		}
	}
	return NULL;
}

char* find_flechie_verb(p_node pn, char temps, int gender, int pers) {
	// models: [Ver:PPre] | [Ver:IImp+SG+P1:IImp+SG+P2]
	char* tab_gender[] = {"SG", "PL", "InvPL"};
	char* tab_pers[] = {"P1", "P2", "P3"};
	flechi** tab = pn->tab_flechis;
	
	for (int i=0; i < pn->nb_flechis; ++i) {
		for (int i_cara=0; i_cara < (int) tab[i]->nb_cara / 3; ++i_cara) {
			int cond_temps = (tab[i]->tab_caracteristics[(i_cara * 3) + 1])[0] == temps;
            int cond_genre = (gender == 2 || strcmp(tab[i]->tab_caracteristics[(i_cara * 3 + 1) + 1], tab_gender[gender]) == 0 || strcmp(tab[i]->tab_caracteristics[(i_cara * 3 + 1) + 1], tab_gender[2]) == 0);
			int cond_pers = strcmp(tab[i]->tab_caracteristics[(i_cara * 3 + 2) + 1], tab_pers[pers]) == 0;

			if (cond_temps && cond_genre && cond_pers) return tab[i]->word;
		}
	}
	return NULL;
}

/**
 * If pn has a noun flechi form, return a random genre and number that pn has.
 * Returns: 1 if pn has at least a noun flechi form; else 0. 
*/
int get_random_genrenumber_from_noun(p_node pn, int* genre, int* number) {
	int noun_exists = 0;
	for (int i=0; i < pn->nb_flechis; ++i) if (strcmp(pn->tab_flechis[i]->tab_caracteristics[0], "Nom") == 0) {
		noun_exists = 1;
		break;
	}
	if (noun_exists == 0) return 0;

	int r; 
	flechi* temp = NULL;
	while (1) {
		r = rand() % pn->nb_flechis;
		temp = pn->tab_flechis[r];
		if (strcmp(temp->tab_caracteristics[0], "Nom") != 0) continue;

		r = rand() % (temp->nb_cara - 1) / 2;
		if (strcmp(temp->tab_caracteristics[2*r + 1], "Mas") == 0) *genre = 0;
		else if (strcmp(temp->tab_caracteristics[2*r + 1], "Fem") == 0) *genre = 1;
		else *genre = rand() % 2;

		if (strcmp(temp->tab_caracteristics[2*r + 2], "SG") == 0) *number = 0;
		else if (strcmp(temp->tab_caracteristics[2*r + 2], "PL") == 0) *number = 1;
		else *number = rand() % 2;

		return 1;
	}
}


/**
 * Makes a string from an array of strings.
 * Does not de-allocate the array, nor the strings.
*/
char* transform_from_array(char** array, int size_array) {
	char* res = NULL;
	int size_res = 0;
	for (int i=0; i<size_array; ++i) {
		if (array[i] == NULL) continue;
        int taille = strlen(array[i]);

		res = realloc(res, size_res + taille + 2); // include space and null char
		for (int j=0; j < taille; ++j) res[size_res + j] = array[i][j];
		res[size_res + taille] = ' ';
		res[size_res + taille + 1] = '\0';
		size_res += taille + 1; // include space char 
	}
    res[size_res - 1] = '\0';
	return res;
}

char* gen_phrase_base(trees T) {
	int size_tnode = 0;
	p_node* nodes = gen_phrase_nodes(T, &size_tnode);
	int size_fl = size_tnode;
	char** tab_flechies = malloc(sizeof(char*) * size_fl);

	for (int i=0; i<size_tnode; ++i) if (nodes[i] != NULL) tab_flechies[i] = nodes[i]->tab_flechis[0]->baseword;

	char* res = transform_from_array(tab_flechies, size_fl);
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

	int gender = rand() % 3, number = rand() % 3;

	for (int i=0; i<size_tnode; ++i) {
        char* temp = NULL;
		if (strcmp(nodes[i]->tab_flechis[0]->tab_caracteristics[0], "Nom") == 0) {
			get_random_genrenumber_from_noun(nodes[i], &gender, &number);
			size_fl++;

			// déterminant
			p_node rnd_det = random_word(T.tree_det);
			tab_flechies = realloc(tab_flechies, sizeof(char*) * size_fl);
            
            do {
                temp = find_flechie_genrenumber(rnd_det, gender, number);
			    if (temp == NULL) {
				printf("missing flechi form for det %s with gender %d and number %d\n", rnd_det->tab_flechis[0]->baseword, gender, number);
                rnd_det = random_word(T.tree_det);
                }
            } while (temp == NULL);
			tab_flechies[index++] = temp;

			// nom
            do {
			    temp = find_flechie_genrenumber(nodes[i], gender, number);
			    if (temp == NULL) {
				    printf("missing flechi form for nom %s with gender %d and number %d\n", nodes[i]->tab_flechis[0]->baseword, gender, number);
                    nodes[i] = random_word(T.tree_nom);
                }
            } while (temp == NULL);
			tab_flechies[index] = temp;
			
		}
		else if (strcmp(nodes[i]->tab_flechis[0]->tab_caracteristics[0], "Adj") == 0) {
            do {
				temp = find_flechie_genrenumber(nodes[i], gender, number);
				if (temp == NULL) {
					printf("missing flechi form for adj %s with gender %d and number %d\n", nodes[i]->tab_flechis[0]->baseword, gender, number);
                    nodes[i] = random_word(T.tree_adj);
                }} while (temp == NULL);
				tab_flechies[index] = temp;
			
        }
		else if (strcmp(nodes[i]->tab_flechis[0]->tab_caracteristics[0], "Ver") == 0) {
            do {
			    temp = find_flechie_verb(nodes[i], 'I', number, 2);
			    if (temp == NULL) {
			    	printf("missing flechi form for ver %s with time I, number %d and person 2\n", nodes[i]->tab_flechis[0]->baseword, number);
                    nodes[i] = random_word(T.tree_ver);
			    }} while (temp == NULL);
			    tab_flechies[index] = temp;
            
		}
		else { // préposition ou pronom indéfini ou interjection
			tab_flechies[index] = nodes[i]->tab_flechis[0]->word;
		}
    index++;
    }

	char* res = transform_from_array(tab_flechies, size_fl);
	free(tab_flechies);
	free(nodes);
	return res;
}
