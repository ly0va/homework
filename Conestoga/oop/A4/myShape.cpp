/**
 * @file myShape.cpp
 * @brief This file contains the test harness for classes Circle and Square
 * @details The file tests basic functionality of classes Circle and Square:
 * user inputs circle color and shape, followed by square color 
 * and side length. Objects are instantiated and method Show() 
 * is called on both. Input accepted through stdin, output printed
 * to stdout.
 * @author Lev Potomkin
 * @see Circle, Square
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Circle.h"
#include "Square.h"
#define BUFFER_SIZE 51 

string getColor(void);
float getFloat(void);

int main(void) {
    // initializing variables
    Circle* circle = NULL;    ///< circle pointer
    Square* square = NULL;    ///< square pointer
    string circleColor = "";
    string squareColor = "";
    float radius = 0;
    float sideLength = 0;

    // asking for input
    printf("Enter circle color: ");
    circleColor = getColor();
    printf("Enter circle radius: ");
    radius = getFloat();

    printf("Enter square color: ");
    squareColor = getColor();
    printf("Enter square side length: ");
    sideLength = getFloat();

    // instantiating objects using dynamically allocated memory
    circle = new Circle(circleColor, radius);
    square = new Square(squareColor, sideLength);

    // displaying information
    circle->Show();
    square->Show();

    // deallocating memory
    delete circle;
    delete square;

    return 0;
}

/**
 * @fn string getColor(void)
 * @brief Accepts a color from stdin
 * @details Reads a string from stdin, reprompting if the color is invalid.
 * @returns **string** - the color entered by the user.
 */
string getColor(void) {
    char buffer[BUFFER_SIZE] = "";
    bool valid = true;
    do {
        if (!valid) {
            // user entered invalid string
            printf("Error! Please enter a valid color: ");
        }
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strlen(buffer)-1] = 0; // getting rid of the last \n
        valid = Shape::Allowed(buffer, allowedColors, TOTAL_COLORS);
    } while (!valid);
    return buffer;
}

/**
 * @fn string getFloat(void)
 * @brief Accepts a non-negative float from stdin
 * @details Reads a number from stdin, reprompting if it is negative.
 * @returns **float** - the number entered by the user.
 */
float getFloat(void) {
    char buffer[BUFFER_SIZE] = "";
    float number = -1;
    bool valid = true;
    do {
        if (!valid) {
            // user entered not a number or the number was negative
            printf("Error! Please enter a valid non-negative value: ");
        }
        fgets(buffer, BUFFER_SIZE, stdin);
        valid = sscanf(buffer, " %f", &number) == 1 && number >= 0;
    } while (number < 0);
    return number;
}
