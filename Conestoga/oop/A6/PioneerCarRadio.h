/* FILE: PioneerCarRadio.cpp
 * PROJECT: PROG 1385 - Assignment 6
 * PROGRAMMER: Lev Potomkin
 * FIRST VERSION: Mar 18, 2019
 * DESCRIPTION: 
 *  This file containts the declaration of PioneerCarRadio class.
 */ 

#ifndef _PIONEERCARRADIO_H  // include guards
#define _PIONEERCARRADIO_H
#include "AmFmRadio.h"
#include <string>

using std::string;

/* NAME: PioneerCarRadio
 * PURPOSE: The PioneerCarRadio class has been created to model the 
 *   Pioneer Car Radio. It publicly inherints the AmFmRadio 
 *   defined in AmFmRadio.h. Additional functionality is given by the
 *   HandleCommand method, which delegates the execution to method that
 *   is determined by the argument.
 *   Also, an additional DisplayInformation method is created to
 *   present the settings in format, different from the one in parent class.
 *   One additional data member is defined - name - to keep track of its type.
 */
class PioneerCarRadio : public AmFmRadio {
private:
    string name;  // type of radio - either "XS440", "XS440-AM" or "XS440-WRLD"
public:
    PioneerCarRadio(string newName = "XS440", bool on = false);  // constructor with default freqs
    PioneerCarRadio(string newName, bool on, Freqs* freqs);      // constructor with non-default freqs
    virtual ~PioneerCarRadio(void);          // destructor
    void HandleCommands(void);               // handling commands from the user
    virtual void ShowCurrentSettings(void);  // prints settings to stdout;
    string GetName(void);
};

#endif