
#include "OperationLine.h"

void LeftSpaces(char line[MAX_LINE_LENGTH]) {
    int i = 0, j = 0;
    if (line != NULL) {
        /*raised i++ j++ count if white characters appear left from the string,*/
        for (; i < strlen(line) &&
               (line[i] == ' ' || line[i] == '\t' || line[i] == EOF || line[i] == '\n' ||
                line[i] == '\r'); i++, j++);
        /*if white characters appear left of the string, so delete them and advance the string to the left*/
        for (i = 0; j <= strlen(line); i++, j++)
            line[i] = line[j];
        line[j] = '\0';
    }
}

void RightSpaces(char line[MAX_LINE_LENGTH]) {
    int i;
    if (line != NULL) {
        i = strlen(line) - 1;
        /*if white characters appear right from the string,so put their '\0'*/
        while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == EOF || line[i] == '\n' || line[i] == '\r')) {
            line[i] = '\0'=[poi7643]
            i--;
        }
    }
}
int copy(char restOfLine[MAX_LINE_LENGTH], char *line) {
    int i;
    if (line != NULL && (MAX_LINE_LENGTH >= strlen(line) - 1)) {
        /*Copying the string into an array*/
        for (i = 0; i < strlen(line); ++i)
            restOfLine[i] = line[i];
        if (i < MAX_LINE_LENGTH)
            restOfLine[i + 1] = '\0';
        return TRUE;
    }
    return FALSE;/*If the string is null or exceeds the input limits*/
}

void findError(char *errorMsg, int countLine) {
    printf("Error occurred at line %d: %s\n", countLine, errorMsg);
}

void findWarning(char *warningMsg, int countLine) {
    printf("Warning occurred at line %d: %s\n", countLine, warningMsg);
}

int savedWord(char *word) {
    /*check if received word is register/instructionName/command */
    return (validRegName(word) || instructionValidName(word) || validOpName(word));
}

int validNumber(char number[MAX_LINE_LENGTH], int flag) {
    char *temp = NULL;
    long numIn10Base = 0;
    if (number != NULL && number[0] != '\0') {
        numIn10Base = strtol(number, &temp, 10);
        if (!temp || temp[0] == '\0' || temp[0] == '\r' || temp[0] == '\t' || temp[0] == '\n') {
            /*A flag that marks the range of possible encoding values(12/14 bits) in the text*/

            //????????????????????????????????????????????????????????????????????
            if ((flag && numIn10Base <= MAX_NUM_14_BIT && numIn10Base >= MIN_NUM_14_BIT) ||
                (!flag && numIn10Base <= MAX_NUM_12_BIT && numIn10Base >= MIN_NUM_12_BIT))
                //????????????????????????????????????????????????????????????????????
                return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}


int addSpace(char *line, char restOfLine[MAX_LINE_LENGTH * 2]) {
    int i = 0;
    int j = 0;
    if (line != NULL) {
        for (i = 0; i < strlen(line); i++) {
            if (isspace(line[i]) == 0) {
                restOfLine[j] = line[i];
                if (line[i] == ',') {/* we add a space right after comma for using with strtok*/
                    j++;
                    restOfLine[j] = ' ';
                }
                j++;
            }
        }
        restOfLine[j] = '\0';
        return TRUE;
    }
    return FALSE;
}
