#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main() {
	int tot_chars = 0;
	int tot_lines = 0;
	int tot_words = 0;
	int isFalse;

	int count = 0;
	int ch;
	int i = 0;
	int tot_words2 = 0;

	while ((ch = getchar()) != EOF) {
		tot_chars++;
		
		if(ch == ' ') {
			i = 1;
		}

		if (isspace(ch)) {
			isFalse = 0;
		} else if (isFalse == 0) {
			tot_words++;
			isFalse = 1;
		}

		if (ch == '\n') {
			tot_lines++;
		}

	}

	printf("Lines in the file: %d\n", tot_lines);
	printf("Characters in the file: %d\n", tot_chars);
	printf("Words in the file: %d\n", tot_words);
	return 0;
}
