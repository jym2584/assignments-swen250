#include <stdlib.h>
#include <stdio.h>

/*This is a comment*/

/*  "gcc -o OUTPUTFILENAME intro.c"  */
/*  "./OUTPUTFILENAME"  */

int main () {
    puts("Hello, world!");

    printf("Hello prinf world\n");
    printf("%s\n", "Hello %s");
    int i = 5;
    printf("Value of i is %d\n", i); // %d = decimal

    if (i > 5) {
        printf("It's big\n");
    } else {
        printf("It's small\n");
    }

    for (int i = 0; i < 5; i++) { // or (int i; i < 2; i += 2)
        printf("I = %d\n", i);
    }

    return 0;
}