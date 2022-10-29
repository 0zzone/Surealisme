#ifndef _HEADER_MAIN_
#define _HEADER_MAIN_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

typedef struct {
	char* word;
	char** cara;
}flechie;

typedef struct {
	flechie** tab;
	int number;
}tab_flechies;

typedef struct node {
	char letter;
	tab_flechies* flechies;
	struct node** alphabet;
} *p_node;


void display_file(char**, int); // This function displays the loaded file
flechie get_split_space(const char*, char*); // This function returns an array of [flechies, base, params]


#endif