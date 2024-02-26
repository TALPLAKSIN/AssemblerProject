
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
            line[i] = '\0';
            i--;
        }
    }
}
