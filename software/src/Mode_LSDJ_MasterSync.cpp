/**************************************************************************
 *  Name:   Timothy Lamb                                                  *
 *  Email:  trash80@gmail.com                                             *
 **************************************************************************/
/**************************************************************************
 *                                                                        *
 *  This program is free software; you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation; either version 2 of the License, or     *
 *  (at your option) any later version.                                   *
 *                                                                        *
 **************************************************************************/

#include "Mode_LSDJ_MasterSync.h"

#include "Led_Functions.h"
#include "Mode_Programmer.h"
#include "Mode.h"


void modeLSDJMasterSyncSetup(void);
void modeLSDJMasterSync(void);
void checkActions(void);
boolean checkLSDJStopped(void);
void sendMidiClockSlaveFromLSDJ(void);


void modeLSDJMasterSyncSetup()
{
    digitalWrite(pinStatusLed, LOW);
    pinMode(pinGBClock, INPUT);

    blinkMaxCount = 1000;
    countSyncTime = 0;

    modeLSDJMasterSync();
}


void modeLSDJMasterSync()
{
    while (1) {
        setMode();    // check if the mode button was depressed

        #ifdef USE_TEENSY
            while (usbMIDI.read()) ;
        #endif

        if (serial->available()) {                // if serial data was send to midi input
            incomingMidiByte = serial->read();    // read it
            checkForProgrammerSysex(incomingMidiByte);
        }

        readgbClockLine = digitalRead(pinGBClock);            // read gameboy's clock line
        if (readgbClockLine) {                                // if Gb's Clock is On
            while (readgbClockLine) {                         // loop untill its off
                readgbClockLine = digitalRead(pinGBClock);    // read the clock again
                bit = digitalRead(pinGBSerialIn);             // read the serial input for song position
                checkActions();
            }

            countClockPause = 0;                      // reset our wait timer for detecting a sequencer stop

            readGbSerialIn = readGbSerialIn << 1;     // left shift the serial byte by one to append new bit from last loop
            readGbSerialIn = readGbSerialIn + bit;    // and then add the bit that was read

            sendMidiClockSlaveFromLSDJ();             // send the clock & start offset data to midi
        }
    }
}


void checkActions()
{
    checkLSDJStopped();    // check if LSDJ hit Stop
    setMode();
    updateStatusLight();
}


/*
    checkLSDJStopped counts how long the clock was on, if its been on too long we assume
    LSDJ has stopped- Send a MIDI transport stop message and return true.
*/
boolean checkLSDJStopped()
{
    countClockPause++;                // increment the counter
    if (countClockPause > 16000) {    // if we've reached our waiting period
        if (sequencerStarted) {
            readgbClockLine = false;
            countClockPause = 0;          // reset our clock
            serial->write(midi::Stop);    // send the transport stop message
            #ifdef USE_TEENSY
                usbMIDI.sendRealTime(midi::Stop);
            #endif
            #ifdef HAS_USB_MIDI
                midiEventPacket_t event = {0x0F, midi::Stop};
                MidiUSB.sendMIDI(event);
                MidiUSB.flush();
            #endif
            sequencerStop();    // call the global sequencer stop function
        }
        return true;
    }
    return false;
}


/*
    sendMidiClockSlaveFromLSDJ waits for 8 clock bits from LSDJ,
    sends the transport start command if sequencer hasnt started yet,
    sends the midi clock tick, and sends a note value that corrisponds to
    LSDJ's row number on start (LSDJ only sends this once when it starts)
*/
void sendMidiClockSlaveFromLSDJ()
{
    if (!countGbClockTicks) {                                          // if we hit 8 bits
        if (!sequencerStarted) {                                       // if the sequencer hasnt started
            serial->write((0x90 + memory[MEM_LSDJMASTER_MIDI_CH]));    // send the midi channel byte
            serial->write(readGbSerialIn);                             // send the row value as a note
            serial->write(0x7F);                                       // send a velocity 127
            serial->write(midi::Start);                                // send MIDI transport start message

            #ifdef USE_TEENSY
                usbMIDI.sendNoteOn(memory[MEM_LSDJMASTER_MIDI_CH] + 1, readGbSerialIn, 0x7F);
                usbMIDI.sendRealTime(0xFA);
            #endif
            #ifdef HAS_USB_MIDI
                midiEventPacket_t event = {0x09, (uint8_t)(0x90 | memory[MEM_LSDJMASTER_MIDI_CH]), readGbSerialIn, 0x7F};
                MidiUSB.sendMIDI(event);
                MidiUSB.flush();
                event = {0x0F, midi::Start};
                MidiUSB.sendMIDI(event);
                MidiUSB.flush();
            #endif
            sequencerStart();    // call the global sequencer start function
        }
        serial->write(midi::Clock);    // send the MIDI Clock Tick

        #ifdef USE_TEENSY
            usbMIDI.sendRealTime(midi::Clock);
        #endif
        #ifdef HAS_USB_MIDI
            midiEventPacket_t event = {0x0F, midi::Clock};
            MidiUSB.sendMIDI(event);
            MidiUSB.flush();
        #endif
        countGbClockTicks = 0;    // reset the bit counter
        readGbSerialIn = 0x00;    // reset our serial read value

        updateVisualSync();
    }
    countGbClockTicks++;    // increment the bit counter
    if (countGbClockTicks == 8) countGbClockTicks = 0;
}
