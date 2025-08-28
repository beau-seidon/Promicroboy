#pragma once

#include "Arduinoboy.h"


#if defined (__MK20DX256__) || defined (__MK20DX128__) || defined (__MKL26Z64__)
/***************************************************************************
* Teensy 3.2, Teensy LC
*
* Notes on Teensy: Pins are not the same as in the schematic, the mapping is below.
* Feel free to change, all related config in is this block.
* Be sure to compile
***************************************************************************/
    #define USE_TEENSY
    #define HAS_USB_MIDI
    #include <USB-MIDI.h>

    #if defined (__MKL26Z64__)
        #define GB_SET(bit_cl, bit_out, bit_in) GPIOB_PDOR = ((bit_in << 3) | (bit_out << 1) | bit_cl)
    #else
        #define GB_SET(bit_cl, bit_out, bit_in) GPIOB_PDOR = (GPIOB_PDIR & 0xfffffff4) | ((bit_in << 3) | (bit_out << 1) | bit_cl)
    #endif

    const int pinGBClock = 16;                        // Analog In 0 - clock out to gameboy
    const int pinGBSerialOut = 17;                    // Analog In 1 - serial data to gameboy
    const int pinGBSerialIn = 18;                     // Analog In 2 - serial data from gameboy
    const int pinMidiInputPower = 0;                  // Not used!
    const int pinStatusLed = 13;                      // Status LED
    const int pinLeds[] = {23, 22, 21, 20, 4, 13};    // LED Pins
    const int pinButtonMode = 2;                      // toggle button for selecting the mode


#elif defined (PRO_MICRO)
/***************************************************************************
* Pro Micro (ATmega32U4, with different pin config)
***************************************************************************/
    #define HAS_USB_MIDI
    #include <USB-MIDI.h>

    #define GB_SET(bit_cl, bit_out, bit_in) PORTF = (PINF & B00011111) | ((bit_cl << 7) | (bit_out << 6) | (bit_in << 5))
    // ^ The reason for not using digitalWrite is to allign clock and data pins for the GB shift reg.
    // Pin distribution comes from official Arduino Leonardo documentation

    const int pinGBClock     = A0;    // Analog In 0 - clock out to gameboy
    const int pinGBSerialOut = A1;    // Analog In 1 - serial data to gameboy
    const int pinGBSerialIn  = A2;    // Analog In 2 - serial data from gameboy
    const int pinMidiInputPower = 4; // power pin for midi input opto-isolator
    const int pinStatusLed = 14; // Status LED
    const int pinLeds[] = {8,9,7,10,16,14}; // LED Pins
    const int pinButtonMode = 3; //toggle button for selecting the mode


#elif defined (__AVR_ATmega32U4__)
/***************************************************************************
* Arduino Leonardo/Yún/Micro (ATmega32U4)
***************************************************************************/
    #define HAS_USB_MIDI
    #include <USB-MIDI.h>

    #define GB_SET(bit_cl, bit_out, bit_in) PORTF = (PINF & B00011111) | ((bit_cl << 7) | (bit_out << 6) | (bit_in << 5))
    // ^ The reason for not using digitalWrite is to align clock and data pins for the GB shift reg.
    // Pin distribution comes from official Arduino Leonardo documentation

    const int pinGBClock = A0;                       // Analog In 0 - clock out to gameboy
    const int pinGBSerialOut = A1;                   // Analog In 1 - serial data to gameboy
    const int pinGBSerialIn = A2;                    // Analog In 2 - serial data from gameboy
    const int pinMidiInputPower = 4;                 // power pin for midi input opto-isolator
    const int pinStatusLed = 13;                     // Status LED
    const int pinLeds[] = {12, 11, 10, 9, 8, 13};    // LED Pins
    const int pinButtonMode = 3;                     // toggle button for selecting the mode


#elif defined (__SAM3X8E__)
/***************************************************************************
* Arduino Due (ATmSAM3X8E)
***************************************************************************/
    #define USE_DUE
    #define HAS_USB_MIDI
    #include <USB-MIDI.h>
    #include <digitalWriteFast.h>

    #define GB_SET(bit_cl, bit_out, bit_in) digitalWriteFast(A0, bit_cl); digitalWriteFast(A1, bit_out); digitalWriteFast(A2, bit_in);
    // ^ The reason for not using digitalWrite is to align clock and data pins for the GB shift reg.

    const int pinGBClock = A0;                       // Analog In 0 - clock out to gameboy
    const int pinGBSerialOut = A1;                   // Analog In 1 - serial data to gameboy
    const int pinGBSerialIn = A2;                    // Analog In 2 - serial data from gameboy
    const int pinMidiInputPower = 4;                 // power pin for midi input opto-isolator
    const int pinStatusLed = 13;                     // Status LED
    const int pinLeds[] = {12, 11, 10, 9, 8, 13};    // LED Pins
    const int pinButtonMode = 3;                     // toggle button for selecting the mode


#else
/***************************************************************************
* Arduino UNO/Ethernet/Nano (ATmega328), Arduino UNO Wifi (ATmega4809) or Mega 2560 (ATmega2560/ATmega1280) (assumed)
***************************************************************************/
    #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
        #define GB_SET(bit_cl, bit_out, bit_in) PORTF = (PINF & B11111000) | ((bit_in << 2) | (bit_out << 1) | bit_cl)
    #elif defined(__AVR_ATmega4809__)
        #define GB_SET(bit_cl, bit_out, bit_in) PORTD = (PIND & B11111000) | ((bit_in << 2) | (bit_out << 1) | bit_cl)
    #else
        #define GB_SET(bit_cl, bit_out, bit_in) PORTC = (PINC & B11111000) | ((bit_in << 2) | (bit_out << 1) | bit_cl)
    #endif
    // ^ The reason for not using digitalWrite is to align clock and data pins for the GB shift reg.

    const int pinGBClock = A0;                       // Analog In 0 - clock out to gameboy
    const int pinGBSerialOut = A1;                   // Analog In 1 - serial data to gameboy
    const int pinGBSerialIn = A2;                    // Analog In 2 - serial data from gameboy
    const int pinMidiInputPower = 4;                 // power pin for midi input opto-isolator
    const int pinStatusLed = 13;                     // Status LED
    const int pinLeds[] = {12, 11, 10, 9, 8, 13};    // LED Pins
    const int pinButtonMode = 3;                     // toggle button for selecting the mode


#endif
