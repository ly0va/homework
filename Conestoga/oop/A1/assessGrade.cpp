/*
* FILE :          assessGrade.cpp
* PROJECT :       PROG1385 - Assignment #1b
* PROGRAMMER :    Potomkin Lev
* FIRST VERSION : 17.01.2019
* DESCRIPTION :
*   Contains implementation of functions used parse input and to
*   assess grades given a string / double / array of ints.
*/

#include "assessGrade.h"
#include <stdio.h>
#include <string.h>

/*
* FUNCTION : assessGrade
* DESCRIPTION :
*   Based on a numeric grade, determines if a student
*   passed or failed the course and returns a verdict.
* PARAMETERS :
*   double grade : numeric grade for the course. Should be between 0 and 100
* RETURNS :
*   char* : A string verdict based on a numeric grade or an error message.
*           Has to be `delete[]`d by caller.
*/
char* assessGrade(double grade) {
    char* output = new char[KILOBYTE];
    if (grade < (double)MIN_GRADE || grade > (double)MAX_GRADE) {
        // Out of range
        sprintf(output, "ERROR! Invalid input.");
    } else {
        // Check if it is a PASS or FAIL mark
        sprintf(output, "Student achieved %.2f %% which is a %s condition.",
                grade, grade < MIN_PASS_GRADE ? "FAIL" : "PASS");
    }
    return output;
}

/*
* FUNCTION : assessGrade
* DESCRIPTION :
*   Based on numeric grades for course assignments, determines if a student
*   passed or failed the course and prints to stdout.
* PARAMETERS :
*   int grades[] : array containing 5 grades - 1 for each assignment.
*                  Each should be between 0 and 100
* RETURNS :
*   char* : A string verdict based on a array of grades or an error message.
*           Has to be `delete[]`d by caller.
*/
char* assessGrade(int grades[]) {
    double average = 0;  // holds the average
    char inRange = 1;    // are all grades in range 0..100?
    char* output = NULL;

    for (int i = 0; i < TOTAL_INT_GRADES; i++) {
        if (grades[i] < MIN_GRADE || grades[i] > MAX_GRADE) {
            inRange = 0; // Out of range
        }
        average += grades[i];
    }

    if (!inRange) {
        // out of range
        output = new char[KILOBYTE];
        sprintf(output, "ERROR! Invalid input.");
    } else {
        // divide by total and pass to assessGrade(double)
        average /= TOTAL_INT_GRADES;
        output = assessGrade(average);
    }

    return output;
}

/*
* FUNCTION : assessGrade
* DESCRIPTION :
*   Based on a letter grade, determines if a student passed
*   or failed the course, or has a special situation and prints to stdout.
* PARAMETERS :
*   char* grade : letter grade for the course or a special abbreviation
* RETURNS :
*   char* : A string verdict based on a letter grade,
*           a special situation verdict or an error message.
*           Has to be `delete[]`d by caller.
*/
char* assessGrade(char* grade) {
    char* output = NULL;
    const int NUMERIC_TOTAL = 8;  // Total letter grades
    const int SPECIAL_TOTAL = 5;  // Total special cases
    const char* stringGrades[NUMERIC_TOTAL] = {"A+", "A", "B+", "B",
                                               "C+", "C", "D", "F"};
    const int numericGrades[NUMERIC_TOTAL] = {95, 85, 77, 72, 67, 62, 57, 50};
    const char* specialGrades[SPECIAL_TOTAL] = {"I", "Q", "AU", "DNA", "I/P"};
    const char* meanings[SPECIAL_TOTAL] = {"Incomplete",
				"Withdrawal after drop/refund date",
 				"Audit", "Did not attend", "In process"};
    int assessed = 0;  // Whether or not a matching string is found

    for (int i = 0; i < NUMERIC_TOTAL; i++) {
        if (strcmp(grade, stringGrades[i]) == 0) {
            output = assessGrade(numericGrades[i]);
            assessed = 1;
        }
    }

    for (int i = 0; i < SPECIAL_TOTAL; i++) {
        if (strcmp(grade, specialGrades[i]) == 0) {
            output = new char[KILOBYTE];
            sprintf(output, "Student has special situation : %s (%s).",
                    grade, meanings[i]);
            assessed = 1;
        }
    }

    if (!assessed) {  // No matching string
        output = new char[KILOBYTE];
        sprintf(output, "ERROR! Invalid input.");
    }

    return output;
}

/*
* FUNCTION : readAndHandle
* DESCRIPTION :
*   Reads input from stdin, determines the format (string/double/int[]),
*   and calls the matching function to assess the grade.
* PARAMETERS : none
* RETURNS :
*   char* : Empty string if 'X' is read, otherwise the verdict based on input.
*           Has to be `delete[]`d by caller.
*/
char* readAndHandle() {
    char* output = NULL;
    int ignored = 0;
    double grade = 0;     // holds the double grade
    char buffer[KILOBYTE]; // holds the string grade
    int grades[TOTAL_INT_GRADES] = {0, 0, 0, 0, 0}; // holds the int[] grade
    scanf("%s", buffer);
    if (sscanf(buffer, "%d.%d", &ignored, &ignored) == 2) {
        // Float grade is found
        sscanf(buffer, "%lf", &grade);
        output = assessGrade(grade);
    } else if (sscanf(buffer, "%d", &grades[0]) == 1) {
        // Array grade is found
        for (int i = 1; getc(stdin) != '\n'; i++) {
            scanf("%d", &grades[i]);
        }
        output = assessGrade(grades);
    } else {  // String grade or 'X' is found
        if (strcmp(buffer, "X") == 0) {
            output = new char[1];
            output[0] = '\0';
        } else {
            output = assessGrade(buffer);
        }
    }
    return output;
}

