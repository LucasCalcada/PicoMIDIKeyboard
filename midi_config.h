#include "stdio.h"
/*
    Keyboard key pins
    *** MUST BE MULTIPLE OF 12 (one entire octave) ***
*/ 
const uint8_t PINS[] = {0,1,2,3,4,5,6,7,8,9,10,11};

/*
    Keyboard notes
    *** MUST BE THE SAME LENGTH AS PINS[] ***
*/
uint8_t NOTES[] = {
    24, // C0
    25, // C#0
    26, // D0
    27, // D#0
    28, // E0
    29, // F0
    30, // F#0
    31, // G0
    32, // G#0
    33, // A0
    34, // A#0
    35  // B0
};

/*
    Octaves
*/

const uint8_t OCTAVE_AMMOUNT = 1;
const uint8_t INITIAL_OCTAVE_OFFSET = 2; // MUST BE LOWER THAN 8 - OCTAVE_AMMOUNT

//  Pins to offset notes in octaves
const uint8_t OCTAVE_UP = 12;
const uint8_t OCTAVE_DOWN = 13;

const uint8_t MIDI_CHANNEL = 0;
const uint8_t MIDI_JACK = 0;      // MIDI jack associated with USB endpoint
const uint8_t TASK_INTERVAL = 10; // Interval to prevent double clicks (default = 10) 