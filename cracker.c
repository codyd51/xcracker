#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#define MAX_LENGTH 16

int attempt_password(char* guess, char* correct) {
	//if they didn't give a password to check against, 
	//pass their guess to the locked program
	if (!correct) {
		char input[strlen(guess) + 1];
		sprintf(input, "./locked \"%s\"\n", guess);
		return system(input);
	}
	//check for correct password
	return strcmp(guess, correct);
}

static int tries = 0;

int dictionary_crack(char* correct) {
	FILE* file = fopen("common_pwds.txt", "r");
	char line[256];

	while (fgets(line, sizeof(line), file)) {
		tries++;

		//strip newline
		char* pos;
		if ((pos = strchr(line, '\n')) != NULL) {
			*pos = '\0';
		}

		if (!attempt_password(line, correct)) {
			//found correct password!
			printf("\n---done---\n");
			printf("Password: %s\n", line);
			printf("Found in %d attempts\n", tries);

			fclose(file);

			return 0;
		}
	}
	//couldn't find password!
	fclose(file);
	return 1;
}

int inc(char* c) {
	if (c[0] == 0) return 0;

	if (c[0] == 127) {
		c[0] = 32;
		return inc(c + sizeof(char));
	}
	c[0]++;
	return 1;
}

int brute_force_crack(char* correct) {
	for (int length = 1; length <= MAX_LENGTH; length++) {
		char* guess = malloc((length + 1) * sizeof(char));
		for (int i = 1; i <= length; i++) {
			for (int j = 0; j < i; j++) {
				guess[j] = 32;
			}
			guess[i] = 0;
		}
		do {
			tries++;
			if (!attempt_password(guess, correct)) {
				//success! we found the correct password
				printf("\n---done---\n");
				printf("Password: %s\n", guess);
				printf("Found in %d attempts\n", tries);
				return 0;
			}
		} while(inc(guess));
	}
	return 1;
}

int main(int argc, char** argv) {
	clock_t begin = clock();

	//if the user gave a password to use, use it instead of the locked program
	char* passed = NULL;
	if (argc > 1) passed = argv[1];

	//try dictionary attack first
	//attempt most common passwords
	if (dictionary_crack(passed)) {
		//now try brute force
		//try every possible password
		if (brute_force_crack(passed)) {
			//out of guesses
			printf("Couldn't find password.\n");
			return 1;
		} 
		else printf("Brute force succeeded.\n");
	}
	else printf("Dictionary crack succeeded.\n");

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Completed in %f seconds.\n", time_spent);
	return 0;
}
