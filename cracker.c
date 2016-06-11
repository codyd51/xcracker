#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

char* stringgen(int length) {
	static int ch = 32;

	char res[2] = "\0";

	res[0] = ch;

	ch++;
	//if we reached the end of printable characters, cycle back to the beginning
	if (ch == 127) ch = 32;
	//the following characters trip us up, so if we're on one then skip it
	if (ch == '\"') ch++;
	if (ch == '&') ch++;
	if (ch == '\\') ch++;
	if (ch == '`') ch++;

	//convert char[] to char*
	char* ret= malloc((length + 1) * sizeof(char));
	ret = strncpy(ret, res, length);
	
	return ret;
}

int main(int argc, char** argv) {
	for (int i = 0; i < (127-32); i++) {
		char* guess = stringgen(1);

		char command[512];
		sprintf(command, "./locked \"%s\"", guess);
		int status = system(command);
		if (!status) {
			//success! we found the correct password
			printf("\n");
			printf("---done---\n");
			printf("Password: %s\n", guess);
			printf("Found in %d tries\n", i);
			return 0;
		}
	}

	//out of guesses
	printf("Couldn't find password.");
	return 1;
}
