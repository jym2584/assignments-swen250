#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "recurse.h"

static void summary() ;
static bool assert_impl(bool expr, char *f_name, int f_line, char *message) ;
static bool assert_eql_impl(
	bool want, bool have, char *f_name, int f_line, char *message) ;

/*
 * Macros so we don't have to explicitly pass filenames and line numbers
 * for each assertion.
 */
#define assert(e, m) assert_impl(e, __FILE__, __LINE__, m)
#define assert_eql(w, h, m) assert_eql_impl((w), (h), __FILE__, __LINE__, (m))

/*
 * Macro to determine whether of not to strings are equal.
 */
//#define streql(a, b) (strcmp((a), (b)) == 0)

/*
 * Number of tests, number of assertions passed, number of assertions failed.
 */
static int ntests = 0 ;
static int npass = 0 ;
static int nfail = 0 ;

void palindrome_tests( bool (*testFunction)(char*));
void list_tests(node*);
void sum_tests();


int main(int ac, char **argv) {
    bool pass = true;
	fprintf(stderr, "** Tests of palindrome **\n") ;
    printf("Testing iterative method\n");
    palindrome_tests(isPalindrome_iterate);
    printf("\nTesting recursive method\n");
    palindrome_tests(isPalindrome_recurse);
    printf("\nRecursive addition tests\n");
    sum_tests();

    node* nodeList ;
    node* n0 = malloc(sizeof(node)); strcpy(n0->word, "one");
    node* n1 = malloc(sizeof(node)); strcpy(n1->word, "giant"); n0->next = n1;
    node* n2 = malloc(sizeof(node)); strcpy(n2->word, "leap"); n1->next = n2;
    node* n3 = malloc(sizeof(node)); strcpy(n3->word, "for"); n2->next = n3;
    node* n4 = malloc(sizeof(node)); strcpy(n4->word, "human-kind"); n3-> next = n4;
    n4->next = NULL; nodeList = n0;
    printf("\nRecursive 'find' tests\n");
    list_tests(nodeList);
    node* p_node = nodeList;
    while (p_node)
    {
        node* next = p_node->next;
        free(p_node);
        p_node = next;
    }
    printf("\n");
    summary();
}

void sum_tests()
{
    bool pass = true;
    pass = assert(sum_of_numbers(3)==6,  "Looking for '6'") && pass ; ntests++;
    pass = assert(sum_of_numbers(4)==10,  "Looking for '10'") && pass ; ntests++;
    pass = assert(sum_of_numbers(5)==15,  "Looking for '15'") && pass ; ntests++;
    pass = assert(sum_of_numbers(6)==21,  "Looking for '21'") && pass ; ntests++;
    pass = assert_eql(sum_of_numbers(30),6,  "Looking for 'one'") && pass ; ntests++;
/*    printf("Sum of 3 is %d\n",sum_of_numbers(3));
    printf("Sum of 4 is %d\n",sum_of_numbers(4));
    printf("Sum of 5 is %d\n",sum_of_numbers(5));
    printf("Sum of 6 is %d\n",sum_of_numbers(6));
    */

}

void list_tests(node* nodeList)
{
    bool pass = true;
    ntests++;
    node* p_result = find(nodeList, "one");
    bool result = true;
    if (p_result == NULL || strcmp(p_result->word, "one") != 0)
        result = false;
    pass = assert_eql(true,result,  "Looking for 'one'") && pass ;

    ntests++;
    p_result = find(nodeList, "for");
    result = true;
    if (p_result == NULL || strcmp(p_result->word, "for") != 0)
        result = false;
    pass = assert_eql(true,result,  "Looking for 'for'") && pass ;

    ntests++;
    p_result = find(nodeList, "human-kind");
    result = true;
    if (p_result == NULL || strcmp(p_result->word, "human-kind") != 0)
        result = false;
    pass = assert_eql(true,result,  "Looking for 'human-kind'") && pass ;

    ntests++;
    p_result = find(nodeList, "");
    result = false;
    if (p_result == NULL )
        result = true;
    pass = assert_eql(true,result,  "Looking for empty string - should return null") && pass ;

    ntests++;
    p_result = find(nodeList, "unknown");
    result = false;
    if (p_result == NULL )
        result = true;
    pass = assert_eql(true,result,  "Looking for 'unknown' - should return null") && pass ;


}


void palindrome_tests( bool (*testFunction)(char*))
{
    bool pass = true;
    printf("Test-1: 'XYXYX'\n");
	bool result = testFunction("XYXYX") ;
    ntests++;
	pass = assert_eql(true,result,  "XYXYX is a palindrome; returned false") && pass ;

    printf("Test-2: 'XYBYBYX'\n");
    ntests++;
	result = testFunction("XYBYBYX") ;
	pass = assert_eql(true,result,  "XYBYBYX is a palindrome; returned false") && pass ;

    printf("Test-3: 'XYXYXM'\n");
    ntests++;
	result = testFunction("XYXYXM") ;
	pass = assert_eql(false ,result,  "XYXYXM is not a palindrome; returned true") && pass ;

    printf("Test-4: 'XYX1YX'\n");
    ntests++;
	result = testFunction("XYX1YX") ;
	pass = assert_eql(false,result,  "XYX1YX is not a palindrome; returned true") && pass ;

    printf("Test-5: 'able was I ere I saw elba'\n");
    ntests++;
	result = testFunction("able was I ere I saw elba") ;
	pass = assert_eql(true,result,  "able was I ere I saw elba is a palindrome; returned false") && pass ;

    printf("Test-6: 'drabasafoolaloofasabard'\n");
    ntests++;
	result = testFunction("drabasafoolaloofasabard") ;
	pass = assert_eql(true,result,  "drabasafoolaloofasabard is a palindrome; returned false") && pass ;

}



static void test_failure() {
	fprintf(stderr, "** Test failed - exiting **\n") ;
	summary() ;
	exit(1) ;
}
	
static void summary() {
	fprintf(stderr, "*** TEST SUMMARY ***\n") ;
	fprintf(stderr, "%d test%s, ",
			ntests, ntests != 1 ? "s" : "");
	fprintf(stderr, "%d assertion%s ",
			npass + nfail, npass + nfail != 1 ? "s" : "") ;
	fprintf(stderr, "(%d passed/%d failed)\n",
			npass, nfail) ;
}




static bool assert_impl(bool expr, char *f_name, int f_line, char *message) {
	if( expr ) {
		npass++ ;
		return true ;
	}

	nfail++ ;
	if( message ) {
		fprintf(stderr, "Assertion failure (%s @ %d): %s\n",
				f_name, f_line, message) ;
	} else {
		fprintf(stderr, "Assertion failure (%s @ %d)\n",
				f_name, f_line) ;
	}
	return false ;
}

static bool assert_eql_impl(bool want, bool have, char *f_name,
		int f_line, char *message) {
	if( want == have ) {
		npass++ ;
		return true ;
	}

	nfail++ ;
	fprintf(stderr, "Assertion failure (%s @ %d)\n", f_name, f_line) ; 

	if( message ) {
		fprintf(stderr, "%s\n", message) ;
	}
	fprintf(stderr, "    Want: \"%s\"\n", want?"true": "false") ;
	fprintf(stderr, "    Have: \"%s\"\n", have?"true": "false") ;
	return false ;
}



