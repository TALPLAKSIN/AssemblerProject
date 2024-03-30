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
    (*IC)++;/* increase IC counter */
    if (opNumber == 0) {/* if the command doesn't require any operands */
        if (!copy(restOfLine, strtok(NULL, " \t\n\v\f\r")))
            return TRUE;
        findError("for this command no Operand allowed or any characters", countLine);
        return FALSE;
    }
    flag = copy(restOfLine, strtok(NULL, ""));
    if (flag && restOfLine[0] != ',') {
        removeLeftWSpaces(restOfLine);
        removeRightWSpaces(restOfLine);
        if (opNumber == 1)
            return validDestOneOp(command, IC, validLabelFile, countLine, restOfLine, previousLocation, inputFile,
                                  HeadTagList);
        else
            return validDestSourceTwoOp(command, IC, validLabelFile, countLine, restOfLine, previousLocation, inputFile,
                                        HeadTagList);
    }
    if (!flag) /* if its empty - Missing operand*/
        findError("Missing operand", countLine);
    else  /* if it starts with a comma, it we have illegal comma */
        findError("illegal commas found right after the command name", countLine);
    return FALSE;
}
