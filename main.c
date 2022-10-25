#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "file.h"

int main(){
	
	int size;
	char** file = read_file("mots.txt", &size);

	for(int i=0; i<size; i++){
		printf("%s \n",get_split_space(file[i])[1]);
	}

	return 0;
}


void display_file(char** file, int size){
	for(int i=0; i<size; i++){
		printf("%s\n", file[i]);
	}
}


char** get_split_space(char* line){
	int size = strlen(line);
	char** tab = (char**) malloc(sizeof(char*) * 3);

	for(int p=0; p<3; p++){
		tab[p] = NULL;
	}

	int change = 0;
	int index = 0;
	for(int i=0; i<size; i++){
		if(line[i] != '\t'){
			if(tab[change] == NULL){
				tab[change] = (char*) malloc(sizeof(char));
			}
			else{
				tab[change] = realloc(tab[change], index+1);
			}
			tab[change][index] = line[i];
			index++;
		}
		else{
			change++;
			index = 0;
		}
	}
	return tab;
}
