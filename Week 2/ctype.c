#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(){
    int tot_punct = 0; // declar & initialize a local variable
    int nchar; // next character read
    
            // read 1 character at a time until we reach no characters
    while ((nchar = getchar()) != EOF);
        if(ispunct(nchar)) {
            ++tot_punct;
        }
    }
    printf("%d punctuation characters\n", tot_punct);
    return 0;
}