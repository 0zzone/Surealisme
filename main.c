#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "file.h"

int main(){
	
	int size;
	char** file = read_file("mots.txt", &size);

	for(int i=0; i<size; i++){
		printf("%s\n", file[i]);
	}

	return 0;
}