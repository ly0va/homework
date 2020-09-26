/*
* FILE :          assessGrade.h
* PROJECT :       PROG1385 - Assignment #1b
* PROGRAMMER :    Potomkin Lev
* FIRST VERSION : 11.01.2019
* DESCRIPTION :
*   Contains prototypes of functions used parse input and to
*   assess grades given a string / double /array of ints.
*   Impletentaions found in assessGrade.cpp
*/

#define KILOBYTE 1024
#define TOTAL_INT_GRADES 5
#define MIN_PASS_GRADE 54.5 // This was in the requirement!! Not 54.495!
#define MIN_GRADE 0
#define MAX_GRADE 100
#define TOTAL_TYPES 3
#define TOTAL_TESTS 33

char* assessGrade(int[]);
char* assessGrade(double);
char* assessGrade(char*);
char* readAndHandle();

