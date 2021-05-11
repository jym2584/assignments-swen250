/*
 * Implementation of functions that find values in strings.
 *****
 * YOU MAY NOT USE ANY FUNCTIONS FROM <string.h>
 *****
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "find.h"

#define NOT_FOUND (-1)	// integer indicator for not found.

/*
 * Return the index of the first occurrence of <ch> in <string>,
 * or (-1) if the <ch> is not in <string>.
 */
int find_ch_index(char string[], char ch) {
	int i;
	for(i = 0; string[i] != '\0'; i++) {
		if (string[i] == ch) {
			//printf("Found %c at position %d\n", string[i],i);
			return i;
		}
	}
	return -1;
}

/*
 * Return a pointer to the first occurrence of <ch> in <string>,
 * or NULL if the <ch> is not in <string>.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_ch_ptr(char *string, char ch) {
	while(*string != '\0') {
		if(*string == ch) { // dereferencing string
			return string;
		}
		string++;
	}
}

/*
 * Return the index of the first occurrence of any character in <stop>
 * in the given <string>, or (-1) if the <string> contains no character
 * in <stop>.
 */
int find_any_index(char string[], char stop[]) {
	int i;
	int j;
	
	for(i = 0; string[i] != '\0'; i++) {
		for(j = 0; stop[j] != '\0'; j++) {
			if (string[i] == stop[j]) {
				return i;
			}
		}
	}
	return -1;
}

/*
 * Return a pointer to the first occurrence of any character in <stop>
 * in the given <string> or NULL if the <string> contains no characters
 * in <stop>.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_any_ptr(char *string, char* stop) {
	while(*string != '\0') {
		char *stop_temp = stop; // Iterating through the start of each char iteration of string now
		
		while(*stop_temp != '\0') {
			//printf("Comparing : %c == %c\n", *string, *stop_temp);
			if(*string == *stop_temp) {
				return string;
			}
			stop_temp++;
		}
		string++;
	}
	return NULL ;	// placeholder
}

/*
 * Return a pointer to the first character of the first occurrence of
 * <substr> in the given <string> or NULL if <substr> is not a substring
 * of <string>.
 * Note: An empty <substr> ("") matches *any* <string> at the <string>'s
 * start.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_substr(char *string, char *substr) {
	bool mismatch = false;
	if(*substr == '\0') {
		return string;
	}
	
    while (*string != '\0') {
        if (*string == *substr) { // If there is matching characters on string and substring
		char *string_temp = string; // temp string
		char *substr_temp = substr; // temp substr

		while(!mismatch) { // While a mismatch doesn't exist
                	if (!*substr_temp) { // If we matched everything on the substring
                    		return string; // return the character 'index' of the string
			}
                	if (*string_temp != *substr_temp) { // If there is a mismatch on the substring
                    		mismatch = true;
				break; // Don't iterate it any further
			}
			string_temp++;
			substr_temp++;
            	}	
        }
        string++;
    }
    return NULL;
}
