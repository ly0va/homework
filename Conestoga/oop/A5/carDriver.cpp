/* FILE: carDriver.cpp
 * PROJECT: PROG 1385 - Assignment 5
 * PROGRAMMER: Lev Potomkin
 * FIRST VERSION: Mar 18, 2019
 * DESCRIPTION: 
 *  This file contains user interface for the PioneerCarRadio and
 *  serves as a test harness.
 *  The interface is implemented by having the user press keys.
 * 
 *  Options are:
 *  'o' to toggle on/off
 *  '+' and '_' to turn the volume up or down, respectively
 *  '=' and '-' to scan frequencies up or down, respectively
 *  'b' to toggle AM/FM
 *  '1' to '5' to select the preset
 *  Shift + '1' to '5' to set the preset
 * 
 *  All input is accepted through stdin and output printed to stdout.
 *  Interface exposes basic functionality of the PioneerCarRadio class found in 
 *  PioneerCarRadio.h
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // getch is here
#include "PioneerCarRadio.h"

int main() {
    PioneerCarRadio radio; // instantiate the radio
    char command = '\0';
    do {
        command = getch(); // read the command
        if (command != 'x') {
            // not exiting - execute the command
            radio.HandleCommand(command);
            radio.DisplayInformation();
        }
    } while (command != 'x');
    return 0;
}