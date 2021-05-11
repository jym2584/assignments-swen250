#include <stdlib.h>
#include <stdio.h>

/*  "gcc -o OUTPUTFILENAME intro.c"  */
/*  "./OUTPUTFILENAME"  */

int main () {
    float i;
    puts("Fahrenheit-Celsius");
    for (i = 0; i <= 300; i += 20) {
        float temp = (i - 32) * 5/9;
        if (i > 10 && (i < 100)) {
            printf("    %.0f", i);
            printf("%*.1f\n", 11, temp);
        } else if (i >= 100) {
            printf("   %.0f", i);
            printf("%*.1f\n", 11, temp);
        } else {
            printf("     %.0f", i);
            printf("%*.1f\n", 11, temp);
        }
    }

    return 0;
}