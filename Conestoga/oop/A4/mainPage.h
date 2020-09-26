/**
 * @mainpage Assignment 4
 * 
 * @section intro Introduction
 * This project is built for the Assignment 4 of the OOP course (PROG 1385).
 * It contains 3 classes and a test harness. 
 * 
 * Classes are:
 * - Shape - an abstract base class
 * - Circle - models a circle and its basic properties
 * - Square - models a square and its basic properties
 * 
 * Test harness contains simple routine with dynamic memory allocation.
 * 
 * @note This project uses DOxygen-style commenting
 * 
 * 
 * ---
 * 
 * @section requirements Project Requirements
 * Requirements can be found on eConestoga.
 * 
 * ---
 * 
 * @section knownBugs Known Issues
 * 1. A static method Shape::Allowed was implemented, althogh wasn't required.
 * This was done in order to minimize code repetition, as the validation routine 
 * is used not only inside the Shape class.
 * 2. A C++11 syntax was used in Shape.h: `virtual ~Shape() = default`. Although wasn't
 * explicitly stated in requirements that Shape needs a destructor, it does and it has 
 * to be virtual in order to avoid undefined behaviour. But it can be a default one.
 * 
 * 
 * ---
 * 
 * @section version Current Version:
 * - @author Lev Potomkin
 * - @version 1.0.0
 * - @date Mar 12, 2019
 * 
 */