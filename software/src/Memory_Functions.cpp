#include "Memory_Functions.h"



boolean checkMemory()
{
    byte chk;
    #ifndef USE_DUE
        for (int m = 0; m < 4; m++) {
            chk = EEPROM.read(MEM_CHECK + m);
            if (chk != defaultMemoryMap[MEM_CHECK + m]) {
                return false;
            }
        }
    #endif
    return true;
}



void changeTasks()
{
    midioutByteDelay = memory[MEM_MIDIOUT_BYTE_DELAY] * memory[MEM_MIDIOUT_BYTE_DELAY + 1];
    midioutBitDelay = memory[MEM_MIDIOUT_BIT_DELAY] * memory[MEM_MIDIOUT_BIT_DELAY + 1];
}



void loadMemory()
{
    #ifndef USE_DUE
        for (int m = MEM_MAX; m >= 0; m--) {
            memory[m] = EEPROM.read(m);
        }
    #endif
    changeTasks();
}



void initMemory(boolean reinit)
{
    if (!alwaysUseDefaultSettings) {
        #ifndef USE_DUE
            if (reinit || !checkMemory()) {
                for (int m = MEM_MAX; m >= 0; m--) {
                    EEPROM.write(m, defaultMemoryMap[m]);
                }
            }
        #endif
        loadMemory();
    } else {
        for (int m = 0; m < MEM_MAX; m++) {    // changed <= to <  -b_s
            memory[m] = defaultMemoryMap[m];
        }
    }
    changeTasks();
}



void printMemory()
{
    for (int m = 0; m < MEM_MAX; m++) {    // changed <= to <  -b_s
        serial->println(memory[m], HEX);
    }
}



void saveMemory()
{
    #ifndef USE_DUE
        for (int m = (MEM_MAX - 1); m >= 0; m--) {
            EEPROM.write(m, memory[m]);
        }
        changeTasks();
    #endif
}
