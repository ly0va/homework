/**
 * @file myShape.cpp
 * @brief This file contains the test harness for classes Circle and Square
 * @details The file tests basic functionality of classes Circle and Square, 
 * in particular overloaded operators +, *, = and ==.
 * 3 Circles and 3 Squares have been instantiated, 
 * method Show() is called in each. Each operator has been tested.
 * All output is printed to stdout.
 * @author Lev Potomkin
 * @see Circle, Square
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circle.h"
#include "Square.h"

int main(void) {

    // instantiating circles
    Circle round1("red", 5.5);
    Circle round2("blue", 10.5);
    Circle playARound;

    // instantiating squares
    Square square1("orange", 5);
    Square square2("purple", 12);
    Square playASquare;

    // printing initial states of shapes
    round1.Show();
    round2.Show();
    playARound.Show();

    square1.Show();
    square2.Show();
    playASquare.Show();

    // performing addition
    playARound = round1 + round2;
    playASquare = square2 + square1;

    // printing restults
    playARound.Show();
    playASquare.Show();

    // performing multiplication
    playARound = round1 * round2;
    playASquare = square2 * square1;

    // printing results
    playARound.Show();
    playASquare.Show();

    // testing assignment
    playARound = round1;

    // testing equality
    if (playARound == round1) {
        puts("Hurray !!");
    } else {
        puts("Awww !!");
    }

    return 0;
}
