#include <stdio.h>

int main(){
    int twenty = 20;
    int thirty = 30;
    int *pInt;

    printf("Twenty %d\n", twenty);
    
    pInt = &twenty;
    printf("Twenty pointerInt %d\n", pInt);
    *pInt = 100;

    printf("pointerInt %d\n", *pInt);
    return 0;
}