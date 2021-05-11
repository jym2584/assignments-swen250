// unit_tests.c
// Larry Kiser October 30, 2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "cpractice1.h"
#include "unit_tests.h"

// Simple boolean assert function for unit testing
int assert( int test_result, char error_format[], ... ) {
    va_list arguments ;
    static int test_number = 1 ;
    int result = 1 ;    // return 1 for test passed or 0 if failed
    
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
    int result ;
    
    // Tests for skip_spaces function
    printf( "\n----------------------- Test the skip_spaces function -------------------------\n" ) ;
    
    // Test 1 -- 
    // 3. If mystring[ start_index ] is an end of string then return -1.
    result = skip_spaces( "", 0 ) ;
    assert( result == -1,
        "skip_spaces must return -1 on an empty string but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 2 -- 
    // 1. If mystring[ start_index ] is a letter it returns the value of start_index.
    result = skip_spaces( "abc", 0 ) ;
    assert( result == 0,
        "skip_spaces must return 0 if the index points to a letter but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 3 -- 
    // 2. If mystring[ start_index ] is a space then it moves to the next position
    //    until it either sees the end of the string or it sees a letter.
    //    If no letter is found it returns a -1 to indicate no letter found.
    result = skip_spaces( " abc", 0 ) ;
    assert( result == 1,
        "skip_spaces must return 1 since that is the position of the first letter but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 4 -- 
    // 2. If mystring[ start_index ] is a space then it moves to the next position
    //    until it either sees the end of the string or it sees a letter.
    //    If no letter is found it returns a -1 to indicate no letter found.
    result = skip_spaces( "    abc", 0 ) ;
    assert( result == 4,
        "skip_spaces must return 4 since there are 4 leading spaces but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 5 -- 
    // 1. If mystring[ start_index ] is a letter it returns the value of start_index.
    result = skip_spaces( "    abc  x", 5 ) ;
    assert( result == 5,
        "skip_spaces must return 5 since position 5 is the letter b but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 6 -- 
    // 2. If mystring[ start_index ] is a space then it moves to the next position
    //    until it either sees the end of the string or it sees a letter.
    //    If no letter is found it returns a -1 to indicate no letter found.
    result = skip_spaces( "    abc  x", 7 ) ;
    assert( result == 9,
        "skip_spaces must return 9 since position 7 and 8 are spaces but it returned %d", result )
        ? passcount++ : failcount++ ;
    
    // Tests for find_next_word
    printf( "\n----------------------- Test the find_next_word function ----------------------\n" ) ;
    
    // Test 7 -- 
    // 3. If mystring[ start_index ] is an end of string return a -1.
    result = find_next_word( "", 0 ) ;
    assert( result == -1,
        "find_next_word must return -1 if it is an empty string but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 8 -- 
    // 1. If mystring[ start_index ] is a letter it searches for the first space.
    //    If it finds a space it skips spaces searching for a letter.
    //    If a letter is found it returns this letter's index position since this is the beginning of the next word.
    //    If no letter is found it returns a -1.
    result = find_next_word( "word", 0 ) ;
    assert( result == -1,
        "find_next_word must return -1 because there is no next word but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 9 -- 
    // 1. If mystring[ start_index ] is a letter it searches for the first space.
    //    If it finds a space it skips spaces searching for a letter.
    //    If a letter is found it returns this letter's index position since this is the beginning of the next word.
    //    If no letter is found it returns a -1.
    result = find_next_word( "word next", 0 ) ;
    assert( result == 5,
        "find_next_word must return 5 for the position of letter n but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 10 -- 
    // 2. If mystring[ start_index ] is a space it searches until it either sees
    //    the end of the string or it sees a letter.
    //    If no letter is found it returns a -1.
    result = find_next_word( "word    next", 4 ) ;
    assert( result == 8,
        "find_next_word must return 8 for the position of letter n but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 11 -- 
    // 2. If mystring[ start_index ] is a space it searches until it either sees
    //    the end of the string or it sees a letter.
    //    If no letter is found it returns a -1.
    result = find_next_word( "word    ", 4 ) ;
    assert( result == -1,
        "find_next_word must return -1 because there are no letters after position 4 but it returned %d", result )
        ? passcount++ : failcount++ ;
    
    // Test change_to_upper function
    printf( "\n----------------------- Test the change_to_upper function ---------------------\n" ) ;
    
    // Test 12 -- 
    // 1. If mystring[ index ] is an upper case letter, a space, or an end of string it makes no change.
    //    This function returns 0 when it makes no change.
    result = change_to_upper( "", 0 ) ;
    assert( result == 0,
        "change_to_upper must return 0 on an empty string but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 13 -- 
    // 1. If mystring[ index ] is an upper case letter, a space, or an end of string it makes no change.
    //    This function returns 0 when it makes no change.
    result = change_to_upper( " ", 0 ) ;
    assert( result == 0,
        "change_to_upper must return 0 on a space but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 14 -- 
    // 1. If mystring[ index ] is an upper case letter, a space, or an end of string it makes no change.
    //    This function returns 0 when it makes no change.
    result = change_to_upper( "T", 0 ) ;
    assert( result == 0,
        "change_to_upper must return 0 on an upper case letter but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 15 -- 
    // 2. This function returns a 1 only when it changes a lower case letter to an upper case letter.
    char lowercasearray[] = "abc" ;
    result = change_to_upper( lowercasearray, 0 ) ;
    assert( result == 1,
        "change_to_upper must return 1 on a lower case letter but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 16 -- 
     assert( strcmp( lowercasearray, "Abc" ) == 0,
        "change_to_upper should change string to Abc but it produced string %s", lowercasearray )
        ? passcount++ : failcount++ ;
    
    // Test capitalize_all_words
    printf( "\n----------------------- Test the capitalize_all_words function ----------------\n" ) ;
    
    // Test 17 -- 
    // If mystring[] is an empty string it returns 0.
    result = capitalize_all_words( "" ) ;
    assert( result == 0,
        "capitalize_all_words must return 0 on an empty string but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 18 -- 
    result = capitalize_all_words( "" ) ;
    assert( result == 0,
        "capitalize_all_words must return 0 on an empty string but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 19 -- 
    char test[] = "test" ;
    result = capitalize_all_words( test ) ;
    assert( result == 1,
        "capitalize_all_words must return 1 for a single uncapitalized word but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 20 -- 
    char oneword[] = "  word" ;
    result = capitalize_all_words( oneword ) ;
    assert( result == 1,
        "capitalize_all_words must return 1 for a single uncapitalized word with leading spaces but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 21 -- 
    char mixedarray[] = "The first word" ;
    result = capitalize_all_words( mixedarray ) ;
    assert( result == 2,
        "capitalize_all_words must return 2 because it only capitalized two words but it returned %d", result )
        ? passcount++ : failcount++ ;
       
    // Test 22 -- 
    assert( strcmp( mixedarray, "The First Word" ) == 0,
        "capitalize_all_words change the string to The First Word but it produced %s", mixedarray )
        ? passcount++ : failcount++ ;
        
    printf( "\n----------------------- Test the fix_bad_code function ------------------------\n" ) ;
	// Test 23 -- 
	assert( fix_bad_code( 0, 0 ) == 0,
		"fix_bad_code expected 0 for two equal values" )
		? passcount++ : failcount++ ;
		
	// Test 24 -- 
	assert( fix_bad_code( 6, 5 ) == 1,
		"fix_bad_code expected 1 because 6 > 5" )
		? passcount++ : failcount++ ;
		
	// Test 25 -- 
	assert( fix_bad_code( 3, 5 ) == -1,
		"fix_bad_code expected -1 because 3 is < 5" )
		? passcount++ : failcount++ ;
		
    printf( "\nSummary of unit tests:\n%d tests passed\n%d tests failed\n\n", passcount, failcount ) ;
    
    return failcount ;
}