/**
 * @file CircleSquare.h
 * @brief Contains declaration of the CircleSquare class
 * @author Lev Potomkin
 * @see Shape, CircleSquare
 */ 
#ifndef __CIRCLESQUARE_H__
#define __CIRCLESQUARE_H__  // include guards

#include "Shape.h"

/**
 * @class CircleSquare
 * @brief Class that models a circle and a circle as one shape
 * 
 * @details The Circle class inherits publicly from class Shape.
 * It models 2 shapes at ones: either square embedded in circle, or
 * vice versa. It has their basic properties: radius, sideLength,
 * area, circumference, etc.
 * It implements:
 * - 2 constructors
 * - destructor
 * - accessor and mutator for the `radius` data member
 * - `Show()` method that displays information
 * - `Perimeter()` - perimeter of the outer shape
 * - `Area()` - area of the outer shape
 * - `OverallDimension()` - dimension of the outer shape
 * - `SecondaryPerimeter()` - perimeter of the inner shape
 * - `SecondaryArea()` - area of the inner shape
 * - operator= - assignment
 * - operator+ - addition
 * 
 * @see Shape
 */
class CircleSquare : public Shape {
    private:
        float radius;      ///< the radius of the circle
        float sideLength;  ///< the side length of the square
    public:
        CircleSquare(string newColor, string newName, 
                     float newRadius, float newSideLength); ///< overloaded constructor
        CircleSquare(void);                         ///< default constructor
        virtual ~CircleSquare(void);                ///< destructor
        float GetRadius(void) const;                ///< radius accessor
        float GetSideLength(void) const;            ///< sideLength accessor
        void SetRadius(float newRadius);            ///< radius mutator
        void SetSideLength(float newSideLength);    ///< sideLength mutator
        virtual float Perimeter(void);              ///< outer perimeter
        virtual float Area(void);                   ///< outer area
        virtual float OverallDimension(void);       ///< outer dimension
        void Show(void);                            ///< prints information
        CircleSquare operator+(const CircleSquare& rhs); ///< addition
        const CircleSquare& operator=(const CircleSquare& rhs); ///< assignment
        float SecondaryPerimeter(void);             ///< inner perimeter
        float SecondaryArea(void);                  ///< inner area
};

#endif