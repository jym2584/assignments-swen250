// Document Analysis project linked list functions
// L. Kiser Feb. 20, 2018

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include "linked_list_functions.h"
#include "unit_tests.h"

// Implement this function first to create an initialized linked list node.
// It must allocate space for the passed string in the one_word structure.
// It must copy the passed string into that structure and sets its word count to 1.
// Assume that the passed word points is not NULL and is not an empty string.
// The calling function is responsible for passing a valid string.
// This function returns a pointer to the allocated node.
struct node *create_node( char *word ) {
	struct node *node = malloc(sizeof(struct node));
  	// adding information to word_entry struct
	
	// Allocating space to pass into unique word
	char *allocate_word = malloc(strlen(word)+1);
  	node->one_word.unique_word = strcpy(allocate_word, word);
  	node->one_word.word_count = 1;

	// Setting next and previous to null
  	node->p_previous = NULL;
  	node->p_next = NULL;
  	return node;   // REMOVE THIS and replace with working code
}

// Inserts a node at the beginning of the linked list.
// Updates the passed set of pointers as needed based upon the addition that was done.
//
// It checks that p_list is not NULL. Checks that word is not NULL and is not an empty string. 
// Returns 0 for failure if either word test fails.
// Also on failure no change is made to the pointers in p_list.
//
// On success it returns a 1 and updates at least the passed p_head and p_current members of p_list.
// p_head and p_current will always point to the newly added node.
// When adding the first node to an empty list p_tail will also point to this same new node since it is the only node.
//
// Hint: use the create_node function to actually create the node.
// Hint: be sure to maintain both the p_previous and p_next pointers in each node.
int add_node_at_head( struct linked_list *p_list, char *word ) {
	if(p_list == NULL || word == NULL || *word == '\0') { // if p_list or word is null, or the word is empty
		return 0; // No changes have been made to the linked_list
	}

	struct node *node = create_node(word); // Create new node of word
	
	if(p_list -> p_head == NULL) { // If there is nothing at the head of the linked list
		p_list -> p_head = node;   // Set the head and tail of the linked list to be the first node that we make!
		p_list -> p_tail = node;
	} else { // Otherwise if a node has been already added to the linked list
		node -> p_next = p_list -> p_head; // Make the next value of the node the head of the LinkedList
		p_list -> p_head -> p_previous = node; // Make the previous node of the head to be the new node
		p_list -> p_head = node; // Make the head to be the new node
		// The next value or tail of the node is already set to NULL
	}

	p_list -> p_current = node; // Set the node as the most recently added of the Linked List
	
	return 1;	// REMOVE THIS and replace with working code
}

// For the passed linked_list pointer free all of the nodes in the list.
// Be careful to free the space for the string before freeing the node itself.
// Also be careful to save a copy of the pointer to the next item in the list before
// freeing the node.
// Lastly, return the number of nodes freed (which could be zero if p_list indicates an empty list).
int clear_linked_list( struct linked_list *p_list ) {
	int freed_count = 0;

	while (p_list -> p_head != NULL){ // Iterating through the linked list to count up how many notes we will free up
		struct node *head_copy = p_list -> p_head; // Save a copy of head
		p_list -> p_head = p_list -> p_head -> p_next; // Setting head to be the next node on the list (like a queue)
		freed_count++;
		free(head_copy); // free the head
	}

	p_list -> p_tail = NULL; // Set tail and current of the list to be null now that we pruned everything from the linked list
	p_list -> p_current = NULL;
	
	return freed_count; // REMOVE THIS and replace with working code
}


// Inserts a node after the current pointer in the linked list.
// Updates the passed set of pointers as needed based upon the addition that was done.
//
// It checks that p_list is not NULL. Checks that word is not NULL and is not an empty string. 
// Returns 0 for failure if either word test fails.
// Also on failure no change is made to the pointers in p_list.
//
// On success it returns a 1 and updates at least the p_current member of p_list. p_current points to the newly added node.
// p_head is updated only if p_current is NULL (an empty list).
// p_tail is updated only if the new node is at the end of the list.
// When adding the first node to an empty list p_tail will also point to this same new node since it is the only node.
//
// Hint: use the create_node function to actually create the node.
// Hint: be sure to maintain both the p_previous and p_next pointers in each node.
// Hint: if this function is called with a p_current that is NULL (meaning the list is empty)
//       use the add_node_at_head function to create the new node.
int add_node_after_current( struct linked_list *p_list, char *word ) {
		if (p_list == NULL || word == NULL || *word == '\0') { // if p_list or word is null, or the word is empty
                return 0; // No changes have been made to the linked_list
        }

        if (p_list->p_current == NULL) { // If the linked list is empty
            add_node_at_head(p_list, word); // Add a new node
        } else { // If a node already exists at the tail
			struct node *node = create_node(word);

			if (p_list->p_current->p_next == NULL) { // If there is nothing on the tail
					node->p_previous = p_list->p_tail; // Set the previous to be the tail
					p_list->p_tail->p_next = node; // Make the tail of the next node to be the new node
					p_list->p_tail = node; // Added the new node to the tail
					p_list->p_current = p_list->p_tail; // Make the current point to the tail

			} else {
					node->p_next = p_list->p_current->p_next; // make the current pointer's next point to the tail
					node->p_previous = p_list->p_current; // make the current pointer's previous point to the head
					p_list->p_current->p_next->p_previous = node; // make the tail's previous point to the current
					p_list->p_current->p_next = node; // make the head's node the same as current
			}

        	p_list->p_current = node; // Make the new node the current
		}
        return 1;
}

// Searches the linked list for the passed word.
// NOTE -- this function REQUIRES that the linked list has been maintained in English language alphabetical order.
// Definition of match: every letter must match exactly including by case.
// e.g. "A" does NOT match "a". "a " does NOT match "a"
//
// If found it sets the current pointer to the matching node.
// If not found it returns a failure and sets the current pointer to the node just before the
// insertion point (by alphabetic order). Note the special case for a new word that goes at the
// beginning of the list. See the examples below.
//
// Hint: use strcmp to determine sorting order.
//
// If it is found the current pointer is set to the node containing the matching word.
// If it is found this function returns a 1 to indicate success.
//
// If it is not found the current pointer is set to the node just before the insertion point.
// If it is not found the function returns a 0 to indicate failure.
// e.g. the list contains the words "apple", "buy", "cat".
//      Searching for "baby" would set current to the node containing "apple".
//      Searching for "acid" would set current to NULL to indicate that "acid" belongs at the head.
//      searching for "zebra" would set current to the node containing "cat".
//
// Tests on p_list and word: p_list, p_list->head, and word must all not be NULL.
// In addition, word must not be an empty string.
// We must have a valid list with at least one node and we must a valid word to match.
// If any of these conditions are violated this function returns a -1 to indicate invalid input.
int find_word( struct linked_list *p_list, char *word ) {
	if (p_list == NULL || word == NULL || *word == '\0' || p_list-> p_head == NULL ) { // if p_list or word is null, the word is empty or the linked list is empty
        return -1; // No changes have been made to the linked_list
    }

	struct node* head = p_list -> p_head;
	
	while(head != NULL) {
		int compareTo = strcmp(word, head -> one_word.unique_word); // sorting

		if(compareTo == 0) {
			p_list -> p_current = head; // make current the head
			return 1;
		} else {
			if(compareTo < 0) { // less than
				p_list -> p_current = head -> p_previous; // make current the previous
				return 0;
			} else { // greater than
				head = head -> p_next; // replace head with the next value of itself
			}
		}
	}

	p_list -> p_current = p_list -> p_tail; // make current the tail

	return 0;
}

