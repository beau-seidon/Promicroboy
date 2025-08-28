#pragma once

#include "Arduinoboy.h"
#include <MIDI.H>



extern midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> sMIDI;
extern midi::MidiInterface<usbMidi::usbMidiTransport> uMIDI;
