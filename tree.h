#ifndef _HEADER_TREE_
#define _HEADER_TREE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

#define SIZE 10
#define NB_TREES 9

typedef struct s_flechi {
	char *word;
	char *baseword;
	char **tab_caracteristics;
	int nb_cara;
} flechi;

typedef struct s_node {
	char letter;
	flechi **tab_flechis;
	int nb_flechis;
	struct s_node **alphabet;
} node, *p_node;

typedef p_node tree;

typedef struct s_trees {
	tree tree_adj;
	tree tree_nom;
	tree tree_ver;
	tree tree_adv;
	tree tree_pro;
	tree tree_pre;
	tree tree_det;
	tree tree_int;
	tree tree_con;
} trees;

typedef struct {
	char p[10];
	int genre; // 0: Masculin 1:Féminin 2: Non binaire
	int nombre; // 0: Singulier 1: Pluriel
} pronom;


void free_all(trees T);
p_node sample_tree();
flechi *get_split(char*); // This function returns an array of [flechies, base, params]
char** get_split_carac(char*, int*); // This function retutns an array of the different caracteristics of a word

void display_struct(flechi);
void display_carac(char**);

node* create_node(char);
trees init_trees();
p_node init_tree();
int get_index(char prompt);
void edit_tree(trees T, char* line);

p_node* search_word(trees, char*, int*);
p_node random_word(tree t);
int is_alphabet_empty(p_node* alphabet);
flechi** search_flechie(trees T, char* search, int* size_res);
void display_flechie(flechi* fl);

#endif