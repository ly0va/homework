/* FILE: AmFmRadio.cpp
 * PROJECT: PROG 1385 - Assignment 5
 * PROGRAMMER: Lev Potomkin
 * FIRST VERSION: Feb 23, 2019
 * DESCRIPTION: 
 *  This file containts constants used in AmFmRadio class methods
 *  as well as the declaration of AmFmRadio class itself.
 *  Also it declares a supplemental struct Freqs that holds
 *  2 Frequencies: for AM and FM bands.
 */ 

#ifndef _AMFMRADIO_H
#define _AMFMRADIO_H

#define BEGIN_AM 530    // minimum frequency of AM band
#define END_AM 1700     // maximum frequency of AM band
#define DELTA_AM 10     // scanning step for AM band
#define BEGIN_FM 87.9   // minimum frequency of FM band
#define END_FM 107.9    // maximum frequency of FM band
#define DELTA_FM 0.2    // scanning step for FM band
#define TOTAL_FREQS 5   // total number of presets
#define BAND_LENGTH 3   // size of char[] that holds "AM"/"FM" label
#define MAX_VOLUME 100  // maximum volume
#define BUFFER_SIZE 20  // size of char[] that holds user input
#define VOLUME_ZERO 0   // constant denoting volume was set to 0
#define VOLUME_OK 1     // constant denoting volume was set as expected
#define VOLUME_MAX 2    // constant denoting volume was set to 100

// holds 2 frequencies: for AM and FM bands
struct Freqs {
    int AMFreq;
    double FMFreq;
};

/* NAME: AmFmRadio
 * PURPOSE: The AmFmRadio class has been created to model the AM/FM Radio.
 *   It has an on/off state, tracks the current playing station, 5 presets
 *   volume and band. Displaying output is optional. 
 *   Class has the ability to get/set the member values, as well as some
 *   supplemental methods for displaying settings and scanning frequencies.
 */
class AmFmRadio {

private:
    Freqs freqs[TOTAL_FREQS];     // holds 5 presets
    double current_station;       // frequency of currently plaing station
                                  // 87.9 to 107.9 for FM, 530 to 1700 for AM
    char frequency[BAND_LENGTH];  // current band: AM or FM
    int volume;                   // current volume: 0 to 100
    bool on;                      // whether or not the radio is on
    bool displayOutput;           // whether or not to display output
    Freqs lastStations;           // holds frequency of last playing 
                                  // station for each band
    int lastVolume;               // holds volume that was set before power-off

public:
    // constructors
    AmFmRadio(bool on = false);      // initializes presets to default values
    AmFmRadio(bool on, Freqs* freqs);// initializes presets to passed values

    // destructor
    ~AmFmRadio(void);

    // methods
    void ShowCurrentSettings(void);    // prints settings to stdout
    void ScanUp(void);                 // changes current station
    void ScanDown(void);               // changes current station

    // accessors
    bool IsRadioOn(void);
    Freqs* GetFreqs(void);
    double GetCurrentStation(void);
    const char* GetFrequency(void);
    int GetVolume(void);
    bool GetDisplayOutput(void);

    // mutators
    void PowerToggle(void);
    void ToggleFrequency(void);
    void ToggleDisplayOutput(void);
    int SetButton(int button_num);
    int SelectCurrentStation(int button_num);
    int SetCurrentStation(double new_station);
    int SetVolume(void);
    int SetVolume(int newVolume);
};
#endif