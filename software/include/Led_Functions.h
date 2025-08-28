#pragma once

#include "Arduinoboy.h"



void showSelectedMode(void);
void updateVisualSync(void);
void updateBlinkLights(void);
void updateStatusLight(void);
void blinkLight(byte midiMessage, byte midiValue);
void updateProgrammerLeds(void);
void updateStatusLed(void);
void statusLedOn(void);
void startupSequence(void);
