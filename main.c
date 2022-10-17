#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "file.h"

int main(){
	
	int size;
	char** file = read_file("mots.txt", &size);

	return 0;
}