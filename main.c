#include "main.h"

#define SIZE 10

int main(){
	node** tree_adj = NULL, **tree_nom = NULL, **tree_ver = NULL, **tree_adv = NULL;
	
	int size;
	char* baseword;
	char** file = read_file("mots.txt", &size);

	flechie f = get_split(file[0]);
	display_struct(f);

	return 0;
}

void display_carac(char** c){
	for(int i=0; i<SIZE; i++){
		printf("%s ", c[i]);
	}
}

void display_struct(flechie f){
	printf("Mot de base : %s\n", f.baseword);
	printf("Mot fléchi : %s\n", f.word);
	display_carac(f.cara);
}


void display_file(char** file, int size){
	for(int i=0; i<size; i++){
		printf("%s\n", file[i]);
	}
}


flechie get_split(char* line){
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

	flechie f;
	f.word = tab[0];
	f.baseword = tab[1];
	f.cara = get_split_carac(tab[2]);

	return f;


}


char** get_split_carac(char* ensemble){
	char** tab = (char**) malloc(sizeof(char*) * SIZE);
	for(int i=0; i<SIZE; i++){
		tab[i] = (char*) malloc(sizeof(char) * 5);
	}

	int change = 0;
	int index = 0;
	for(int k=0; k<strlen(ensemble); k++){
		if(ensemble[k] == ':' || ensemble[k] == '+'){
			change++;
			index = 0;
		}
		else{
			tab[change][index] = ensemble[k];
					index++;
		}
	}
	return tab;

}















