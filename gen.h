#ifndef _HEADER_GEN_
#define _HEADER_GEN_


#include "tree.h"

/**
 * Internal function to look for a flechi word (having a type and genre caracteristics) corresponding to given type and genre.
 * Genre varies between 0 and 2 (Masculine, Feminine, Whatever),
 * Number varies between 0 and 2 (Singular, Plural, Whatever).
*/
char* find_flechie_genrenumber(p_node pn, int genre, int number);

/**
 * Internal function to look for a flechi verb corresponding to given time, genre and person.
 * Time is the first letter (IImp -> letter == 'I'),
 * Number varies between 0 and 2 (Singular, Plural, Whatever),
 * Person varies between 0 and 2 (First, Second, Third).
*/
char* find_flechie_verb(p_node pn, char time, int number, int person);

/**
 * Creates an allocated array of p_node.
 * This array follows a predefined sentence model.
 * The int* argument gives the size of the returned value.
*/
p_node* gen_phrase_nodes(trees T, int* size);

/**
 * Generates a model-defined phrase with base words. 
*/
char* gen_phrase_base(trees T);

/**
 * Generates a correct phrase, following a predefined sentence model.
 * If a base word is not associated with required flechi caracteristics, announces it and look for another base word. 
*/
char* gen_phrase_flechie(trees T);

#endif 