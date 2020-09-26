/**
 * @file Shape.h
 * @brief Contains declaration of the Shape class
 * @author Lev Potomkin
 * @see Shape
 */ 

#ifndef __SHAPE_H__
#define __SHAPE_H__
#include <string>
#define TOTAL_NAMES 3   ///< number of allowed names
#define TOTAL_COLORS 8  ///< number of allowed colors

using std::string;

// allowed values for names and colors
const string allowedNames[TOTAL_NAMES] = {"Circle", "Square", "Unknown"};
const string allowedColors[TOTAL_COLORS] = {"red", "green", "blue", 
                      "yellow", "purple", "pink", "orange", "undefined"};
/**
 * @class Shape
 * @brief An abstract base class to inherit other shape classes from
 * 
 * @details Shape provides interface for other shape classes.
 * It defines the following data members:
 * - `name`: either Circle, Square or Unknown
 * - `color`: either red, green, blue, yellow, purple, pink, orange of undefined
 * 
 * As well as:
 * - 2 constructors
 * - virtual destructor (so that there won't be any undefined behaviour)
 * - accessors and mutators for data members
 * - 3 pure virtual methods:
 *   - `Area()` - returns area
 *   - `Perimeter()` - returns perimeter
 *   - `OverallDimension()`
 * - static method `Allowed()` - validates color and name
 * 
 * @see Square, Circle
 */
class Shape {
    private:
        string name;            ///< shape name - Circle, Square or Unknown
        string color;           ///< shape color
    public:
        Shape(void);                            ///< default constructor
        Shape(string newName, string newColor); ///< overloaded constructor
        // has to have a virtual destructor, so it's a default one
        virtual ~Shape() = default;             ///< default destructor
        string GetName(void) const;             ///< name accessor
        string GetColor(void) const;            ///< color accessor
        void SetName(string newName);           ///< name mutator
        void SetColor(string newColor);         ///< color mutator
        virtual float Perimeter(void) = 0;      ///< perimeter (virtual)
        virtual float Area(void) = 0;           ///< area (virtual)
        virtual float OverallDimension(void) = 0; ///< overall dimension (virtual)
        static bool Allowed(string field, 
                            const string *allowedFields, 
                            int totalFields);   ///< checks if name/color is allowed
};

#endif
