#include "OperationLine.h"
#include "AddressingMethods.h"
#include <string.h>

void removeLeftWSpaces(char currLine[MaxInputLength]) {
    int i = 0, j = 0;
    if (currLine != NULL) {
        /*raised i++ j++ count if white characters appear left from the string,*/
        for (; i < strlen(currLine) &&
               (currLine[i] == ' ' || currLine[i] == '\t' || currLine[i] == EOF || currLine[i] == '\n' ||
                currLine[i] == '\r'); i++, j++);
        /*if white characters appear left of the string, so delete them and advance the string to the left*/
        for (i = 0; j <= strlen(currLine); i++, j++)
            currLine[i] = currLine[j];
        currLine[j] = '\0';
    }
}

void removeRightWSpaces(char currLine[MaxInputLength]) {
    int i;
    if (currLine != NULL) {
        i = strlen(currLine) - 1;
        /*if white characters appear right from the string,so put their '\0'*/
        while (i >= 0 && (currLine[i] == ' ' || currLine[i] == '\t' || currLine[i] == EOF || currLine[i] == '\n' ||
                          currLine[i] == '\r')) {
            currLine[i] = '\0';
            i--;
        }
    }
}

int make_copy(char validLineArray[MaxInputLength], char *currLine) {
    int i;
    if (currLine != NULL && (MaxInputLength >= strlen(currLine) - 1)) {
        /*Copying the string into an array*/
        for (i = 0; i < strlen(currLine); ++i)
            validLineArray[i] = currLine[i];
        if (i < MaxInputLength)
            validLineArray[i + 1] = '\0';
        return TRUE;
    }
    return FALSE;/*If the string is null or exceeds the input limits*/
}

void identifyError(char *error, int num0fLine) {
    printf("Error occurred at line %d: %s\n", num0fLine, error);
}

void identifyWarning(char *warning, int num0fLine) {
    printf("Warning occurred at line %d: %s\n", num0fLine, warning);
}

int is_reserved_word(char *word) {
    /*check if received word is register/instructionName/command */
    return (check_reg_name(word) || instructionValidName(word) || check_op_name(word));
}

int checkValidNumber(char num[MaxInputLength], int mark) {
    char *temp = NULL;
    long numIn10Base = 0;
    if (num != NULL && num[0] != '\0') {
        numIn10Base = strtol(num, &temp, 10);
        if (!temp || temp[0] == '\0' || temp[0] == '\r' || temp[0] == '\t' || temp[0] == '\n') {
            /*A flag that marks the range of possible encoding values(12/14 bits) in the text*/
            if ((mark && numIn10Base <= MAX_NUM_14_BIT && numIn10Base >= MIN_NUM_14_BIT) ||
                (!mark && numIn10Base <= MAX_NUM_12_BIT && numIn10Base >= MIN_NUM_12_BIT))
                return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}


int adding_space(char *currLine, char validLineArray[MaxInputLength * 2]) {
    int i = 0;
    int j = 0;
    if (currLine != NULL) {
        for (i = 0; i < strlen(currLine); i++) {
            if (isspace(currLine[i]) == 0) {
                validLineArray[j] = currLine[i];
                if (currLine[i] == ',') {/* we add a space right after comma for using with strtok*/
                    j++;
                    validLineArray[j] = ' ';
                }
                j++;
            }
        }
        validLineArray[j] = '\0';
        return TRUE;
    }
    return FALSE;
}
