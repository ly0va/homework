/**
 * @file myShape.cpp
 * @brief This file contains the test harness for classes Circle, Square and CircleSquare
 * @details The file tests basic functionality of classes Circle, Square and CircleSquare
 * in particular overloaded operator+, template functions and exception handling.
 * Addition of squares is tested via the template function, as was addition of 
 * a square to a circle. All exceptions are handles, output printed to stdout.
 * @author Lev Potomkin
 * @see Circle, Square, CircleSquare
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circle.h"
#include "Square.h"
#include "CircleSquare.h"

template<class Type>
Type CombineShape(const Type& lhs, const Type& rhs);

template<class Type1, class Type2>
CircleSquare CombineDifferentShape(const Type1& lhs, const Type2& rhs);

int main(void) {

    // instantiating circles
    Circle round1("red", 5.5);
    Circle round2("blue", 10.5);

    // instantiating squares
    Square square1("orange", 5);
    Square square2("purple", 12);

    CircleSquare playARoundSquare;

    Square playASquare = CombineShape(square2, square1);
    playASquare.Show();

    try {
        playARoundSquare = CombineDifferentShape(square2, round1);
        playARoundSquare.Show();
    } catch (const char* e) {
        puts(e);
    }

    try {
        playARoundSquare = CombineDifferentShape(square1, round2);
        playARoundSquare.Show();
    } catch (const char* e) {
        puts(e);
    }

    return 0;
}

/**
 * @fn CombineShape
 * @brief Performs addition of 2 shapes of the same type
 * @param lhs - left hand side operand
 * @param rhs - right hand side operand
 * @return **Type** - the result of addition
 */
template<class Type>
Type CombineShape(const Type& lhs, const Type& rhs) {
    return lhs + rhs;
}

/**
 * @fn CombineShape
 * @brief Performs addition of 2 shapes of different types (Square & Circle)
 * @param lhs - left hand side operand
 * @param rhs - right hand side operand
 * @return **CircleSquare** - the result of addition
 */
template<class Type1, class Type2>
CircleSquare CombineDifferentShape(const Type1& lhs, const Type2& rhs) {
    return lhs + rhs;
}