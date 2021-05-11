/*
 * Implementation of the read_data module.
 *
 * See read_data.h for a description of the read_data function's
 * specification.
 *
 * Note that the parameter declarations in this module must be
 * compatible with those in the read_data.h header file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "read_data.h"
// Reads the three fields from lines such as W$1349$1.414$ into
// local variables using getchar().
// Converts the two numeric fields to numbers using atoi for the
// integer fields and atof for the double.
// Using a correctly defined set of parameters (use pointers) pass
// those values back to the program that called this function.

void read_data(char *a_char, int *an_int, double *a_float) {
	int i;
	char ch;
	char array[3][MAXLINE+1]; // 3 arrays of array characters
	int split = 0;
	while(split < 3) { // Incrementing on the dollar sign split
		for (i = 0; (ch = getchar()) != EOF; i++) { // iterating through each character given that it's not an end of file or just a new line
			array[split][i] = ch; // Add each character to the word array
			if (ch == '$') { // If the dollar sign is found, we add a NUL terminator and go to the next word on the line
				break; 
			}
		}

		array[split][i] = '\0';
		split++;
	}
	//printf("Output 0: %s\n", array[0]);
	//printf("Output 1: %s\n", array[1]);
	//printf("Output 2 value string %s\n", array[1]);
	//printf("Output 2: %s\n", array[2]);
	//printf("Output 3 value string %s\n", array[2]);

	*a_char = array[0][0];
	*an_int = atoi(array[1]);
	*a_float = atof(array[2]);
	return;
}