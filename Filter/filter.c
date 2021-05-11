/*
 * Implementation of functions that filter values in strings.
 *****
 * YOU MAY NOT USE ANY FUNCTIONS FROM <string.h> OTHER THAN
 * strcpy() and strlen()
 *****
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "filter.h"

#define NUL ('\0')

/*
 * YOU MAY FIND THIS FUNCTION USEFUL.
 * Return true if and only if character <c> is in string <s>.
 */
static bool includes(char c, char *s) {
	while( *s && c != *s ) {
		s++ ;
	}
	return c == *s ;
}

/*
 * YOU MAY ALSO FIND THIS FUNCTION USEFUL.
 * Return true if and only if string <pre> is a prefix of string <s>.
 */
static bool prefix(char *s, char *pre) {
	while( *pre && *s == *pre ) {
		s++ ;
		pre++ ;
	}
	return *pre == NUL ;
}

/*
 * Copy <string> to <result> while removing all occurrences of <ch>.
 */
void filter_ch_index(char string[], char result[], char ch) {
	int i;
	int j = 0;
	for (i = 0; string[i] != '\0'; i++) {
		if(string[i] != ch) {
			result[j] = string[i];
			j++;
		}
	}
	result[j] = '\0';
}

/*
 * Return a pointer to a string that is a copy of <string> with
 * all occurrences of <ch> removed. The returned string must occupy
 * the least possible dynamically allocated space.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *filter_ch_ptr(char *string, char ch) {
	char *p_copy = malloc(strlen(string) + 1); // allocates memory up to the length of string
	char *p = p_copy; // retains the memory address of the first character

	while(*string != '\0') {
		if(*string != ch) { // if the character of the string doesn't match the letter
            *p_copy = *string; // append it to the new string
			//printf("Added %c\n" , *p_copy);
            *p_copy++;
		}
		string++;
	}

	*p_copy = '\0';
	
	p_copy = malloc(strlen(p) + 1); // re-allocates the size of p_copy to be the length of p since we have no more use for p_copy
	strcpy(p_copy, p); // Copy the contents from p to p_copy

	free(p); // We have no more use for p since we have copied the string from p over to p_copy
	
	return p_copy;
}

/*
 * Copy <string> to <result> while removing all occurrences of
 * any characters in <remove>.
 */
void filter_any_index(char string[], char result[], char remove[]) {
	int i;
	int j;
	int k = 0;
	int changed = 0;

	if (strlen(remove) == 0) {
		strcpy(result, string);
		changed = 1; // If there is nothing to change based on the characters on remove, we shouldn't need to iterate
	}

	if (changed != 1) { // Preventing iteration if there is nothing on remove
		for (i = 0; i < strlen(string); i++) {
			int count = 0;
			for(j = 0; j < strlen(remove); j++) {
				if(string[i] != remove[j]) { // If the string doesn't match any characters on remove
					count++;
				}

				if(count == strlen(remove)) { // If the string doesn't match any characters on remove
					result[k] = string[i]; // Add it to our result array
					k++;
				}
			}
		}
		result[k] = '\0';
	}

}

/*
 * Return a pointer to a copy of <string> after removing all
 * occurrrences of any characters in <remove>.
 * The returned string must occupy the least possible dynamically
 * allocated space.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *filter_any_ptr(char *string, char* remove) {
	char *p_copy = malloc(strlen(string) + 1); // allocates memory up to the length of string
	char *p = p_copy; // retains the memory address of the first character
	
	while(*string != '\0') {
		if(!includes(*string, remove)) {
			*p_copy = *string;
			*p_copy++;
		}
		string++;
	}

	*p_copy = '\0';
	
	p_copy = malloc(strlen(p) + 1); // re-allocates the size of p_copy to be the length of p since we have no more use for p_copy
	strcpy(p_copy, p); // Copy the contents from p to p_copy

	free(p); // We have no more use for p since we have copied the string from p over to p_copy
	
	return p_copy;
}

/*
 * Return a pointer to a copy of <string> after removing all
 * occurrrences of the substring <substr>.
 * The returned string must occupy the least possible dynamically
 * allocated space.
 *****
 * YOU MAY *NOT* USE ARRAY INDEXING.
 *****
 */
char *filter_substr(char *string, char* substr) {
	char *p_copy = malloc(strlen(string) + 1); // allocates memory up to the length of string
	char *p = p_copy; // retains the memory address of the first character

	while(*string != '\0') {
		if (prefix(string, substr)) { // if a substring exists from the character at the string "index"
			//printf("Substring found for %s\n", string);
			int count = 0;
			for(; count != strlen(substr); count++) { // Skipping over the characters with the substring
				string++;
			}
		} else {
			*p_copy = *string; // Add everything else
			*p_copy++;
			string++;
		}
	}

	*p_copy = '\0';
	
	p_copy = malloc(strlen(p) + 1); // re-allocates the size of p_copy to be the length of p since we have no more use for p_copy
	strcpy(p_copy, p); // Copy the contents from p to p_copy

	free(p); // We have no more use for p since we have copied the string from p over to p_copy
	
	return p_copy;
}
