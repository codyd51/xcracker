#include <stdio.h>
#include <string.h>

#define PASSWORD "b"

int main(int argc, char** argv) {
	char word[256];
	fgets(word, sizeof(word), stdin);
	
	//remove newline from input
	char* pos;
	if ((pos = strchr(word, '\n')) != NULL) {
		*pos = '\0';
	}

	//check for correct password
	if (strcmp(word, PASSWORD) == 0) {
		printf("Access granted.\n");
		return 0;
	}
	printf("Incorrect password.\n");
	return 1;
}
