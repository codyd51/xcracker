#include <stdio.h>
#include <string.h>

#define PASSWORD "b"

int process_input(char* word) {
	//check for correct password
	if (strcmp(word, PASSWORD) == 0) {
		printf("Access granted.\n");
		return 1;
	}
	printf("Incorrect password.\n");
	return 0;
}

int main(int argc, char** argv) {
	int access_granted = 0;
	while (!access_granted) {
		//get input 
		char word[256];
		fgets(word, sizeof(word), stdin);
		
		//remove newline from input
		char* pos;
		if ((pos = strchr(word, '\n')) != NULL) {
			*pos = '\0';
		}

		//test input
		access_granted = process_input(word);
	}
	return 0;
}
