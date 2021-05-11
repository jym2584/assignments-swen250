// Document Analysis project functions for Part 2

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "analysis.h"
#include "unit_tests.h"

// First checks that p_list is not NULL. Returns 0 if p_list is a NULL pointer.
// Then checks that word pointer is not NULL and word is not any empty string.
// Returns 0 if either of the above tests on the passed word fails.
//
// Creates the list if starting a fresh list.
// Searches existing list for a match on the word. Increments word count
// if found. If not found adds the word in alphabetic order.
// Returns 1 if the word was added successfully.
// Returns 0 on failure.
// NOTE -- this function makes no assumption on upper or lower case. That is handled by read_file.
// For simplicity all words passed from the unit tests are all lower case only.
int process_word ( struct linked_list *p_list, char *word ) {
	if(p_list == NULL || word == NULL || *word == '\0' ) {
		return 0;
	}
	int status = 0;

	if(find_word(p_list, word) == 1) { // if the word has been found on the list
		struct node* current = p_list -> p_current;
		current -> one_word.word_count++;
		status = 1;

	} else if (add_node_after_current(p_list, word) == 1) { // adding the word to the list has been successful
		status = 1;
		
	} else {
		status = 0;
	}

	return status;
}

// First checks that the passed string with the file name is not a NULL pointer and is not an empty string.
// Also checks that the passed pointer to the linked_list struct is not a NULL pointer.
// Returns 0 if any of the above tests fail.
// returns 0 if the file cannot be read or if the file does not contain any words as defined for this project.
// returns the number of words if the file was found, opened successfully, and it contained at least one valid word.
// NOTE -- this function MUST convert all words read to lower case only! e.g "First" becomes "first"
int read_file( struct linked_list *p_list, char *file_name ) {
	if ( p_list == NULL || file_name == NULL || *file_name == '\0' ) {
		return 0;
	}
	
	FILE *file = fopen( file_name, "r" );
	
	if (file == NULL) { // if the file cannot be read
		return 0;
	}

	// Now read and process the entire file.
	char ch; 
	int count = 0; // word count
	char word[MAX_WORD + 1]; // word array
	int i = 0; // incrementing for word array
	
	for (ch = fgetc(file); ch != EOF; ch = fgetc(file)) { // iterating through each character on the file
	    if(isalpha(ch)) { // If it's a valid character
			ch = tolower(ch); // convert to lowercase if applicable
			word[i] = ch; // add it to our word array
			i++;
			
	    } else {
			word[i] = '\0'; // assuming that there is a non-alpha character, we can stop searching here

			if(process_word(p_list, word) == 1) {
				count++;
			}

			i = 0; // reset back so we can iterate again
		}
	}
	
	fclose(file);
	return count;
}


// Returns 0 in the word_count field if the p_list pointer is NULL.
// Returns 0 in the word_count field if no first word meaning p_head == NULL (empty list).
// Otherwise, returns a struct with the first unique word and its number of occurrences in the text file.
struct word_entry get_first_word( struct linked_list *p_list ) {
	struct word_entry entry ;
	entry.word_count = 0 ;		// cover empty list case.

	if(p_list == NULL || p_list -> p_head == NULL) {
		return entry;
	}

	struct node* head = p_list -> p_head;
	//struct node* current = p_list -> p_current;

	// Setting it to entry now
	entry.unique_word = head -> one_word.unique_word;
	entry.word_count = head -> one_word.word_count;

	p_list -> p_current = head;

	return entry;
}

// Returns 0 in the word_count field if p_list is NULL.
// Returns 0 in the word_count field if no next word (previously reached end of list or it is an empty list).
// Otherwise, returns a struct with the next unique word and its number of occurrences in the text file.
struct word_entry get_next_word( struct linked_list *p_list ) {
	struct word_entry entry ;
	entry.word_count = 0 ;		// cover end of list case.

	if(p_list == NULL || p_list -> p_head == NULL || p_list -> p_current == NULL || p_list -> p_current -> p_next == NULL) {
		return entry;
	}

	struct node* current = p_list -> p_current;

	// Setting it to entry now
	entry.unique_word = current -> p_next -> one_word.unique_word;
	entry.word_count = current -> p_next -> one_word.word_count;

	p_list -> p_current = current -> p_next;

	return entry;	
}

// Returns 0 in the word_count field if no previous word (was already at beginning of the list or it is an empty list).
// Otherwise, returns a struct with the previous unique word and its number of occurrences in the text file.
struct word_entry get_prev_word( struct linked_list *p_list ) {
	struct word_entry entry ;
	entry.word_count = 0 ;		// cover end of list case.
	
	if(p_list == NULL || p_list -> p_head == NULL || p_list -> p_current == NULL || p_list -> p_current -> p_previous == NULL) {
		return entry;
	}

	//struct node* current = p_list -> p_current;
	struct node* previous = p_list -> p_current -> p_previous;
	
	// Setting it to entry now
	entry.unique_word = previous -> one_word.unique_word;
	entry.word_count = previous -> one_word.word_count;

	p_list -> p_current = previous;

	return entry;
}

// Returns 0 in the word_count field if the p_list pointer is NULL.
// Returns 0 in the word_count field if no last word meaning p_tail == NULL (empty list).
// Otherwise, returns a struct with the last unique word and its number of occurrences in the text file.
struct word_entry get_last_word( struct linked_list *p_list ) {
	struct word_entry entry ;
	entry.word_count = 0 ;		// cover empty list case.

	if(p_list == NULL || p_list -> p_tail == NULL) {
		return entry;
	}

	//struct node* current = p_list -> p_current;
	struct node* tail = p_list -> p_tail;

	// Setting it to entry now
	entry.unique_word = tail -> one_word.unique_word;
	entry.word_count = tail -> one_word.word_count;

	p_list -> p_current = tail;
	
	return entry;
}

// First check the p_list is not NULL. Return 0 if it is NULL.
// Return 0 if the list is empty (e.g. p_head is NULL).
// Writes the sorted unique word list to a csv file.
// Receives the linked list pointer and the name of the file to be created.
// Returns 1 on a successful write of the file.
// Returns 0 on any failure.
// Test for a NULL or empty string in the file_name. Return 0 for failure if NULL or empty.
// Be sure to test for failure to open the file, failure to write to the file, and failure to close.
// You must have a header row exactly like this (without the quotes): "word,count"
// You must have one row for each unique word and its count (e.g. without quotes "student,5").
// It must be in sorted order and must be the complete list.
int write_unique_word_list_to_csv_file(  struct linked_list *p_list, char *file_name ) {
	if ( p_list == NULL || file_name == NULL || *file_name == '\0' ) {
		return 0;
	}
	
	FILE *file = fopen( file_name, "w" );
	
	if (file == NULL) { // if the file cannot be read
		return 0;
	}
	fprintf(file, "word,count\n");

	struct node *current = p_list -> p_current;
	while(current) { // iterating through list
		fprintf(file,"%s,%d\n", current -> one_word.unique_word, current -> one_word.word_count);
		current = current -> p_next; // go to the next word
	}
		
	fclose(file);
	return 1;
}
