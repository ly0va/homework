/* FILE: PioneerCarRadio.cpp
 * PROJECT: PROG 1385 - Assignment 6
 * PROGRAMMER: Lev Potomkin
 * FIRST VERSION: Mar 18, 2019
 * DESCRIPTION:
 *  This file contains all methods for the PioneerCarRadio class
 *  (except for those inherited from AmFmRadio).
 *  This includes
 *  - 2 constructors
 *  - destructor
 *  - HandleCommand(char command) - delegates execution to the method
 *                                  determined by the argument
 *  - DisplayInformation(void) - prints current settings to stdout
 */


#include "PioneerCarRadio.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>

using std::string;


/* FUNCTION: PioneerCarRadio::PioneerCarRadio
 * DESCRIPTION:
 *  Constructor of the PioneerCarRadio class.
 *  Accepts the radio type and 
 *  whether or not the radio is on.
 *  Sets other data members to default values
 *  (found in AmFmRadio.h).
 * PARAMETERS: 
 *  string newName : optional (default = "XS440")
 *                   type of the radio.
 *  bool newOn : optional (default = false), 
 *               whether or not the radio is on. 
 * RETURNS: none
 */
PioneerCarRadio::PioneerCarRadio(string newName, bool on): AmFmRadio(on) {
    name = newName;
}

/* FUNCTION: PioneerCarRadio::PioneerCarRadio
 * DESCRIPTION:
 *  Constructor of the PioneerCarRadio class.
 *  Accepts whether or not the radio is on and an 
 *  array of struct Freqs - presets.
 *  Sets other data members to default values.
 * PARAMETERS: 
 *  string newName : type of the radio
 *  bool newOn : whether or not the radio is on
 *  Freqs* newFreqs: array of TOTAL_FREQS frequency pairs - presets.
 * RETURNS: none
 */
PioneerCarRadio::PioneerCarRadio(string newName, bool on, Freqs* freqs): 
    AmFmRadio(on, freqs) {
        name = newName;
}

/* FUNCTION: PioneerCarRadio::~PioneerCarRadio
 * DESCRIPTION:
 *  Prints "Dstroying Pioneer <type> Radio" to stdout.
 * PARAMETERS: none
 * RETURNS: none
 */
PioneerCarRadio::~PioneerCarRadio(void) {
    printf("Destroing Pioneer %s Radio\n", name.c_str());
}

/* FUNCTION: PioneerCarRadio::HandleCommands
 * DESCRIPTION:
 *  Loops and accepts used command (1 char at a time)
 *  Depending on the command, can perform following actions:
 *  'o' to toggle on/off
 *  '+' and '_' to turn the volume up or down, respectively
 *  '=' and '-' to scan frequencies up or down, respectively
 *  'b' to toggle AM/FM
 *  '1' to '5' to select the preset
 *  Shift + '1' to '5' (!@#$%) to set the preset
 *  'x' to stop accepting commands and quit
 *  After each keystroke prints the current settings.
 * PARAMTERES: none
 * RETURNS: none
 */
void PioneerCarRadio::HandleCommands(void) {
    char command = 0;
    ShowCurrentSettings();
    do {
        command = getch();
        if (IsRadioOn() || command == 'o') { 
            switch (command) { // determining the action
                case 'o': 
                    PowerToggle();
                    break;
                case '+':
                    SetVolume(GetVolume() + 1);
                    break;
                case '_':
                    SetVolume(GetVolume() - 1);
                    break;
                case '=':
                    ScanUp();
                    break;
                case '-':
                    ScanDown();
                    break;
                case 'b':
                    ToggleFrequency();
                    break;
                case '1': // these conveniently 
                case '2': // have successive ascii values
                case '3':
                case '4':
                case '5':
                    SelectCurrentStation(command - '1');
                    break;
                case '!': // these have successive
                case '#': // ascii values too,
                case '$': // except for the @ (Shift + 2)
                case '%':
                    SetButton(command - '!');
                    break;
                case '@':
                    SetButton(1);
                    break;
            }
            ShowCurrentSettings();
        }
    } while (command != 'x');
}

/* FUNCTION: PioneerCarRadio::ShowCurrentSettings
 * DESCRIPTION:
 *  Method to print all current settings of the radio to stdout.
 *  If the radio is off, it stops at that. Otherwise, prints
 *  the full information.
 * PARAMETERS: none
 * RETURNS: none
 */
void PioneerCarRadio::ShowCurrentSettings(void) {
    bool on = IsRadioOn();
    printf("\nPioneer %s\n", name.c_str());
    printf("Radio is %s\n", on ? "on" : "off");
    if (on) {
        printf("Volume: %d\n", GetVolume());
        if (strcmp(GetFrequency(), "AM") == 0) {
            printf("Current Station: %4d AM\n", (int)GetCurrentStation());
        } else {
            printf("Current Station: %5.1f FM\n", GetCurrentStation());
        }
        printf("AM Buttons:\n");
        for (int i = 0; i < TOTAL_FREQS; ++i) {
            printf("%d: %5d", i + 1, GetFreqs()[i].AMFreq);
            printf(i + 1 == TOTAL_FREQS ? "\n" : ", ");
        }
        if (name != "XS440-AM") {
            printf("FM Buttons:\n");
            for (int i = 0; i < TOTAL_FREQS; ++i) {
                printf("%d: %5.1f", i + 1, GetFreqs()[i].FMFreq);
                printf(i + 1 == TOTAL_FREQS ? "\n" : ", ");
            }
        }
    }
}

/* FUNCTION: PioneerCarRadio::GetName
 * DESCRIPTION:
 *  Accessor for the name data member. 
 * PARAMETERS: none
 * RETURNS: 
 *  string : a copy of the name
 */ 
string PioneerCarRadio::GetName(void) {
    return name;
}