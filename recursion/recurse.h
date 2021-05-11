#include <stdio.h>
#include <stdbool.h>

typedef struct node
{
    char word[128];
    struct node* next;
} node;


bool isPalindrome_iterate(char* str);

bool isPalindrome_recurse(char* str);

int sum_of_numbers(int);

node* find(node* node, char* word);

// helper funtion
bool str_splice(char* str, int start, int end);
