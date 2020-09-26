/*
* FILE : hashing.c
* PROJECT : Mini Lab 2
* AUTHOR : Potomkin Lev
* DATE : 30.01.2019
* DESCRIPTION : 
*   This file contains an implementation of a simple hash function.
*   Main function performs tests on 3 different files.
*
*
* PSEUDOCODE : 
*
*   function hash(string):
*       digest := 0
*       for each character in string:
*           digest := (digest + ascii value of character) mod 256
*       return digest
*
*   function main():
*       for each file:
*           if file exists:
*               string := file content
*               digest := hash(string)
*               print digest
*           else:
                print error
*/

#include <stdio.h>
#define TOTAL_FILES 3
#define MAX_SIZE 1024

int hash(char* string, int length);

// files for testing
const char* files[TOTAL_FILES] = {"test.dat", "test2.dat", "test3.dat"};

int main(void) {
    int digest = 0;
    int length = 0;
    char buffer[MAX_SIZE];

    for (int i = 0; i < TOTAL_FILES; i++) {
        FILE* file = fopen(files[i], "rb"); // binary mode
        if (file != NULL) {
            // assuming size of file < 1K
            length = fread(buffer, 1, MAX_SIZE, file); 
            digest = hash(buffer, length);
            printf("Digest of %s: %d\n", files[i], digest);
            fclose(file);
        } else {
            // File doesn't exist
            printf("File %s not found :(\n", files[i]);
        }
    }

    return 0;
}

/*
* FUNCTION : hash
* DESCRIPTION : 
*   Calculates a simple hash function on a string.
* PARAMETERS : 
*   char* string : a string to be taken hash of
*   int length : legnth of a given string
* RETURNS :
*   int : hash value of a given string
*/
int hash(char* string, int length) {
    char digest = 0;
    for (int i = 0; i < length; i++) {
        digest += string[i]; // mod 256 performed implicitly
    }
    return digest;
}