/* FILE: driver.cpp
 * PROJECT: PROG 1385 - Assignment 3
 * PROGRAMMER: Lev Potomkin
 * FIRST VERSION: Feb 23, 2019
 * DESCRIPTION: 
 *  This file contains user interface for the AmFmRadio.
 *  Displayed menu has 9 options:
 *  1. Toggle power
 *  2. Set volume
 *  3. Toggle band
 *  4. Set button
 *  5. Select button
 *  6. Show current settings
 *  7. Scan up
 *  8. Scan down
 *  9. Quit.
 *  All input is accepted through stdin and output printed to stdout.
 *  Interface exposed basic functionality of the AmFmRadio class found in 
 *  AmFmRadio.h
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "AmFmRadio.h"

#include <iostream>
using namespace std;

// Constants that denote menu options: 1 through 9
// Names are self-descriptive
enum menuItems {
    kMenuNothing = 0,      // special constant for initialization only
    kMenuTogglePower = 1,
    kMenuSetVolume, 
    kMenuToggleAMFM, 
    kMenuSetButton, 
    kMenuSelectButton,
    kMenuShowCurrentSettings, 
    kMenuScanUp, 
    kMenuScanDown, 
    kMenuQuit
};


int main() {
    int volume_OK = 0;
    int button_OK = 0;
    int button_num = 0;
    menuItems choice = kMenuNothing;
    char buf[BUFFER_SIZE] = "";
    AmFmRadio jazzy(true);
    bool on = false;
    // cout << "a";
    do {
        // printing menu
        printf("\n\nMAIN MENU\n");
        printf("=========\n\n");
        printf("1.  Toggle Power\n");
        printf("2.  Set Volume\n");
        printf("3.  Toggle AM / FM\n");
        printf("4.  Set a Button \n"); 
        printf("5.  Select a Button \n"); 
        printf("6.  Show Current Settings\n"); 
        printf("7.  Scan Up \n"); 
        printf("8.  Scan Down \n"); 
        printf("9.  Quit the Program\n");
        printf("\nMake a selection from the menu\n");
        fgets(buf, sizeof buf, stdin);
        choice = (menuItems) atoi(buf);
        on = jazzy.IsRadioOn();
        // performing actions depending on the option
        switch (choice) {
            case kMenuTogglePower:
                jazzy.PowerToggle();
                break;
            case kMenuSetVolume: 
                if (on) {
                    volume_OK = jazzy.SetVolume();
                    if (volume_OK == VOLUME_ZERO) {
                        printf("\nVolume was set to 0.");
                    } else if (volume_OK == VOLUME_MAX) {
                        printf("\nVolume was set to 100.");
                    }
                } else {
                    printf("\nThe radio must be turned on before the "
                           "volume can be set!");
                }
                break;
            case kMenuToggleAMFM:
                if (on) {
                    jazzy.ToggleFrequency();
                } else {
                    printf("\nThe radio must be turned on before the "
                        "band can be toggled!");
                }
                break;
            case kMenuSetButton:
                if (on) {
                    printf("\nWhich button do you want to set?");
                    fgets(buf, sizeof buf, stdin);
                    button_num = atoi(buf) - 1;
                    button_OK = jazzy.SetButton(button_num);
                    if (button_OK == 0) {
                        printf("\nYou entered an invalid button number!");
                    }
                } else {
                    printf("\nYou must turn the radio on before "
                           "you set the buttons!\n");
                }
                break;
            case kMenuSelectButton:
                if (on) {
                    printf("\nEnter the number of the button: ");
                    fgets(buf, 20, stdin);
                    button_num = atoi(buf) - 1;
                    button_OK = jazzy.SelectCurrentStation(button_num);
                    if (button_OK == 0) {
                        printf("\nYou entered an invalid button number!");
                    }
                } else {
                    printf("\nYou must turn the radio on before "
                           "you set the buttons!\n");
                }
                break;
            case kMenuShowCurrentSettings:
                jazzy.ShowCurrentSettings();
                break;
            case kMenuScanUp:
                if (on) {
                    jazzy.ScanUp();
                } else {
                    printf("\nYou must turn the radio on before "
                           "you can use the scan button!\n");
                }
                break;
            case kMenuScanDown:
                if (on) {
                    jazzy.ScanDown();
                } else {
                    printf("\nYou must turn the radio on before "
                           "you can use the scan button!\n");
                }
                break;
            case kMenuQuit:
                break;
            default:
                printf("You have entered an invalid selection."
                       "Please make \nanother selection.\n");
                break;
        }
        if (choice != kMenuShowCurrentSettings && choice != kMenuQuit) {
            jazzy.ShowCurrentSettings();
        }
    } while (choice != kMenuQuit);

    printf("\nGoodbye!\n");
    return 0;
}