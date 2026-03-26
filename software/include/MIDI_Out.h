#pragma once

#include "Arduinoboy.h"

#include <MIDI.H>


extern midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> sMIDI;
extern midi::MidiInterface<usbMidi::usbMidiTransport> uMIDI;


void MIDI_sendRealTime(midi::MidiType t);
void MIDI_sendNoteOff(byte note, byte velocity, byte channel);
void MIDI_sendNoteOn(byte note, byte velocity, byte channel);
void MIDI_sendControlChange(byte number, byte value, byte channel);
void MIDI_sendProgramChange(byte number, byte channel);
