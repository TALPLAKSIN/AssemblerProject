#include "AddressingMethods.h"
int instructionValidName(char *instruction){
    int i;
    for (i = 0; i < MAX_NUM_INSTRUCTION; i++) {
        if (strcmp(instruction, instructionNames[i].name) == 0)
            return TRUE;

    }

}
