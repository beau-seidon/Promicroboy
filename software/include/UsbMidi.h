#pragma once

#include "Arduinoboy.h"



void usbMidiSendTwoByteMessage(uint8_t b1, uint8_t b2);
void usbMidiSendThreeByteMessage(uint8_t b1, uint8_t b2, uint8_t b3);
void usbMidiInit(void);
void usbMidiUpdate(void);