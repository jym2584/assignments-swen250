void 

void strappend_a(char to[], char from[]) {
    int idx = 0;

    while (to[idx++] ) {
        idx--;
        int idx2 = 0;
        while ( (to[idx] = from[idx2])) {
            idx++;
            idx2++;
        }
    }
}


int main() {

    char my_to[128];
    strcpy(my_to, "1234");
    strappend_a(my_to, "5678");
    printf("To is now %s\n", my_to);
    strcpy("abcd", "defg"); // Reserves memory for "abcd" along with \0 character (5 bytes)
                            // but because it is a quoted string, it is supposed to be a constant pointer (not supposed to be able to change it)
                            // trying to change this constant pointer and we will not let you do that (results in Segmentation Fault)
    printf("To is now%s\n", to);



}