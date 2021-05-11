#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

/**
 * Gets the contents of the file
 * @param filename filename
 * @return file contents
*/
char* get_contents_from_file(char *filename) {
    if (filename == NULL || *filename == '\0') {
        return NULL;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;

    } else {
        int MAX_CHARS = 3000;
        char *get_contents = malloc(MAX_CHARS); // allocates memory up to some limit
        char *contents_temp = get_contents; // retains the memory address of the first character
        
        int ch;
        int i = 0;

        while ((ch = fgetc(file)) != EOF) { // read the file
            *get_contents = (char)ch;
            get_contents++;
        }

        get_contents[i] = '\0';

        get_contents = malloc(strlen(contents_temp) + 1); // allocate memory for new get_contents now
        strcpy(get_contents, contents_temp); // Copy the contents from contents_temp to get_contents
        free(contents_temp); // free unused variable

        return get_contents;
    }
}

/**
 * Encrypts each character of the string
 * @param string an array of characters
 * @return encrypted string
 */
char* encrypt(char* string) {
    for(int i = 0; string[i] != '\0'; i++) {
        string[i] = string[i] + 100;
    }

    return string;
}

/**
 * Decrypts each character of the string
 * @param string an array of characters
 * @return decrypted string
 */
char* decrypt(char* string) {
    for(int i = 0; string[i] != '\0'; i++) {
        string[i] = string[i] - 100;
    }

    return string;
}

/**
 * Rewrites contents from file into a new file
 * @param filename filename
 * @param selection e for encrypt, d for decrypt
 * @return 1 if operation is successful
 */
int overwrite(char* filename, char* selection) {
    if (filename == NULL || *filename == '\0') {
        return 0;
    }

    char *filename_no_ext = malloc(strlen(filename + 5)); // allocates size for the filename without the extension, saves room for NUL character
    char *no_ext_copy = filename_no_ext;

    /** Get the filename (without extension) */
    for(int i = 0; i < strlen(filename); i++) {
        if(filename[i] == '.') {
            *filename_no_ext = '\0';
            break;
        } else {
            *filename_no_ext = filename[i];
            filename_no_ext++;
        }
    }

    filename_no_ext = malloc(strlen(no_ext_copy) + 1); // allocate memory for new filename_no_ext now
    strcpy(filename_no_ext, no_ext_copy); // Copy the contents from no_ext_copy to filename_no_ext 
    free(no_ext_copy); // free unused variable

    /** Get selection **/
    if(selection[1] =='e') {
        FILE *new_file = fopen(strcat(filename_no_ext, "_enc.txt"), "w+"); // re-write the entire file
        char *encrypted = encrypt(get_contents_from_file(filename)); // gets encrypted message

        for(int i = 0; i < strlen(encrypted); i++) {
            fputc(encrypted[i], new_file); // appends encrypted message to new file
        }

        fclose(new_file);
        return 1;

    } else if (selection[1] =='d') {
        FILE *new_file = fopen(strcat(filename_no_ext, "_dec.txt"), "w+"); // re-write the entire file
        char * decrypted = decrypt(get_contents_from_file(filename)); // gets decrypted message

        for(int i = 0; i < strlen(decrypted); i++) {
            fputc(decrypted[i], new_file); // appends decrypted message to new file
        }

        fclose(new_file);
        return 1;
    }


    return 0;

}


int main(int argc,char* argv[]) {
    if(argc == 3) {
        char* selection = argv[1]; 
        char* filename = argv[2];
    
        if (overwrite(filename, selection) == 1) {
            return 0;
        }

    }

    printf("Usage:\nfilesec -e|-d [filename]");
    return 0;
}
