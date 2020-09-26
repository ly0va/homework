/* FILE: PioneerAM.cpp
 * PROJECT: PROG 1385 - Assignment 6
 * PROGRAMMER: Lev Potomkin
 * FIRST VERSION: Mar 23, 2019
 * DESCRIPTION: 
 *  This file containts the declaration of class PioneerWorld
 *  and implemenation of its methods.
 */ 
#ifndef _PIONEERWORLD_H // inlcude guards
#define _PIONEERWORLD_H
#include <string.h>
#include "PioneerCarRadio.h"

// different constants for different scanning settings
#define BEGIN_AM_WORLD 531
#define END_AM_WORLD 1602
#define DELTA_AM_WORLD 9

/* NAME: PioneerAM
 * PURPOSE:
 *  This class is created to model the car radio, but with 
 *  different scanning settings.
 *  It is a subclass or PioneerCarRadio and therefore inherits all its
 *  methods. 
 *  Class data members are overriden to implement different scanning settings.
 *  No overriden methods or data members defined. 
 */
class PioneerWorld : public PioneerCarRadio {

public:
    /*FUNCTION: PioneerWorld::PioneerWorld
    * DESCRIPTION:
    *  Constructor of the PioneerWorld class.
    *  Accepts whether or not the radio is on.
    *  Sets name to "XS440-WRLD".
    *  Sets other data members to default values
    * PARAMETERS: 
    *  bool newOn : optional (default = false), 
    *               whether or not the radio is on. 
    * RETURNS: none
    */
    PioneerWorld(bool on = false): PioneerCarRadio("XS440-WRLD", on) {
        // different default settings
        SetCurrentStation(BEGIN_AM_WORLD);
        for (int i = 0; i < TOTAL_FREQS; ++i) {
            SetButton(i);
        }
    }

private:
    /* FUNCTION: PioneerWorld::ScanUp
    * DESCRIPTION:
    *  Method to change the frequency of current_station.
    *  If on AM band, increment by 9, otherwise by 0.2
    *  If maximum frequency reached, roll down to the minimum frequency.
    *  Also, print to stdout (optional)
    * PARAMETERS: none
    * RETURNS: none
    */
    virtual void ScanUp(void) {
        if (strcmp("AM", GetFrequency()) == 0) {
            if (GetCurrentStation() >= END_AM_WORLD) {
                SetCurrentStation(BEGIN_AM_WORLD);
            } else {
                SetCurrentStation(DELTA_AM_WORLD + GetCurrentStation());
            }
        } else {
            AmFmRadio::ScanUp();
        }
    }

    /* FUNCTION: PioneerWorld::ScanDown
    * DESCRIPTION:
    *  Method to change the frequency of current_station.
    *  If on AM band, decrement by 9, otherwise by 0.2
    *  If minimum frequency reached, roll up to the maximum frequency.
    *  Also, print to stdout (optional)
    * PARAMETERS: none
    * RETURNS: none
    */
    virtual void ScanDown(void) {
        if (strcmp("AM", GetFrequency()) == 0) {
            if (GetCurrentStation() <= BEGIN_AM_WORLD) {
                SetCurrentStation(END_AM_WORLD);
            } else {
                SetCurrentStation(GetCurrentStation() - DELTA_AM_WORLD);
            }
        } else {
            AmFmRadio::ScanDown();
        }
    }
    
};

#endif