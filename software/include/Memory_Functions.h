#pragma once

#include "Arduinoboy.h"

#ifndef USE_DUE
    #include <EEPROM.h>
#endif


void changeTasks(void);
void loadMemory(void);
void initMemory(boolean reinit);
void saveMemory(void);
