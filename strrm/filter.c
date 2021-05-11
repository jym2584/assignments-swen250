#include <stdio.h>


void remove_all_chars(char* str, char c) {
    char *pr = str;
    char *pw = str;

    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}

int main() {
    char str[] = "llHello, world!ll";
    remove_all_chars(str, 'l');
    printf("'%s'\n", str);
    return 0;
}