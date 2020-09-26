/*
* FILE :          assign1.cpp
* PROJECT :       PROG1385 - Assignment #1b
* PROGRAMMER :    Potomkin Lev
* FIRST VERSION : 11.01.2019
* DESCRIPTION :
*   Main file for the assignment. Assesses grades based on
*   the input from stdin until 'X' is read.
*/

#include "assessGrade.h"
#include <stdio.h>

int main() {
    char* output = NULL; // holds a string to print
    int terminate = 0;  // does the user want terminate the program?
    do {
        printf("\nEnter student's grade >> "); // prompt
        output = readAndHandle();  // parse input and return output
        if (*output != 0) {
            // string is not empty, continue
            puts(output);
        } else {
            // user wants to terminate
            terminate = 1;
        }
        delete[] output;  // free memory
    } while(!terminate);
    return 0;
}

