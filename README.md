# Pico MIDI Keyboard
MIDI Controller firmware for the Raspberry Pi Pico microcontroller  
Available languages: [:brazil:](/assets/readmes/pt-br.md), [:us:](README.md)  
![Default config pinout](/assets/pinout.png "Default config pinout")
## Building the project
If you don't have the pico-sdk downloaded start by running the following commands
*(don't forget to replace ```<PATH-TO-PICO-SDK>``` with your actual SDK path)*:
```
$ git clone https://github.com/raspberrypi/pico-sdk.git --branch master
$ cd pico-sdk
$ git submodule update --init
$ cd ..
$ export PICO_SDK_PATH=<PATH-TO-PICO-SDK>
```
Then, run the following commands to download and build the project
```
$ git clone https://github.com/LucasCalcada/PicoMIDIKeyboard
$ cd PicoMIDIKeyboard
$ mkdir build
$ cd build
$ cmake ..
$ make
```
Finally, plug in the pico holding the BOOTSEL button and copy the MIDIKeyboard.uf2 file into the board's storage
## Installation
You can download a prebuilt version on the [releases](https://github.com/LucasCalcada/PicoMIDIKeyboard/releases/latest) section
***(It is recommended to build the project yourself, since you can customize the settings to your likings and needs)***  
The firmware can be installed by holding the pico's BOOTSEL button and copying the MIDIKeyboard.uf2 file into the board's storage
## Configuration
By editing the *midi_config.h* you can customize the funcionality of the keyboard
| Option | Description |
|--------|-------------|
| PINS[ ] | Sets each pin that will be used as key inputs |
| NOTES[ ] | Sets each note that corresponding pin will send |
| OCTAVE_AMMOUNT | Sets the number of octaves your keyboard will have (depends on the number of PINS you have set up | 
| INITIAL_OCTAVE_OFFSET | Sets the starting offset for the keyboard octave |
| OCTAVE_UP and OCTAVE_DOWN | Sets the pins to change the octave offset |