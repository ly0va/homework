/**
 * @file Circle.cpp
 * @brief Contains implementation of the Circle class methods
 * @details For the class Circle this file contains:
 * - 2 constructors
 * - destructor
 * - accessor and mutator for the `radius` data member
 * - `Show()` - method that displays information
 * - `Perimeter()` - circumference
 * - `Area()`
 * - `OverallDimension()` - diameter
 * - operator= - assignment
 * - operator* - multiplication
 * - operator+ - addition
 * - operator== - equality
 * 
 * @author Lev Potomkin
 * @see Shape
 */

#include "Circle.h"
#include <stdio.h>

/**
 * @brief A default constructor of the Circle class
 * @details Sets name to "Circle", color to "undefined" and radius to 0.0
 */
Circle::Circle(void): Shape("Circle", "undefined") {
    radius = 0.0;
}

/**
 * @brief An overloaded constructor of the Circle class
 * @details Sets name to "Circle", color and radius to the given values.
 * If the values are invalid, sets color to "undefined" and radius to 0.0
 * @param newColor string containing the color
 * @param newRadius number containing the radius
 */
Circle::Circle(string newColor, float newRadius): Shape("Circle", newColor) {
    radius = newRadius >= 0.0 ? newRadius : 0.0;
}

/**
 * @brief A destructor for the class Circle
 * @details prints "The circle is broken ..." to stdout.
 */
Circle::~Circle(void) {
    puts("The circle is broken ...");
}

/**
 * @brief An accessor of the `radius` data member
 * @return Returns circle's radius
 */
float Circle::GetRadius(void) const {
    return radius;
}

/**
 * @brief A mutator of the `radius` data member
 * @details If the passed value is invalid, `radius` is left untouched
 * @param newRadius a number to be set as a radius
 */
void Circle::SetRadius(float newRadius) {
    radius = newRadius >= 0.0 ? newRadius : radius;
}

/**
 * @brief Methods that prints all available information about the circle to stdout.
 * @details The following circle information is printed:
 * - name
 * - color
 * - radius
 * - circumference
 * - area
 */
void Circle::Show(void) {
    printf("\nShape Information\n");
    printf("Name\t\t: Circle\n");
    printf("Color\t\t: %s\n", GetColor().c_str());
    printf("Radius\t\t: %.2f cm\n", radius);
    printf("Circumference\t: %.2f cm\n", Perimeter());
    printf("Area\t\t: %.2f square cm\n", Area());
}

/**
 * @brief Returns circumference of the circle
 * @return **float** circumference, namely 2*PI*radius.
 */
float Circle::Perimeter(void) {
    return 2*PI*radius;
}

/**
 * @brief Returns area of the circle
 * @return **float** area, namely PI*radius*radius.
 */
float Circle::Area(void) {
    return PI*radius*radius;
}

/**
 * @brief Returns diameter of the circle
 * @return **float** width, namely  2*radius.
 */
float Circle::OverallDimension(void) {
    return 2*radius;
}

/**
 * @brief Performs addition of 2 Circles
 * @details This method implements the + operator:
 * The resulting circle has the color of the left operand
 * and the radius equal to the sum of operands' radii.
 * @param rhs the right hand side operand
 * @return **Circle** the resulting Circle
 */
Circle Circle::operator+(const Circle& rhs) {
    return Circle(GetColor(), radius+rhs.GetRadius());
}

/**
 * @brief Performs muliplication of 2 Circles
 * @details This method implements the * operator:
 * The resulting circle has the color of the right operand
 * and the radius equal to the product of operands' radii.
 * @param rhs the right hand side operand
 * @return **Circle** the resulting Circle
 */
Circle Circle::operator*(const Circle& rhs) {
    return Circle(rhs.GetColor(), radius*rhs.GetRadius());
}

/**
 * @brief Performs assignment of one Circle to another
 * @details This method implements the = operator
 * @param rhs the circle to assign
 * @return **const Circle&** a const reference to the circle assigned to
 */
const Circle& Circle::operator=(const Circle& rhs) {
    if (this != &rhs) {
        SetColor(rhs.GetColor());
        SetRadius(rhs.GetRadius());
    }
    return *this;
}

/**
 * @brief Performs comparison of 2 Circles
 * @details This method implements the == operator
 * @param rhs the circle to compare to
 * @return **bool** true if colors are the same and \
 * radii are equal within the margin of EPSILON
 */
bool Circle::operator==(const Circle& rhs) {
    return GetColor() == rhs.GetColor() &&
           abs(radius - rhs.GetRadius()) < EPSILON;
}
