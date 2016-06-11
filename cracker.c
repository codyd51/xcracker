#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define MAX_LENGTH 16

int inc(char* c) {
	if (c[0] == 0) return 0;
	if (c[0] == 'z') {
		c[0] = 'a';
		return inc(c + sizeof(char));
	}
	c[0]++;
	return 1;
}

int main(int argc, char** argv) {
	static int tries = 0;
	for (int length = 1; length <= 2; length++) {

		char* guess = malloc((length + 1) * sizeof(char));
		for (int i = 1; i <= length; i++) {
			for (int j = 0; j < i; j++) {
				guess[j] = 'a';
			}
			guess[i] = 0;
		}
		do {
			tries++;

			char command[512];
			sprintf(command, "./locked \"%s\"", guess);
			int status = system(command);
			if (!status) {
				//success! we found the correct password
				printf("\n");
				printf("---done---\n");
				printf("Password: %s\n", guess);
				printf("Found in %d tries\n", tries);
				return 0;
			}
		} while(inc(guess));
	}

	//out of guesses
	printf("Couldn't find password.");
	return 1;
}
