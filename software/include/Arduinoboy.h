#pragma once

#include <Arduino.h>
#include "MCU_Pin_Assignments.h"

#ifndef USE_DUE
    #include <EEPROM.h>
#endif



#define MEM_MAX 65
#define NUMBER_OF_MODES 7    // Right now there are 7 modes, Might be more in the future

// !!! do not edit these, they are the position in EEPROM memory that contain the value of each stored setting
#define MEM_CHECK 0
#define MEM_VERSION_FIRST 1
#define MEM_VERSION_SECOND 2
#define MEM_MODE 5
#define MEM_FORCE_MODE 4

#define MEM_LSDJSLAVE_MIDI_CH 6

#define MEM_LSDJMASTER_MIDI_CH 7
#define MEM_KEYBD_CH 8

#define MEM_KEYBD_COMPAT_MODE 9
#define MEM_KEYBD_CH_TO_INST 10

#define MEM_MIDIOUT_NOTE_CH 11
#define MEM_MIDIOUT_CC_CH 15
#define MEM_MIDIOUT_CC_MODE 19
#define MEM_MIDIOUT_CC_SCALING 23
#define MEM_MIDIOUT_CC_NUMBERS 27

#define MEM_MGB_CH 55
#define MEM_LIVEMAP_CH 60

#define MEM_MIDIOUT_BIT_DELAY 61
#define MEM_MIDIOUT_BYTE_DELAY 63

// #define PRO_MICRO // define this for Pro Micro custom Arduino (not detectable from regular defines)


// extern interface:

/***************************************************************************
* User Settings
***************************************************************************/

extern boolean usbMode;
extern byte defaultMemoryMap[MEM_MAX];
extern byte memory[MEM_MAX];


/***************************************************************************
* Lets Assign our Arduino Pins .....
***************************************************************************/

extern HardwareSerial *serial;


/***************************************************************************
* Memory
***************************************************************************/

extern boolean alwaysUseDefaultSettings;


/***************************************************************************
* Sysex Settings & vars
***************************************************************************/

extern boolean sysexReceiveMode;
extern boolean sysexProgrammingConnected;
extern unsigned long sysexProgrammerWaitTime;
extern unsigned long sysexProgrammerCallTime;
extern unsigned long sysexProgrammerLastSent;
extern boolean sysexProgrammingMode;
extern unsigned long sysexProgrammerLastResponse;
extern byte sysexManufacturerId;
extern int sysexPosition;
extern byte sysexData[128];
extern byte longestSysexMessage;
extern int midioutBitDelay;
extern int midioutByteDelay;


/***************************************************************************
* Switches and states
***************************************************************************/

extern boolean sequencerStarted;
extern boolean midiSyncEffectsTime;
extern boolean midiNoteOnMode;
extern boolean midiProgramChange;
extern boolean midiAddressMode;
extern boolean midiValueMode;
extern int midiOutLastNote[4];
extern boolean statusLedIsOn;
extern boolean statusLedBlink;
extern boolean nanoState;
extern boolean nanoSkipSync;
extern int buttonDepressed;
extern boolean blinkSwitch[6];
extern unsigned long int blinkSwitchTime[6];
extern uint8_t switchLight;
extern uint16_t blinkMaxCount;
extern unsigned long midioutNoteTimer[4];
extern byte midioutNoteHold[4][4];
extern byte midioutNoteHoldCounter[4];
extern int midioutNoteTimerThreshold;


/***************************************************************************
* Counter vars
***************************************************************************/

extern int countLSDJTicks;
extern int countSyncTime;
extern int countSyncLightTime;
extern int countSyncSteps;
extern int countSyncPulse;
extern int countGbClockTicks;
extern int countClockPause;
extern int countStatusLedOn;
extern int miscLastLed;
extern unsigned long int miscLedTime;
extern unsigned long int miscLedMaxTime;


/***************************************************************************
* Inbound Data Placeholders
***************************************************************************/

extern byte incomingMidiByte;
extern byte readgbClockLine;
extern byte readGbSerialIn;
extern byte bit;
extern byte midiData[3];        // array size defined implicitly
extern byte lastMidiData[3];    // array size defined implicitly
extern int lastMode;
extern byte midiDefaultStartOffset;
extern byte midiStatusType;
extern byte midiStatusChannel;



/***************************************************************************
* LSDJ Keyboard mode settings
***************************************************************************/

extern byte keyboardNotes[24];    // array size defined implicitly
extern byte keyboardOctDn;
extern byte keyboardOctUp;
extern byte keyboardInsDn;
extern byte keyboardInsUp;
extern int keyboardCurrentOct;
extern int keyboardCurrentIns;
extern int keyboardLastOct;
extern int keyboardLastIns;
extern int keyboardDiff;
extern int keyboardCount;
extern byte keyboardStartOctave;
extern byte keyboardNoteStart;
extern byte keyboardNoteOffset;
extern byte keyboardCommands[12];


/***************************************************************************
* LSDJ Midi Map mode vars
***************************************************************************/

extern int mapCurrentRow;
extern int mapQueueMessage;
extern unsigned long mapQueueTime;
extern uint8_t mapQueueWaitSerial;
extern uint8_t mapQueueWaitUsb;


/***************************************************************************
* mGB Settings
***************************************************************************/

#define GB_MIDI_DELAY 500    // Microseconds to delay the sending of a byte to gb
