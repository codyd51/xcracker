#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PASSWORD "sea"

int process_input(char* word) {
	//check for correct password
	if (strcmp(word, PASSWORD) == 0) {
		printf("Access granted.\n");
		return 0;
	}
	printf("Incorrect password.\n");
	return 1;
}

int main(int argc, char** argv) {
	if (argc == 1) {
		printf("Please pass a password.\n");
		return 1;
	}

	//create string from arguments
	int i, v = 0, size = argc - 1;

	char* password = (char*)malloc(v);
	for (i = 1; i <= size; i++) {
		password = (char*)realloc(password, (v + strlen(argv[i])));
		strcat(password, argv[i]);

		//if this is not the last element, add a space
		if (i != size) {
			strcat(password, " ");
		}
	}

	//test input
	return process_input(password);
}
