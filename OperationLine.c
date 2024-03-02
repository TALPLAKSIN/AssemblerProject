
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
