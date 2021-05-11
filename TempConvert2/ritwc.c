#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define FALSE (0)
#define TRUE  (1)

int main() {
	int tot_chars = 0 ;	/* total characters */
	int tot_lines = 0 ;	/* total lines */
	int tot_words = 0 ;	/* total words */

	/* REPLACE WITH ADDITIONAL VARIABLE DECLARATIONS YOU NEED */
	int i = 0;
	int ch;
	int isFalse;
	int count = 0;

	for (ch = getchar(); ch != '\n' && ch != EOF; ch = getchar()) {
		tot_chars++;
		printf("%s", ch);
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
	/* REPLACE WITH THE CODE FOR WORD COUNT */
	printf("Lines in the file: %d\n", tot_lines);
	printf("Characters in the file: %d\n", tot_chars);
	printf("Words in the file: %d\n", tot_words);
	return 0 ;
}
