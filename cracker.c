#include <stdio.h>
#include <string.h>

char* stringgen(int length) {
	static int ch = 'a';

	char res[length+1];

	res[0] = ch;
	res[1] = '\0';

	//if we reached the end of the alphabet, cycle back to the beginning
	if (ch == 'z') ch = 'a';

	//convert char[] to char*
	char* ret = &res[0];
	return ret;
}

int main(int argc, char** argv) {
	for (int i = 0; i < ('z' - 'a'); i++) {
		char* guess = stringgen(1);

	}
}
