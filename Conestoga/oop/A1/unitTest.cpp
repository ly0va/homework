/*
* FILE :          uniTest.cpp
* PROJECT :       PROG1385 - Assignment #1b
* PROGRAMMER :    Potomkin Lev
* FIRST VERSION : 22.01.2019
* DESCRIPTION :
*   Contains 33 test cases and functions necessary for them to be performed.
*   Main function performs test cases in order specified in the assignment.
*/

#include "assessGrade.h"
#include <stdio.h>
#include <string.h>

// Constants for denoting grade type
enum GradeType {STRING = 0, DOUBLE = 1, ARRAY = 2};
// Constants for denoting test type
enum TestType {FUNCTIONAL = 0, EXCEPTION = 1, BOUNDARY = 2};

/*
* Structure that holds test cases. Includes:
* test ID;
* the type of test (functional / exception / boundary);
* the type of grade to be tested (string / double / array);
* the grade itself;
* expected output;
*/
struct test {
    int ID;
    TestType type;
    GradeType gradeType;
    void* grade;
    char expected[KILOBYTE];
};

// Testing functions
int functionalTest(const test*, GradeType);
int exceptionTest(const test*, GradeType);
int boundaryTest(const test*, GradeType);
void justTest(const test*);

const char* gradeTypes[TOTAL_TYPES] = {"char*", "double", "int[]"};
const char* testTypes[TOTAL_TYPES] = {"Functional", "Exception", "Boundary"};
const test tests[TOTAL_TESTS] =
    {
       {1,  FUNCTIONAL, STRING, (void*)("A"),
            "Student achieved 85.00 % which is a PASS condition."},
       {2,  FUNCTIONAL, STRING, (void*)("B+"),
            "Student achieved 77.00 % which is a PASS condition."},
       {3,  FUNCTIONAL, STRING, (void*)("F"),
            "Student achieved 50.00 % which is a FAIL condition."},
       {4,  FUNCTIONAL, STRING, (void*)("AU"),
            "Student has special situation : AU (Audit)."},
       {5,  FUNCTIONAL, STRING, (void*)("I/P"),
            "Student has special situation : I/P (In process)."},
       {6,  EXCEPTION,  STRING, (void*)("A-"),
            "ERROR! Invalid input."},
       {7,  EXCEPTION,  STRING, (void*)("Hello"),
            "ERROR! Invalid input."},
       {8,  EXCEPTION,  STRING, (void*)(""),
            "ERROR! Invalid input."},
       {9,  EXCEPTION,  STRING, (void*)("ABCD"),
            "ERROR! Invalid input."},
       {10, EXCEPTION,  STRING, (void*)("$#!%"),
            "ERROR! Invalid input."},
       {11, FUNCTIONAL, DOUBLE, (void*)(new double(10.0)),
            "Student achieved 10.00 % which is a FAIL condition."},
       {12, FUNCTIONAL, DOUBLE, (void*)(new double(54.22)),
            "Student achieved 54.22 % which is a FAIL condition."},
       {13, FUNCTIONAL, DOUBLE, (void*)(new double(54.77)),
            "Student achieved 54.77 % which is a PASS condition."},
       {14, FUNCTIONAL, DOUBLE, (void*)(new double(73.123)),
            "Student achieved 73.12 % which is a PASS condition."},
       {15, FUNCTIONAL, DOUBLE, (void*)(new double(90.01)),
            "Student achieved 90.01 % which is a PASS condition."},
       {16, EXCEPTION,  DOUBLE, (void*)(new double(12345.678)),
            "ERROR! Invalid input."},
       {17, EXCEPTION,  DOUBLE, (void*)(new double(-1.11)),
            "ERROR! Invalid input."},
       {18, EXCEPTION,  DOUBLE, (void*)(new double(-1000.0)),
            "ERROR! Invalid input."},
       {19, EXCEPTION,  DOUBLE, (void*)(new double(-1e9)),
            "ERROR! Invalid input."},
       {20, EXCEPTION,  DOUBLE, (void*)(new double(1e9)),
            "ERROR! Invalid input."},
       {21, BOUNDARY,   DOUBLE, (void*)(new double(100.0)),
            "Student achieved 100.00 % which is a PASS condition."},
       {22, BOUNDARY,   DOUBLE, (void*)(new double(100.001)),
            "ERROR! Invalid input."},
       {23, BOUNDARY,   DOUBLE, (void*)(new double(0.0)),
            "Student achieved 0.00 % which is a FAIL condition."},
       {24, FUNCTIONAL, ARRAY,  (void*)(new int[5]{10, 20, 30, 40, 50}),
            "Student achieved 30.00 % which is a FAIL condition."},
       {25, FUNCTIONAL, ARRAY,  (void*)(new int[5]{90, 95, 85, 70, 70}),
            "Student achieved 82.00 % which is a PASS condition."},
       {26, FUNCTIONAL, ARRAY,  (void*)(new int[5]{100, 85, 85, 0, 0}),
            "Student achieved 54.00 % which is a FAIL condition."},
       {27, FUNCTIONAL, ARRAY,  (void*)(new int[5]{51, 0, 0, 0, 0}),
            "Student achieved 10.20 % which is a FAIL condition."},
       {28, FUNCTIONAL, ARRAY,  (void*)(new int[5]{0, 90, 90, 93, 0}),
            "Student achieved 54.60 % which is a PASS condition."},
       {29, EXCEPTION,  ARRAY,  (void*)(new int[5]{5, 5, 5, 5, -1}),
            "ERROR! Invalid input."},
       {30, EXCEPTION,  ARRAY,  (void*)(new int[5]{10, 101, 10, 10, 10}),
            "ERROR! Invalid input."},
       {31, EXCEPTION,  ARRAY,  (void*)(new int[5]{-10, 100, -100, 100, 100}),
            "ERROR! Invalid input."},
       {32, EXCEPTION,  ARRAY,  (void*)(new int[5]{900, 80, 110, 50, 3}),
            "ERROR! Invalid input."},
       {33, EXCEPTION,  ARRAY,  (void*)(new int[5]{123, -123, 0, 0, 0}),
            "ERROR! Invalid input."}
    };

int main(void) {

    // Jump table
    int (*testFunctions[TOTAL_TYPES])(const test*, GradeType) =
                    {functionalTest, exceptionTest, boundaryTest};

    for (int gradeType = 0; gradeType < TOTAL_TYPES; gradeType++) {
        for (int testType = 0; testType < TOTAL_TYPES; testType++) {
            for (int i = 0; i < TOTAL_TESTS; i++) {
                testFunctions[testType](&tests[i], (GradeType)gradeType);
            }
        }
    }

	return 0;
}

/*
* FUNCTION : justTest
* DESCRIPTION :
*   Performs a given test case and prints result to stdout.
* PARAMETERS :
*   const test* myTest : constant pointer to `test` structure -
*                        a test to be performed
* RETURNS : none
*/
void justTest(const test* myTest) {
    char* result = NULL;
    printf("Test #%d : %s test of assessGrade(%s)\n",
           myTest->ID, testTypes[myTest->type], gradeTypes[myTest->gradeType]);

    if (myTest->gradeType == STRING) {  // string grade
        char* stringGrade = (char*)myTest->grade;
        printf("   >> Sumbitting \"%s\" as the student's mark\n",
                   stringGrade);
        result = assessGrade(stringGrade);
    } else if (myTest->gradeType == ARRAY) { // int[] grade
        int* arrayGrade = (int*)myTest->grade;
        printf("   >> Sumbitting \"[");
        for (int i = 0; i < TOTAL_INT_GRADES; i++) {
            printf("%d", arrayGrade[i]);
            printf(i == TOTAL_INT_GRADES-1 ? "]" : ",");
        }
        printf(" as the student's mark\n");
        result = assessGrade(arrayGrade);
    } else { // double grade
        double doubleGrade = *(double*)myTest->grade;
        printf("   >> Sumbitting \"%.3f\" as the student's mark\n",
                   doubleGrade);
        result = assessGrade(doubleGrade);
    }

    printf("     >> Expected result : %s\n", myTest->expected);
    printf("     >> Actual result   : %s\n", result);
    printf("   ** TEST %s **\n\n",
           strcmp(myTest->expected, result) ? "FAILED" : "PASSED");
    delete[] result;
}

/*
* FUNCTION : functionalTest
* DESCRIPTION :
*   Only performs a test case if its type is FUNCTIONAL and
*   its grade type matches the given grade type.
*   Prints result to stdout.
* PARAMETERS :
*   const test* myTest : constant pointer to `test` structure -
*                        a test to be performed.
*   GradeType gradeType : a grade type to match the
*                         type of the grade in the test case
* RETURNS :
*   int : 1 if the test case was performed, 0 otherwise.
*/
int functionalTest(const test* myTest, GradeType gradeType) {
    // Check if the testType and gradeType are valid
    int valid = myTest->type == FUNCTIONAL && myTest->gradeType == gradeType;
    if (valid) {
        justTest(myTest);
    }
    return valid;
}

/*
* FUNCTION : exceptionTest
* DESCRIPTION :
*   Only performs a test case if its type is EXCEPTION and
*   its grade type matches the given grade type.
*   Prints result to stdout.
* PARAMETERS :
*   const test* myTest : constant pointer to `test` structure -
*                        a test to be performed.
*   GradeType gradeType : a grade type to match the
*                         type of the grade in the test case
* RETURNS :
*   int : 1 if the test case was performed, 0 otherwise.
*/
int exceptionTest(const test* myTest, GradeType gradeType) {
    // Check if the testType and gradeType are valid
    int valid = myTest->type == EXCEPTION && myTest->gradeType == gradeType;
    if (valid) {
        justTest(myTest);
    }
    return valid;
}

/*
* FUNCTION : boundaryTest
* DESCRIPTION :
*   Only performs a test case if its type is BOUNDARY and
*   its grade type matches the given grade type.
*   Prints result to stdout.
* PARAMETERS :
*   const test* myTest : constant pointer to `test` structure -
*                        a test to be performed.
*   GradeType gradeType : a grade type to match the
*                         type of the grade in the test case
* RETURNS :
*   int : 1 if the test case was performed, 0 otherwise.
*/
int boundaryTest(const test* myTest, GradeType gradeType) {
    // Check if the testType and gradeType are valid
    int valid = myTest->type == BOUNDARY && myTest->gradeType == gradeType;
    if (valid) {
        justTest(myTest);
    }
    return valid;
}

// This was fun.
// Writing one function doing three different things, and then
// writing three different functions doing exactly the same thing :)
