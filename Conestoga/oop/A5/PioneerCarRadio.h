/* FILE: PioneerCarRadio.cpp
 * PROJECT: PROG 1385 - Assignment 5
 * PROGRAMMER: Lev Potomkin
 * FIRST VERSION: Mar 18, 2019
 * DESCRIPTION: 
 *  This file containts the declaration of PioneerCarRadio class.
 */ 

#ifndef _PIONEERCARRADIO_H  // include guards
#define _PIONEERCARRADIO_H
#include "AmFmRadio.h"

/* NAME: PioneerCarRadio
 * PURPOSE: The PioneerCarRadio class has been created to model the 
 *   Pioneer Car Radio. It publicly inherints the AmFmRadio 
 *   defined in AmFmRadio.h. Additional functionality is given by the
 *   HandleCommand method, which delegates the execution to method that
 *   is determined by the argument.
 *   Also, an additional DisplayInformation method is created to
 *   present the settings in format, different from the one in parent class.
 *   No additional data members created.
 */
class PioneerCarRadio : public AmFmRadio {
public:
    PioneerCarRadio(bool on = false);      // constructor with default freqs
    PioneerCarRadio(bool on, Freqs* freqs);// constructor with non-default freqs
    ~PioneerCarRadio(void);                // destructor
    void HandleCommand(char command);      // handling commands from the user
    void DisplayInformation(void); // prints settings to stdout;
                                   // not overriding ShowCurrentSettings because 
                                   // that would require adding 'virtual'
                                   // and we are not allowed to change the base
};

#endif