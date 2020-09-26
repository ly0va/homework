/**
 * @file Square.cpp
 * @brief Contains implementation of the Square class methods
 * @details For the class Square this file contains:
 * - 2 constructors
 * - destructor
 * - accessor and mutator for the `sideLength` data member
 * - `Show()` - method that displays information
 * - `Perimeter()`
 * - `Area()`
 * - `OverallDimension()`
 * 
 * @author Lev Potomkin
 * @see Shape
 */

#include "Square.h"
#include <stdio.h>

/**
 * @brief A default constructor of the Square class
 * @details Sets name to "Square", color to "undefined" and sideLength to 0.0
 */
Square::Square(void): Shape("Square", "undefined") {
    sideLength = 0.0;
}

/**
 * @brief An overloaded constructor of the Square class
 * @details Sets name to "Square", color and sideLength to the given values.
 * If the values are invalid, sets color to "undefined" and sideLength to 0.0
 * @param newColor string containing the color
 * @param newSideLength number containing the side length
 */
Square::Square(string newColor, float newSideLength): Shape("Square", newColor) {
    sideLength = newSideLength >= 0.0 ? newSideLength : 0.0;
}

/**
 * @brief A destructor for the class Square
 * @details prints "The square is squished ..." to stdout.
 */
Square::~Square(void) {
    puts("The square is squished ...");
}

/**
 * @brief An accessor of the `sideLength` data member
 * @return Returns square's side length
 */
float Square::GetSideLength(void) {
    return sideLength;
}

/**
 * @brief A mutator of the `sideLength` data member
 * @details If the passed value is invalid, `sideLength` is left untouched
 * @param newSideLength a number to be set as a side length
 */
void Square::SetSideLength(float newSideLength) {
    sideLength = newSideLength >= 0.0 ? newSideLength : sideLength;
}

/**
 * @brief Methods that prints all available information about the square to stdout.
 * @details The following square information is printed:
 * - name
 * - color
 * - side length
 * - perimeter
 * - area
 */
void Square::Show(void) {
    printf("\nShape Information\n");
    printf("Name\t\t: Square\n");
    printf("Color\t\t: %s\n", GetColor().c_str());
    printf("Side-Length\t: %.2f cm\n", sideLength);
    printf("Perimeter\t: %.2f cm\n", Perimeter());
    printf("Area\t\t: %.2f square cm\n", Area());
}

/**
 * @brief Returns perimeter of the square
 * @return **float** perimeter, namely 4*sideLength.
 */
float Square::Perimeter(void) {
    return 4*sideLength;
}

/**
 * @brief Returns area of the square
 * @return **float** area, namely sideLength*sideLength.
 */
float Square::Area(void) {
    return sideLength*sideLength;
}

/**
 * @brief Returns width of the square
 * @return **float** width, equal to sideLength.
 */
float Square::OverallDimension(void) {
    return sideLength;
}