#include "main.h"

int main(){
	node** tree_adj = NULL, **tree_nom = NULL, **tree_ver = NULL, **tree_adv = NULL;
	
	int size;
	char* baseword;
	char** file = read_file("mots.txt", &size);

	for(int i=0; i<size; i++){
		printf("%s \n",get_split_space(file[i], baseword)[1]);
	}

	return 0;
}


void display_file(char** file, int size){
	for(int i=0; i<size; i++){
		printf("%s\n", file[i]);
	}
}


flechie get_split_space(const char* line, char* baseword){
	int size = strlen(line);
	flechie f = {NULL, NULL};

	int change = 0;
	int index = 0;
	for(int i=0; i<size; i++){
		if(line[i] != '\t'){
			switch (change) {
				case 1:
					if(f.word == NULL) f.word = (char*) malloc(sizeof(char));
					else f.word = realloc(f.word, index+1);
					f.word[index] = line[i];
					break;
				case 2:
					if(baseword == NULL) baseword = (char*) malloc(sizeof(char));
					else baseword = realloc(baseword, index+1);
					baseword[index] = line[i];
					break;
				case 3:
					// la fonction de découpage des caractéristiques
					break;
			}
			index++;
		}
		else{
			change++;
			index = 0;
		}
	}
	return f;
}
