#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "file.h"

#define LINE 300000
#define COL 200 
 
char** read_file(char* fileName, int* tot){
	char** line = (char**) malloc(sizeof(char*)*LINE);
	for(int l=0; l<LINE; l++){
		line[l] = (char*) malloc(sizeof(char)*COL);
	}
    FILE *fptr = NULL; 
    int i = 0;
    *tot = 0;

	fptr = fopen(fileName, "r");
    while(fgets(line[i], COL, fptr)) {
        int j = strlen(line[i]);
        if (line[i][j - 1] == '\n') line[i][j - 1] = '\0';
        else line[i][j] = '\0';
        i++;
    }
    *tot = i;
    return line;
}

void display_file(char** file, int size){
	for(int i=0; i<size; i++){
		printf("%s\n", file[i]);
	}
}

void free_file(char** file) {
    for (int i=0; i<LINE; i++) free(file[i]);
    free(file);
}
