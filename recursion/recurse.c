#include "recurse.h"
#include <string.h>
#include <stdlib.h>

// Iterative function to check if the given string is a palindrome or not
// Parameters:
// char *str: This is the string to be checked.  Assume it is a valid string
//          - If it is a palindrome (same string forward and backward), 
//            then return true, else return false
// Returns true if 'str' is a palindrome, else returns false
// Use a loop to check for a palindrome, do not use recursion!
bool isPalindrome_iterate(char* str) {
    for(int i = 0; i < strlen(str) - 1; i++) {
        if(str[i] != str[(strlen(str)-1) - i]) {
            return false;
        }
    }


    return true; //Replace this - just allows compile to work
}




// Recursive function to check if the string is a palindrome
// Parameters:
// char* str: The string to check
// returns true if 'str' is a palindrome, else returns false
// NOTE: There are several ways to solve using recursion.
// You may use an intermediate function to assist with the solution
//  i.e. set up the logic, then call another function
bool isPalindrome_recurse(char* str) {
    return str_splice(str, 0, strlen(str)-1);

}

// Trims the first and last character of the string
// eg: passing in racecar
// returns: aceca
bool str_splice(char* str, int start, int end) {
    if (start == end) {
        return 1;
    }
    
    if (str[start] == str[end]) {
        start += 1;
        end -= 1;
        return str_splice(str, start, end);
    } else {
        return 0;
    }

}


//Use recursion to add up N numbers
//For example, if 'how_many' is 5, you would end up adding 5 + 4 + 3 + 2 + 1
//Do not use a loop!!
//Parameters: int how_many: How many numbers to add
//Returns: Sum of the added numbers
int sum_of_numbers(int how_many) {
    if (how_many <= 1) {
        return how_many;
    }

    return how_many + sum_of_numbers(how_many - 1);
}

//Using recursion, find a matching node in a linked list
//Parameters:
// node* node: This is the first node in the linked list.
// char* word: This is the word in the node you need to look for.
// Returns: If the word is found, return the node, else return NULL

node* find(node* node, char* word) {
     if (strcmp(node->word, word) == 0){
        return node;
    }
    
    if (node->next != NULL) {
        return find(node->next, word);
    }
    
    return NULL;//Replace this - just allows compile to work
}
