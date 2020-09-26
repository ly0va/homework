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
 * - operator= - assignment
 * - operator* - multiplication
 * - operator+ - addition
 * - operator== - equality
 * 
 * @author Lev Potomkin
 * @see Shape
 */

#include "Square.h"
#include <stdio.h>
#include <exception>

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
float Square::GetSideLength(void) const {
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

/**
 * @brief Performs addition of 2 Squares
 * @details This method implements the + operator:
 * The resulting Square has the color of the left operand
 * and the sideLength equal to the sum of operands' sideLengths.
 * @param rhs the right hand side operand
 * @return **Square** the resulting Square
 */
Square Square::operator+(const Square& rhs) const {
    return Square(GetColor(), sideLength+rhs.GetSideLength());
}

/**
 * @brief Performs muliplication of 2 Squares
 * @details This method implements the * operator:
 * The resulting Square has the color of the right operand
 * and the sideLength equal to the product of operands' sideLengths.
 * @param rhs the right hand side operand
 * @return **Square** the resulting Square
 */
Square Square::operator*(const Square& rhs) {
    return Square(rhs.GetColor(), sideLength*rhs.GetSideLength());
}

/**
 * @brief Performs assignment of one Square to another
 * @details This method implements the = operator
 * @param rhs the Square to assign
 * @return **const Square&** a const reference to the Square assigned to
 */
const Square& Square::operator=(const Square& rhs) {
    if (this != &rhs) {
        SetColor(rhs.GetColor());
        SetSideLength(rhs.GetSideLength());
    }
    return *this;
}

/**
 * @brief Performs comparison of 2 Squares
 * @details This method implements the == operator
 * @param rhs the Square to compare to
 * @return **bool** true if colors are the same and \
 * radii are equal within the margin of EPSILON
 */
bool Square::operator==(const Square& rhs) {
    return GetColor() == rhs.GetColor() &&
           abs(sideLength - rhs.GetSideLength()) < EPSILON;
}

/**
 * @brief Performs addition of a Square and a Circle
 * @details This method implements the + operator:
 * The resulting CircleSquare has the color of the left operand, 
 * sideLength of the left operand, radius of the right operand,
 * and name "Square-Circle".
 * Throws exception if the sideLength is less then a diameter.
 * @param rhs the right hand side operand
 * @return **Square** the resulting CircleSquare
 */
CircleSquare Square::operator+(const Circle& rhs) const {
    if (sideLength / 2 >= rhs.GetRadius()) {
        return CircleSquare(GetColor(), "Square-Circle", 
                            rhs.GetRadius(), sideLength);
    } else {
        throw "ERROR: Incompatible shape sizes";
    }
}