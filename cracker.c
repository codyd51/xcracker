#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

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

int attempt_password(char* pass) {
	char input[strlen(pass) + 1];
	sprintf(input, "./locked \"%s\"\n", pass);
	return system(input);
}

int main(int argc, char** argv) {
	clock_t begin = clock();

	for (int length = 1; length <= MAX_LENGTH; length++) {
		char* guess = malloc((length + 1) * sizeof(char));
		for (int i = 1; i <= length; i++) {
			for (int j = 0; j < i; j++) {
				guess[j] = 'a';
			}
			guess[i] = 0;
		}
		do {
			static int tries = 0;
			tries++;
			if (!attempt_password(guess)) {
				//success! we found the correct password
				printf("\n");
				printf("---done---\n");
				printf("Password: %s\n", guess);
				printf("Found in %d attempts\n", tries);

				clock_t end = clock();
				double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
				printf("Completed in %f\n", time_spent);
				return 0;
			}
		} while(inc(guess));
	}
	//out of guesses
	printf("Couldn't find password.");
	return 1;
}
