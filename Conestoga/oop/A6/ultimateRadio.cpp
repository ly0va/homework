/* FILE: ultimateRadio.cpp
 * PROJECT: PROG 1385 - Assignment 5
 * PROGRAMMER: Lev Potomkin
 * FIRST VERSION: Mar 18, 2019
 * DESCRIPTION: 
 *  This file contains the test harness for PioneerAM and PioneerWorld classes.
 *  It accepts a single command line argument, either "-car", "-am" or "-world" 
 *  and instantiates an object respectively. 
 *  For each instantiated object the HandleCommands method is run (see
 *  documentation for exact interface).
 *  After exiting that method, user us preseted with the following interface:
 *  'c' to create PioneerCarRadio
 *  'a' to create PioneerAM radio
 *  'w' to create PioneerWorld radio
 *  'x' to exit.
 *  In case the command line argument is missing or invalid and in case the
 *  the program runs out of memory, error is printed and program terminates.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <stdexcept>
#include "PioneerAm.h"
#include "PioneerWorld.h"

// command line switches
#define AM_SWITCH "-am"
#define WORLD_SWITCH "-world"
#define CAR_SWITCH "-car"

using namespace std;

PioneerCarRadio* createRadio(string type);

int main(int argc, char** argv) {
    PioneerCarRadio* pRadio = NULL; // radio object
    char key = 0;
    string type = "";

    try {
        if (argc < 2) {
            // a command line argument missing
            throw runtime_error("not enough arguments");
        }
        pRadio = createRadio(argv[1]);
        pRadio->HandleCommands();
    } catch (exception& e) {
        // something bad happened :(
        printf("Error: %s\n", e.what());
        return 0;
    }

    do {

        if (pRadio != NULL) {
            // free the memory
            delete pRadio;
            pRadio = NULL;
        }

        key = getch(); // read the command

        // determine the type of radio
        if (key == 'c') {
            type = CAR_SWITCH;
        } else if (key == 'a') {
            type = AM_SWITCH;
        } else if (key == 'w') {
            type = WORLD_SWITCH;
        }

        if (key == 'c' || key == 'a' || key == 'w') {
            try {
                // instantiate and enter the event loop
                pRadio = createRadio(type);
                pRadio->HandleCommands();
            } catch (bad_alloc& e) {
                // out of memory :(
                printf("Error: %s\n", e.what());
                return 0;
            }
        }

    } while (key != 'x');

    return 0;
}

/**
 * FUNCTION: createRadio
 * DESCRiPTION: 
 *  Dynamically allocates memory for a radio object and
 *  instantiates it based of the argument provided.
 *  Throws invalid_argument in case argument is not one of
 *  "-car", "-am", "-world" and throws bad_alloc if out of memory.
 * PARAMETERS:
 *  string type: the type of radio to instantiate
 * RETURNS:
 *  PioneerCarRadio* : a pointer to instantiated radio object
 * 
 */
PioneerCarRadio* createRadio(string type) {
    if (type == CAR_SWITCH) {
        return new PioneerCarRadio;
    } else if (type == AM_SWITCH) {
        return new PioneerAM;
    } else if (type == WORLD_SWITCH) {
        return new PioneerWorld;
    } else {
        throw invalid_argument("invalid argument: " + type);
    }
}