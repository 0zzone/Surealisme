#ifndef _HEADER_MAIN_
#define _HEADER_MAIN_

typedef struct node {
	char letter;
	char** flechies;
	struct node** alphabet;
} node;


void display_file(char**, int); // This function displays the loaded file
char** get_split_space(char*); // This function returns an array of [flechies, base, params]


#endif