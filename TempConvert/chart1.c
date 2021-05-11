#include <stdlib.h>
#include <stdio.h>

/*  "gcc -o OUTPUTFILENAME intro.c"  */
/*  "./OUTPUTFILENAME"  */

int main () {
    int i;
    puts("Fahrenheit-Celsius");
    for (i = 0; i <= 300; i += 20) {
        int temp = (i - 32) * 5/9;
        if (i >= 100) {
            printf("    %d      %d\n", i, temp);
        } else {
            if (temp > -10 && temp < 0) {
                printf("    %d       %d\n", i, temp);
            } else {
                printf("    %d       %d\n", i, temp);
        }
    }
    }
    return 0;
}