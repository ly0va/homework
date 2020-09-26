/**
 * @file Shape.cpp
 * @brief Contains implementation of Shape class methods
 * @details For the class Shape this file contains:
 * - 2 constructors
 * - virtual destructor (so that there won't be any undefined behaviour)
 * - accessors and mutators for data members
 * - 3 pure virtual methods:
 *   - `Area()` - returns area
 *   - `Perimeter()` - returns perimeter
 *   - `OverallDimension()`
 * - static method `Allowed()` - validates color and name
 * 
 * @author Lev Potomkin
 * @see Shape
 */

#include "Shape.h"

/**
 * @brief Checks if the supplied string is a valid color or name
 * @param field a string to check
 * @param allowedFields an array of allowed string values
 * @param totalFields total number of allowed string values
 * @returns **bool** - whether or not the string is valid
 */
bool Shape::Allowed(string field, 
                    const string *allowedFields, 
                    int totalFields) {
    bool result = false;
    for (int i = 0; i < totalFields; i++) {
        if (field == allowedFields[i]) {
            result = true;
        }
    }
    return result;
}

/**
 * @brief Default constructor of the Shape class
 * @details Sets the name to "Unknown" and color to "undefined".
 */
Shape::Shape(void) {
    name = "Unknown";
    color = "undefined";
}

/**
 * @brief An overloaded constructor of the Shape class
 * @details Accepts a name and a color. If the name is invalid, it
 * is set to "Unknown". If the color is invalid, it is set to "undefined"
 * @param newName a string containing the shape's name
 * @param newColor a string containing shape's color
 */
Shape::Shape(string newName, string newColor) {
    name = Allowed(newName, allowedNames, TOTAL_NAMES) 
           ? newName : "Unknown";
    color = Allowed(newColor, allowedColors, TOTAL_COLORS) 
            ? newColor : "undefined";
}

/**
 * @brief An accessor of the `name` data member
 * @details Returns the copy of a shape's name
 * @return **string** shape's name
 */
string Shape::GetName(void) {
    return name;
}

/**
 * @brief An accessor of the `color` data member
 * @details Returns the copy of a shape's color
 * @return **string** shape's color
 */
string Shape::GetColor(void) {
    return color;
}

/**
 * @brief A mutator of the `name` data member
 * @details Provides interface to set the shape's name.
 * If the name is invalid, it is left untouched.
 * @param newName a name to be set
 */
void Shape::SetName(string newName) {
    name = Allowed(newName, allowedNames, TOTAL_NAMES) 
           ? newName : name;
}

/**
 * @brief A mutator of the `color` data member
 * @details Provides interface to set the shape's color.
 * If the color is invalid, it is left untouched.
 * @param newColor a color to be set
 */
void Shape::SetColor(string newColor) {
    color = Allowed(newColor, allowedColors, TOTAL_COLORS) 
            ? newColor : color;
}


