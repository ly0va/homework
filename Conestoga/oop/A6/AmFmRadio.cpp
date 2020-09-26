/* FILE: AmFmRadio.cpp
 * PROJECT: PROG 1385 - Assignment 6
 * PROGRAMMER: Lev Potomkin
 * FIRST VERSION: Feb 23, 2019
 * DESCRIPTION:
 *  This file contains all methods for the AmFmRadio class.
 *  This includes
 *  - 2 constructors
 *  - destructor
 *  - accessors:
 *      bool IsRadioOn(void);
 *      Freqs* GetFreqs(void);
 *      double GetCurrentStation(void);
 *      char* GetFrequency(void);
 *      int GetVolume(void);
 *      bool GetDisplayOutput(void);
 *  - mutators:
 *      void PowerToggle(void);
 *      void ToggleFrequency(void);
 *      void ToggleDisplayOutput(void);
 *      int SetButton(int button_num);
 *      int SelectCurrentStation(int button_num);
 *      int SetCurrentStation(double new_station);
 *      int SetVolume(void);
 *      int SetVolume(int newVolume);
 *  - methods:
 *      void ShowCurrentSettings(void);
 *      void ScanUp(void);
 *      void ScanDown(void);
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AmFmRadio.h"

/* FUNCTION: AmFmRadio::AmFmRadio
 * DESCRIPTION:
 *  Constructor of the AmFmRadio class.
 *  Accepts whether or not the radio is on.
 *  Sets other data members to default values.
 * PARAMETERS: 
 *  bool newOn : optional (default = false), 
 *               whether or not the radio is on. 
 * RETURNS: none
 */
AmFmRadio::AmFmRadio(bool newOn) {
    for (int i = 0; i < TOTAL_FREQS; ++i) {
        freqs[i].AMFreq = BEGIN_AM;
        freqs[i].FMFreq = BEGIN_FM;
    }
    current_station = BEGIN_AM;
    lastStations = freqs[0];
    strcpy(frequency, "AM");
    lastVolume = volume = 0;
    on = newOn;
    displayOutput = false;
}

/* FUNCTION: AmFmRadio::AmFmRadio
 * DESCRIPTION:
 *  Constructor of the AmFmRadio class.
 *  Accepts whether or not the radio is on and an 
 *  array of struct Freqs - presets.
 *  Sets other data members to default values.
 * PARAMETERS: 
 *  bool newOn : whether or not the radio is on
 *  Freqs* newFreqs: array of TOTAL_FREQS frequency pairs - presets.
 * RETURNS: none
 */
AmFmRadio::AmFmRadio(bool newOn, Freqs* newFreqs) {
    for (int i = 0; i < TOTAL_FREQS; ++i) {
        freqs[i] = newFreqs[i];
    }
    current_station = freqs[0].AMFreq;
    lastStations = freqs[0];
    strcpy(frequency, "AM");
    lastVolume = volume = 0;
    on = newOn;
    displayOutput = false;
}

/* FUNCTION: AmFmRadio::~AmFmRadio
 * DESCRIPTION:
 *  If displayOutput is true, prints "Destroying AmFmRadio"
 *  to stdout.
 * PARAMETERS: none
 * RETURNS: none
 */
AmFmRadio::~AmFmRadio(void) {
    if (displayOutput) {
        printf("Destroying AmFmRadio\n");
    }
}

/* FUNCTION: AmFmRadio::IsRadioOn
 * DESCRIPTION:
 *  Accessor of `bool on` data mebmer.
 * PARAMETERS: none
 * RETURNS: 
 *  bool: the value of `on` data member
 */
bool AmFmRadio::IsRadioOn(void) {
    return on;
}

/* FUNCTION: AmFmRadio::GetFreqs
 * DESCRIPTION:
 *  Accessor of `Freqs* freqs` data mebmer.
 * PARAMETERS: none
 * RETURNS: 
 *  Freqs*: the copy of `freqs` array
 */
Freqs* AmFmRadio::GetFreqs(void) {
    static Freqs freqsCopy[TOTAL_FREQS];
    for (int i = 0; i < TOTAL_FREQS; i++) {
        freqsCopy[i] = freqs[i];
    }
    return freqsCopy;
}

/* FUNCTION: AmFmRadio::GetCurrentStation
 * DESCRIPTION:
 *  Accessor of `double current_station` data mebmer.
 * PARAMETERS: none
 * RETURNS: 
 *  doubel: the value of `current_station` data member
 */
double AmFmRadio::GetCurrentStation(void) {
    return current_station;
}

/* FUNCTION: AmFmRadio::GetFrequency
 * DESCRIPTION:
 *  Accessor of `char* frequency` data mebmer.
 * PARAMETERS: none
 * RETURNS: 
 *  char*: string containting copy of `frequency` data member
 */
const char* AmFmRadio::GetFrequency(void) {
    return strcmp(frequency, "AM") == 0 ? "AM" : "FM";
}

/* FUNCTION: AmFmRadio::GetVolume
 * DESCRIPTION:
 *  Accessor of `int volume` data mebmer.
 * PARAMETERS: none
 * RETURNS: 
 *  int: the value of `volume` data member
 */
int AmFmRadio::GetVolume(void) {
    return volume;
}

/* FUNCTION: AmFmRadio::GetDisplayOutput
 * DESCRIPTION:
 *  Accessor of `bool displayOutput` data mebmer.
 * PARAMETERS: none
 * RETURNS: 
 *  bool: the value of `displayOutput` data member
 */
bool AmFmRadio::GetDisplayOutput(void) {
    return displayOutput;
}

/* FUNCTION: AmFmRadio::PowerToggle
 * DESCRIPTION:
 *  Mutator of `bool on` data mebmer.
 *  If on was true, sets to false and vice versa.
 * PARAMETERS: none
 * RETURNS: none
 */
void AmFmRadio::PowerToggle(void) {
    if (on) {
        on = false;
        lastVolume = volume;
        volume = 0;
    } else {
        on = true;
        volume = lastVolume;
    }
}

/* FUNCTION: AmFmRadio::ToggleFrequency
 * DESCRIPTION:
 *  Mutator of `char* frequency` data mebmer.
 *  If frequency was "AM", sets to "FM" and vice versa.
 * PARAMETERS: none
 * RETURNS: none
 */
void AmFmRadio::ToggleFrequency(void) {
    if (strcmp(frequency, "AM") == 0) {
        strcpy(frequency, "FM");
        lastStations.AMFreq = current_station;
        current_station = lastStations.FMFreq;
    } else {
        strcpy(frequency, "AM");
        lastStations.FMFreq = current_station;
        current_station = lastStations.AMFreq;
    }
}

/* FUNCTION: AmFmRadio::ToggleDisplayOutput
 * DESCRIPTION:
 *  Mutator of `bool displayOutput` data mebmer.
 *  If displayOutput was true, sets to false and vice versa.
 * PARAMETERS: none
 * RETURNS: 
 *  bool: the value of `on` data member
 */
void AmFmRadio::ToggleDisplayOutput(void) {
    displayOutput = !displayOutput;
}

/* FUNCTION: AmFmRadio::SetVolume
 * DESCRIPTION:
 *  Mutator of `int volume` data mebmer.
 *  Accepts input from stdout. 
 *  If requested value < 0, sets to 0
 *  If requested value > 100, sets to 100
 * PARAMETERS: none
 * RETURNS: 
 *  int: 0 if set to 0, 2 if set to 100, 1 otherwise.
 */
int AmFmRadio::SetVolume(void) {
    char buf[BUFFER_SIZE] = "";
    printf("\nEnter the volume level (0 - 100). ");
    fgets(buf, sizeof buf, stdin);
    return SetVolume(atoi(buf));
}

/* FUNCTION: AmFmRadio::SetVolume
 * DESCRIPTION:
 *  Mutator of `int volume` data mebmer.
 *  Accepts input as an argument. 
 *  If requested value < 0, sets to 0
 *  If requested value > 100, sets to 100
 * PARAMETERS: 
 *  int newVolume: value to be set
 * RETURNS: 
 *  int: 0 if set to 0, 2 if set to 100, 1 otherwise.
 */
int AmFmRadio::SetVolume(int newVolume) {
    volume = newVolume;
    if (volume < 0) {
        volume = 0;
        return VOLUME_ZERO;
    }
    if (volume > MAX_VOLUME) {
        volume = MAX_VOLUME;
        return VOLUME_MAX;
    }
    return VOLUME_OK;
}

/* FUNCTION: AmFmRadio::SetCurrentStation
 * DESCRIPTION:
 *  Mutator of `double current_station` data mebmer.
 *  Accepts input as an argument. 
 *  For AM band should be from 530 to 1700 
 *  For FM - from 87.9 to 107.9
 * PARAMETERS: 
 *  double new_station: value to be set
 * RETURNS: 
 *  int: 1 if set successfully, 0 otherwise
 */
int AmFmRadio::SetCurrentStation(double new_station) {
    if (strcmp(frequency, "AM") == 0 && 
        new_station >= BEGIN_AM && new_station <= END_AM) {
            current_station = new_station;
            return 1;
    }
    if (strcmp(frequency, "FM") == 0 && 
        new_station >= BEGIN_FM && new_station <= END_FM) {
            current_station = new_station;
            return 1;
    }
    return 0;
}

/* FUNCTION: AmFmRadio::SetButton
 * DESCRIPTION:
 *  Mutator of `Freqs* freqs` data mebmer.
 *  Sets a field of freqs[button_num] to current_station
 * PARAMETERS: 
 *  int button_num: index of the preset, from 0 to 4
 * RETURNS: 
 *  int: 1 if set successfully, 0 otherwise
 */
int AmFmRadio::SetButton(int button_num) {
    if (button_num >= 0 && button_num <= 4) {
        if (strcmp("AM", frequency) == 0) {
            freqs[button_num].AMFreq = current_station;
        } else {
            freqs[button_num].FMFreq = current_station;
        }
        return 1;
    }
    return 0;
}

/* FUNCTION: AmFmRadio::SelectCurrentStation
 * DESCRIPTION:
 *  Mutator of `double current_station` data mebmer.
 *  Sets current_station to a field of freqs[button_num]
 * PARAMETERS: 
 *  int button_num: index of the preset, from 0 to 4
 * RETURNS: 
 *  int: 1 if set successfully, 0 otherwise
 */
int AmFmRadio::SelectCurrentStation(int button_num) {
    if (button_num >= 0 && button_num <= 4) {
        if (strcmp("AM", frequency) == 0) {
            current_station = freqs[button_num].AMFreq;
        } else {
            current_station = freqs[button_num].FMFreq;
        }
        return 1;
    }
    return 0;
}

/* FUNCTION: AmFmRadio::ShowCurrentSettings
 * DESCRIPTION:
 *  Method to print all current settings of the radio to stdout.
 * PARAMETERS: none
 * RETURNS: none
 */
void AmFmRadio::ShowCurrentSettings(void) {
    printf("\n\nRadio is %s. \n", on ? "on" : "off");
    printf("\nFrequency: %s\n", frequency);
    printf("Volume: %d\n", volume);
    if (strcmp(frequency, "AM") == 0) {
        printf("Current Station: %d AM\n", (int)current_station);
    } else {
        printf("Current Station: %.1f FM\n", current_station);
    }
    printf("AM Button Settings: ");
    for (int i = 0; i < TOTAL_FREQS; ++i) {
        printf("%d) %6d ", i + 1, freqs[i].AMFreq);
    }
    printf("\nFM Button Settings: ");
    for (int j = 0; j < TOTAL_FREQS; ++j) {
        printf("%d) %6.1f ", j + 1, freqs[j].FMFreq);
    }
}

/* FUNCTION: AmFmRadio::ScanUp
 * DESCRIPTION:
 *  Method to change the frequency of current_station.
 *  If on AM band, increment by 10, otherwise by 0.2
 *  If maximum frequency reached, roll down to the minimum frequency.
 *  Also, print to stdout (optional)
 * PARAMETERS: none
 * RETURNS: none
 */
void AmFmRadio::ScanUp(void) {
    if (strcmp("AM", frequency) == 0) {
        if (current_station >= END_AM) {
            current_station = BEGIN_AM;
        } else {
            current_station += DELTA_AM;
        }
    } else {
        if (current_station >= END_FM) {
            current_station = BEGIN_FM;
        } else {
            current_station += DELTA_FM;
        }
    }
    if (displayOutput) {
        printf("\nCurrent station: %f %s\n", 
               current_station, frequency);
    }
}

/* FUNCTION: AmFmRadio::ScanDown
 * DESCRIPTION:
 *  Method to change the frequency of current_station.
 *  If on AM band, decrement by 10, otherwise by 0.2
 *  If minimum frequency reached, roll up to the maximum frequency.
 *  Also, print to stdout (optional)
 * PARAMETERS: none
 * RETURNS: none
 */
void AmFmRadio::ScanDown(void) {
    if (strcmp("AM", frequency) == 0) {
        if (current_station <= BEGIN_AM) {
            current_station = END_AM;
        } else {
            current_station -= DELTA_AM;
        }
    } else {
        if (current_station <= BEGIN_FM) {
            current_station = END_FM;
        } else {
            current_station -= DELTA_FM;
        }
    }
    if (displayOutput) {
        printf("\nCurrent station: %f %s\n", 
               current_station, frequency);
    }
}

