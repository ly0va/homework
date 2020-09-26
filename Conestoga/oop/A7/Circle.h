/**
 * @file Circle.h
 * @brief Contains declaration of the Circle class
 * @author Lev Potomkin
 * @see Circle
 */ 

#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include "Shape.h"

/**
 * @class Circle
 * @brief Class that models a circle
 * 
 * @details The Circle class inherits publicly from class Shape.
 * It models a circle and its basic properties, such as radius,
 * area, circumference, etc.
 * It implements:
 * - 2 constructors
 * - destructor
 * - accessor and mutator for the `radius` data member
 * - `Show()` method that displays information
 * - `Perimeter()`
 * - `Area()`
 * - `OverallDimension()`
 * 
 * @see Shape
 */
class Circle: public Shape {
    private:
        float radius;                             ///< the radius of the circle
    public:
        Circle(void);                             ///< the default constructor
        Circle(string newColor, float newRadius); ///< overloaded construtor
        virtual ~Circle(void);                    ///< destructor
        float GetRadius(void);                    ///< radius accessor
        void SetRadius(float newRadius);          ///< radius mutator
        void Show(void);                          ///< prints information
        virtual float Perimeter(void);            ///< returns circumference
        virtual float Area(void);                 ///< returns area
        virtual float OverallDimension(void);     ///< returns diameter
        Circle operator+(const Circle& rhs);      ///< addition operator
        Circle operator*(const Circle& rhs);      ///< multiplication operator
        const Circle& operator=(const Circle& rhs); ///< assignment operator
        bool operator==(const Circle& rhs);       ///< equality operator
};

#endif
