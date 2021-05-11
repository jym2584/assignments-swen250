// C pointers Practice Practicum
// SWEN-250
// unit_tests
// Larry Kiser October 30, 2015
// Larry Kiser updated July 6, 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "cpractice2.h"
#include "unit_tests.h"

// Simple boolean assert function for unit testing
int assert( int test_result, char error_format[], ... ) {
	va_list arguments ;
	static int test_number = 1 ;
	int result = 1 ;	// return 1 for test passed or 0 if failed
	
	if ( ! test_result ) {
		va_start( arguments, error_format ) ;
		printf( "Test # %d failed: ", test_number ) ;
		vprintf( error_format, arguments ) ;
		printf( "\n" ) ;
		result = 0 ;
	}
	test_number++ ;
	return result ;
}

//////////////////////////////////////////////////////////////////////////
// Begin unit tests //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// do the unit tests
int test()
{
	int passcount = 0 ;
	int failcount = 0 ;
	char bad_code_string[] = "badcode" ;
	char updated_bad_code_string[] = "badcodZ" ;
	
	printf( "\nTests for get_pointer_at_position...................\n" ) ;
	char *test1 = "findfinstring" ;

	// Test 1
	assert( get_pointer_at_position( test1, 0 ) == test1,
		"Expected pointer to the beginning of the string" )
		? passcount++ : failcount++ ;
	// Test 2
	assert( get_pointer_at_position( test1, 4 ) == test1 + 4,
		"Expected pointer at position 4" )
		? passcount++ : failcount++ ;
	// Test 3
	assert( get_pointer_at_position( test1, 12 ) == test1 + 12,
		"Expected pointer to last character" )
		? passcount++ : failcount++ ;
	// Test 4
	assert( get_pointer_at_position( test1, 14 ) == NULL,
		"Expected NULL pointer because 14 is past the end of the string" )
		? passcount++ : failcount++ ;
	
	printf( "\nTests for get_y_values...........................\n" ) ;
	int xvalues1[] = { 0, 5, 2 } ;
	int xvalues_saved[] = { 0, 5, 2 } ;
	int yvalues1[] = { -1, 9, 3 } ;
	int *calculated_y_values ;

	// Test 5
	calculated_y_values = get_y_values( NULL, 2, -1, 3 ) ;
	assert( calculated_y_values == NULL,
		"Expected NULL pointer because x array pointer is NULL" )
		? passcount++ : failcount++ ;
	
	// Test 6
	calculated_y_values = get_y_values( xvalues1, 2, -1, 0 ) ;
	assert( calculated_y_values == NULL,
		"Expected NULL pointer because number_of_x_values is 0" )
		? passcount++ : failcount++ ;
	
	// Test 7
	calculated_y_values = get_y_values( xvalues1, 2, -1, 3 ) ;
	if ( calculated_y_values < (int *)1000 )		// avoid bogus pointer value crashes
	{
		// force the assert to fail to report a bad pointer
		assert( 0,
			"Bad calculated_y_values pointer!")
			? passcount++ : failcount++ ;
	}
	else
		assert( memcmp( calculated_y_values, yvalues1, sizeof(yvalues1) ) == 0,
			"Returned array must match the expected values in yvalues1[]" )
			? passcount++ : failcount++ ;
			
	// Test 8
	assert( memcmp( xvalues_saved, xvalues1, sizeof( xvalues_saved ) ) == 0,
		"get_y_values function corrupted xvalues1 array" )
		? passcount++ : failcount++ ;

	printf( "\nTests for get_sum_and_free_space................................\n" ) ;
	// Test 9
	assert( get_sum_and_free_space( NULL, 3 ) == 0,
		"Expect 0 since the py pointer is NULL" )
		? passcount++ : failcount++ ;
		
	// Test 10 -- xvalues1 is the incorrect array but is ignored because the count is 0.
	assert( get_sum_and_free_space( xvalues1, 0 ) == 0,
		"Expect 0 since the number_of_y_values is 0" )
		? passcount++ : failcount++ ;
		
	// Test 11
	int result = get_sum_and_free_space( calculated_y_values, 3 ) ;
	assert( result == 11,
		"Expect 11 since the number_of_y_values is 11 but got %d", result )
		? passcount++ : failcount++ ;
		
	printf( "\nTests for same_array................................\n" ) ;
	
	// Test 12
	assert( same_array( xvalues1, xvalues1 ) == 1,
		"Expect 1 since it is the same array" )
		? passcount++ : failcount++ ;
	// Test 13
	assert( same_array( xvalues1, &xvalues1[1] ) == 0,
		"Expect 0 since a different position in the array" )
		? passcount++ : failcount++ ;
	// Test 14
	assert( same_array( NULL, xvalues1 ) == 0,
		"Expect 0 since one is NULL" )
		? passcount++ : failcount++ ;
	// Test 15
	assert( same_array( xvalues1, NULL ) == 0,
		"Expect 0 since 2nd is NULL" )
		? passcount++ : failcount++ ;
		
	printf( "\nTests for bool_flip_flop............................\n" ) ;
	// Test 16
	assert( bool_flip_flop() == 1,
		"Expect 1 this is the first time it is called" )
		? passcount++ : failcount++ ;
	// Test 17
	assert( bool_flip_flop() == 0,
		"Expect 0 this is the second time it is called" )
		? passcount++ : failcount++ ;
	// Test 18
	assert( bool_flip_flop() == 1,
		"Expect 1 this is the third time it is called" )
		? passcount++ : failcount++ ;
	// Test 19
	assert( bool_flip_flop() == 0,
		"Expect 0 this is the fourth time it is called" )
		? passcount++ : failcount++ ;
		
	printf( "\nTests for fix_bad_code..............................\n" ) ;
	// Test 20
	assert( fix_bad_code(bad_code_string) == 1,
		"Expect 1 since it is not any empty string" )
		? passcount++ : failcount++ ;
	// Test 21
	assert( strcmp( bad_code_string, updated_bad_code_string ) == 0,
		"Expect Z in last position of bad_code_string but got this string %s", bad_code_string )
		? passcount++ : failcount++ ;
		
	printf( "\nSummary of unit tests:\n%d tests passed\n%d tests failed\n\n", passcount, failcount ) ;
	
	return failcount ;
}
