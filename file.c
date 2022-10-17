#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define LINE 10
#define COL 50 
 
char** read_file(char* fileName, int* tot){
	char** line = (char**) malloc(sizeof(char*)*LINE);
	for(int l=0; l<LINE; l++){
		line[l] = (char*) malloc(sizeof(char)*COL);
	}
	char fname[20];
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