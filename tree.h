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
	struct node **alphabet;
} node, *p_node;

typedef struct s_trees {
	p_node tree_adj;
	p_node tree_nom;
	p_node tree_ver;
	p_node tree_adv;
} trees;

void free_all(trees T);
flechie *get_split(char*); // This function returns an array of [flechies, base, params]
char** get_split_carac(char*, int*); // This function retutns an array of the different caracteristics of a word

void display_struct(flechie);
void display_carac(char**);

node* create_node(char);
p_node init_tree();
void edit_tree(trees, char* line);

p_node* search_word(trees, char*, int*);

#endif