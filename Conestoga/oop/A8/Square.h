/**
 * @file Square.h
 * @brief Contains declaration of the Square class
 * @author Lev Potomkin
 * @see Square
 */ 
#ifndef __SQUARE_H__
#define __SQUARE_H__
#include "Shape.h"
#include "Circle.h"
#include "CircleSquare.h"

/**
 * @class Square
 * @brief Class that models a square
 * 
 * @details The Square class inherits publicly from class Shape.
 * It models a sqaure and its basic properties, such as side length,
 * area, perimeter, etc.
 * It implements:
 * - 2 constructors
 * - destructor
 * - accessor and mutator for the `sideLength` data member
 * - `Show()` - method that displays information
 * - `Perimeter()`
 * - `Area()`
 * - `OverallDimension()`
 * 
 * @see Shape
 */
class Square: public Shape {
    private:
        float sideLength;                             ///< the side length of the square
    public:
        Square(void);                                 ///< the default constructor
        Square(string newColor, float newSideLength); ///< the overloaded constructor
        virtual ~Square(void);                        ///< destructor
        float GetSideLength(void) const;              ///< side length accessor
        void SetSideLength(float newSideLength);      ///< side length mutator
        void Show(void);                              ///< prints information
        virtual float Perimeter(void);                ///< returns perimeter
        virtual float Area(void);                     ///< returns area
        virtual float OverallDimension(void);         ///< returns width
        Square operator+(const Square& rhs) const;    ///< addition operator
        Square operator*(const Square& rhs);      ///< multiplication operator
        const Square& operator=(const Square& rhs); ///< assignment operator
        bool operator==(const Square& rhs);       ///< equality operator
        CircleSquare operator+(const Circle& rhs) const; ///< another addition operator
};

#endif
