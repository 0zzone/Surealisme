#ifndef _HEADER_TREE_
#define _HEADER_TREE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

#define SIZE 10
#define NB_TREES 9

/**
 * Structure of a flechi word. 
 * Contains:
 * * flechi word,
 * * base word,
 * * an array of the flechi word caracteristics,
 * * number of caracteristics / logical size of the array. 
*/
typedef struct s_flechi {
	char *word;
	char *baseword;
	char **tab_caracteristics;
	int nb_cara;
} flechi;

/**
 * A tree node, containing the following members:
 * * letter,
 * * tab_flechis: array of flechi words corresponding to the reached baseword,
 * * nb_flechis: number of flechi words, or logical length of tab_flechis,
 * * alphabet: array of pointed nodes, index with respect to their letter (order defined by function get_index: from 'a' to 'z', then '-' and apostrophe ').
*/
typedef struct s_node {
	char letter;
	flechi **tab_flechis;
	int nb_flechis;
	struct s_node **alphabet;
} node, *p_node;

typedef p_node tree;

/**
 * Structure containing all n-ary trees. 
*/
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


/**
 * Free every tree of T and their content. 
*/
void free_all(trees T);

/**
 * Returns an example tree.
*/
p_node sample_tree();
/**
 * Parses a line from the dictionary.
 * Returns an array of [flechi word, base word, flechi word caracteristics]
 * **/
flechi *get_split(char*);

/**
 * Returns an array of the different caracteristics of a word.
 * Used by get_split function.
*/
char** get_split_carac(char*, int*); 

void display_carac(char**);

/**
 * Creates a node (allocates it, set its values properly).
*/
node* create_node(char);

/**
 * Initialize a struct of trees.
*/
trees init_trees();

/**
 * Initialize a tree.
*/
tree init_tree();

/**
 * Based on a prompt, returns the correct index for the node alphabet.
 * Used by functions that rely on tree navigation. 
*/
int get_index(char prompt);

/**
 * Based on a line from the dictionnary, edits the corresponding tree. 
*/
void edit_tree(trees T, char* line);

/**
 * Using a char* prompt, returns an array of p_nodes whose baseword is prompt.
 * The int* argument gives the size of the returned array. 
*/
p_node* search_word(trees, char*, int*);

/**
 * While knowing the tree to look at, returns a random valid p_node (it has a baseword and flechi words).
*/
p_node random_word(tree t);

/**
 * Receives the alphabet of a node.
 * Returns 1 if all values of alphabet is NULL (cannot navigate deeper into the tree);
 * else return 0.
*/
int is_alphabet_empty(p_node* alphabet);

/**
 * Searches definitions of the searched word (can be a flechi word) into all trees.
 * Returns an array of pointed flechi structures corresponding to the prompt. 
 * The int* argument gives the size of the returned array.
*/
flechi** search_flechie(trees T, char* search, int* size_res);

/**
 * Displays p_node elements.
*/
void display_node(p_node pn);

/**
 * Displays the flechi elements. 
*/
void display_flechie(flechi* fl);

#endif