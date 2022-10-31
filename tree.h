#ifndef _HEADER_TREE_
#define _HEADER_TREE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

#define SIZE 10

typedef struct s_flechie {
	char *word;
	char *baseword;
	char **tab_cara;
	int n_cara;
} flechie;

typedef struct s_node {
	char letter;
	flechie **tab;
	int n_flechies;
	struct s_node **alphabet;
} node, *p_node;

typedef p_node tree;

typedef struct s_trees {
	tree tree_adj;
	tree tree_nom;
	tree tree_ver;
	tree tree_adv;
} trees;

void free_all(trees T);
p_node sample_tree();
flechie *get_split(char*); // This function returns an array of [flechies, base, params]
char** get_split_carac(char*, int*); // This function retutns an array of the different caracteristics of a word

void display_struct(flechie);
void display_carac(char**);

node* create_node(char);
p_node init_tree();
void edit_tree(trees, char* line);

p_node* search_word(trees, char*, int*);
p_node random_word(tree t);
int is_alphabet_empty(p_node* alphabet);

#endif