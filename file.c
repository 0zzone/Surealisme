#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "file.h"

#define LINE 100
#define COL 50 
 
char** read_file(char* fileName, int* tot){
	char** line = (char**) malloc(sizeof(char*)*LINE);
	for(int l=0; l<LINE; l++){
		line[l] = (char*) malloc(sizeof(char)*COL);
	}
    FILE *fptr = NULL; 
    int i = 0;
    *tot = 0;

	fptr = fopen(fileName, "r");
    while(fgets(line[i], COL, fptr)) 
	{
        line[i][strlen(line[i]) - 1] = '\0';
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
