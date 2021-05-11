#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
// assuming we are reading and processing lines of text, where at the most the first 80 characters of a line are useful

// declare an array to hold the line as a string
#define MAXLINE (80)
char line[ MAXLINE + 1 ];

// how would we read in such a line
void readline( char line[], int maxsize) {
    int i = 0;
    int ch;

    for ( ch = getchar(); ch != '\n' && ch != EOF; ch = getchar() ) {
        if (i < maxsize) {
            line[i++] = ch; // storing line in array
        }
    } 
    line[i] = '\0'; // null character, only way for the C language to end 
    return;
}

void strcpy(char sto[], char sfrom[]) {
    int i;
    for (i = 0; sto[i] = sfrom[i]; ++i)
        ; // sto[i] = sfrom[i]: copy the ith character, if this was a NUL, exit the loop
}

/// String library
#include <string.h>
strlen("Hello") // length of 5
void strcpy( char sto[], charsfrom[]);
void strncopy (char sto[], char sfrom[], unsigned n);
    // Copies n characters to sto from sfrom padding with \0 as necessary
    // if sfrom is too long to fit in sto, then sto will NOT be NUL terminated

int strcmp (char str1[], char str2[]);
    // comparison is in dictionary order
    // returns -1, 0,  if str1 is less than, equal to, or greater than str2, respectively


// wc utility

// wc < DarkAndStormyNight.txt : pushing text file into standard in (to wc)