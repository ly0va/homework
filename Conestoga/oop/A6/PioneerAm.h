/* FILE: PioneerAM.cpp
 * PROJECT: PROG 1385 - Assignment 6
 * PROGRAMMER: Lev Potomkin
 * FIRST VERSION: Mar 23, 2019
 * DESCRIPTION: 
 *  This file containts the declaration of class PioneerAM 
 *  and implemenation of its methods.
 */ 

#ifndef _PIONEERAM_H // include guards
#define _PIONEERAM_H
#include <stdio.h>
#include "PioneerCarRadio.h"

/* NAME: PioneerAM
 * PURPOSE:
 *  This class is created to model the car radio, but only with an AM band.
 *  It is a subclass or PioneerCarRadio and therefore inherits all its
 *  methods. 
 *  The only overriden method is ToggleFrequency, which prints an error message
 *  No new data members defined.
 */
class PioneerAM : public PioneerCarRadio {

public:

    /*FUNCTION: PioneerAM::PioneerAM
    * DESCRIPTION:
    *  Constructor of the PioneerAM class.
    *  Accepts whether or not the radio is on.
    *  Sets name to "XS440-AM".
    *  Sets other data members to default values
    *  (found in AmFmRadio.h).
    * PARAMETERS: 
    *  bool newOn : optional (default = false), 
    *               whether or not the radio is on. 
    * RETURNS: none
    */
    PioneerAM(bool on = false): PioneerCarRadio("XS440-AM", on) {}

    /*FUNCTION: PioneerAM::ToggleFrequency
    * DESCRIPTION:
    *  An overriden method to disable the option
    *  to toggle the frequency. 
    *  If displayOutput is on, prints and error message to stdout.
    * PARAMETERS: none 
    * RETURNS: none
    */
    virtual void ToggleFrequency(void) {
        if (GetDisplayOutput()) {
            printf("Can't toggle band - AM only!\n");
        }
    }
};

#endif