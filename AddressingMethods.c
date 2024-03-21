#include "AddressingMethods.h"
int instructionValidName(char *instruction){
    int i;
    for (i = 0; i < MAX_NUM_INSTRUCTION; i++) {
        if (strcmp(instruction, instructionNames[i].name) == 0)
            return TRUE;
    }
    return FALSE;
}
int validateCommand(char *command, int *IC, FILE *validLabelFile, int countLine, long previousLocation,
                    FILE *inputFile, TagList *HeadTagList) {
    int opNumber;
    int flag;
    char restOfLine[MAX_LINE_LENGTH] = {0};
    opNumber = get_num_of_operation(command);
}