#ifndef _HEADER_MAIN_
#define _HEADER_MAIN_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

typedef struct {
	char* word;
	char* baseword;
	char** cara;
} flechie;


typedef struct node {
	char letter;
	flechie** tab;
	int number;
	struct node** alphabet;
} node, *p_node;

typedef struct {
	p_node tree_adj; 
	p_node tree_nom;
	p_node tree_ver; 
	p_node tree_adv;
} trees;


void display_file(char**, int); // This function displays the loaded file
flechie get_split(char*); // This function returns an array of [flechies, base, params]
char** get_split_carac(char*); // This function retutns an array of the different caracteristics of a word

void display_struct(flechie);
void display_carac(char**);

node* create_node(char);
p_node init_tree();
void edit_tree(trees, char* line);


#endif