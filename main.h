#ifndef _HEADER_MAIN_
#define _HEADER_MAIN_

typedef struct node {
	char letter;
	char** flechies;
	struct node** alphabet;
} node;


void display_file(char**, int); // This function displays the loaded file
line_nom_adj get_struct_line(char**); // This function returns a struct with all informations of a line
char** get_split_space(char*); // This function returns an array of [flechies, base, params]


#endif