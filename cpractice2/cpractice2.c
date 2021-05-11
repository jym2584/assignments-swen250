// C pointers Practice Practicum
// SWEN-250
// Larry Kiser October 30, 2015
// Larry Kiser updated July 6, 2017

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cpractice2.h"
#include "unit_tests.h"

// return a pointer to the character that is at the passed position.
// return a null if the requested position is past the end of the string.
// Hint -- to solve this you need to do some simple pointer math. You are allowed to use string functions.
// Parameters:
//		*pstring is a character pointer to a typical string.
//		position is zero based index into the string/
char *get_pointer_at_position( char *pstring, int position ) {
	/*
	int count = 0;
	while (*pstring != '\0') {
		if(count == position) {
			return pstring;
		}
		count++;
		pstring++;
	}
	
	return NULL;
	*/
	if (position >= strlen(pstring)) {
		return NULL;
	}
	return pstring + position;
}

// Convert array of integer x values into an array of y values using y = mx + b where m and b are constants
// passed to the function.
// You must return an array of y values. This array must be stored on the heap.
// Only create this array of y values if you have a valid px pointer and valid number_of_x_values
//     as described below.
// You must not modify the array of x values.
// The m and b integer constants can be positive, negative or zero.
// Return NULL if the passed in px pointer is NULL or if the number_of_x_values is <= 0.
// Parameters:
//		*px is a pointer to an array of x values.
//		m is the integer slope
//		b is the integer offset.
//		number_of_x_values is the number of entries in the array of x values

			// Array,    rest are integers
int *get_y_values( int *px, int m, int b, int number_of_x_values ) {
	if(px == NULL || number_of_x_values <= 0) {
		return NULL;
	}

	int *py = malloc(sizeof(int) * number_of_x_values); // have enough memory to have number_of_x_values integers into the array (technically an array)
	int *wpy = py; // copy of py (start of array)
	int *wpx = px; // copy of px (start of array)

	int i;
	for(i = 0; i < number_of_x_values; i++) {
		//*wpy = *wpx * m + b;
		py[i] = px[i] * m + b;
		wpy++;
		wpx++;
	}

	return py;		// Fix this -- it is incorrect but allows the program to compile and run.
}

// Adds up the number of integers in the passed py array.
// The number of integers is in number_of_y_values.
// If py is a NULL pointer you must return 0.
// if number_of_y_values is <= 0 you must return 0.
// if py is space that was allocated on the heap you must free that space in this function.
// However, only free the py space if the number_of_y_values is > 0.
int get_sum_and_free_space( int *py, int number_of_y_values ) {
	if(py == NULL || number_of_y_values <= 0) {
		return 0;
	}
	int *wpy = py; // copy of py;
	int sum = 0;
	for(int i = 0; i < number_of_y_values; i++) {
		//sum += py[i];
		sum += wpy[i];
		//sum += *wpy;
		// wpy++;
	}

	free(py); // freeing the memory on py now
	return sum;
}

// Determine if two pointers point to the same array of numbers
// return 1 if they do, return 0 otherwise.
// return 0 if either pointer is NULL.
// This is testing your understanding of what is actually contained in a pointer.
int same_array( int *pfirst, int *psecond ) {
	if (pfirst == NULL || psecond == NULL) {
		return 0;
	}
	if (pfirst == psecond) {
		return 1;
	}
	return 0;
}

// The first time this is called return 1.
// The second time this is called return 0.
// Continue this pattern returning 1, then 0, then 1 and so on.
int bool_flip_flop() {
	static int flipped = 0;
	if(flipped == 0) {
		flipped = 1;
		return 1;
	} else {
		flipped = 0;
		return 0;
	}
}

// This function is implemented incorrectly. You need to correct it.
// When fixed it changes the last character in the passed string to 'Z'.
// It returns returns 1 on success.
// It returns 0 on if the passed string is NULL or an empty string.
int fix_bad_code( char *pstring ) {
	/*
	if (*pstring == '\0' || pstring == NULL) {
		return 0;
	}

	while (*pstring != '\0') {
		pstring++;
	}
	pstring--;
	*pstring = 'Z';
	
	return 1;
	*/
	if (*pstring == '\0' || strlen(pstring) == 0) {
		return 0;
	}
	
	while ( *pstring != '\0' ) {
		if((strlen(pstring)-1) == 0) {
			*pstring = 'Z'; //
			return 1;
		}
		pstring++;
	}
	return 0;
}
