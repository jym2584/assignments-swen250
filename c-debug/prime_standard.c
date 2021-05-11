#include <stdio.h>
#include <stdbool.h>

int main() {
    int i;                                  /* Iterating from i to the defined upper_bound */
    int j;                                  /* Checking from i to half the current number */
    bool is_prime;                          /* True/False value if the current number is prime */
    int upper_bound;                        /* Our bounds from 2 to the input value */

    printf("Enter upper bound: ");
    scanf("%d", &upper_bound);
  
    for (i = 2; i <= upper_bound; i++) {    /* Iterating from 2 to the input value */
        is_prime = true;                    /* set prime to true for every number we iterate, up to the input number */

        for (j = 2; j <= i/2; j++) {        /* Checking to see if the number i as we iterate by 1 up to upper_bound, is divisible by 0 */
            if (i % j == 0) {
                is_prime = false;           /* Set prime to false */
                break;  
            }
        }  
  
        if (is_prime) {                     /* Print that the number is prime if is_prime has been untouched by our divisible by 0 conditional*/
            printf("%d is a prime number.\n", i);  
        }  

    }  

    return 0; 
}