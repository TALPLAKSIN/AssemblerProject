#include "OperationLine.h"
#include "AddressingMethods.h"
#include <string.h>

void removeLeftWSpaces(char currLine[MaxInputLength]) {
    int i = 0;/* Loop counter */
    int j = 0;/* Loop counter */
    if (currLine != NULL) {/* Check if the input line is not NULL */
        /*Increment the counters 'i' and 'j' by one and update the 'count' variable if there are any whitespace characters to the left of the string*/
        for (; i < strlen(currLine) &&
               (currLine[i] == ' ' || currLine[i] == '\t' || currLine[i] == EOF || currLine[i] == '\n' ||
                currLine[i] == '\r'); i++, j++);
        /*If there are any leading whitespace characters before the string, remove them and move the string to the left*/
        for (i = 0; j <= strlen(currLine); i++, j++)
            currLine[i] = currLine[j];
        currLine[j] = '\0';
    }
}

void removeRightWSpaces(char currLine[MaxInputLength]) {
    int i=0;/* Loop counter */
    if (currLine != NULL) {/* Check if the input line is not NULL */
        i = strlen(currLine) - 1;/* Start from the end of the string */
        /*if white characters appear after the string, replace them with '\0'."*/
        while (i >= 0 && (currLine[i] == ' ' || currLine[i] == '\t' || currLine[i] == EOF || currLine[i] == '\n' ||
                          currLine[i] == '\r')) {
            currLine[i] = '\0';
            i--;
        }
    }
}

int make_copy(char validLineArray[MaxInputLength], char *currLine) {
    int i=0;/* Loop counter */
    if (currLine != NULL && (MaxInputLength >= strlen(currLine) - 1)) {
        /* Copy characters from the current line to the validLineArray */
        for (i = 0; i < strlen(currLine); ++i)
            validLineArray[i] = currLine[i];
        /* Add '\0' at the end of the copied string */
        if (i < MaxInputLength)
            validLineArray[i + 1] = '\0';
        return TRUE;/* Copy successful */
    }
    return FALSE;/*If the string is null or exceeds the input limits*/
}

void make_cut(char operand[MaxInputLength]) {
    int i = 0, j = 0;/* Loop counter */
    int flag = TRUE;/*Indicates when the operand ends*/
    char cut[MaxInputLength] = {0};/*temp array*/
    for (; i < strlen(operand); i++)
        cut[i] = operand[i];/*copy the array*/
    while (j < strlen(operand) && operand[j] != '[') /*Finding the starting position of the '['*/
        j++;
    /*Copies to the temporary array the value itself followed by a line drop and \0 to the others cells*/
    for (i = j; (i < strlen(operand)&&flag) || (i - j-1 < strlen(operand)&&!flag) ; ++i) {
        if ( flag&&operand[i] != ']' )
            cut[i-j-1] = operand[i];
        else if(flag&&operand[i] != ']' ){
            flag = FALSE;
            cut[i - j-1] = '\n';
        }
        else
            cut[i - j-1] = '\0';
    }
    /*copy the temp array to the primary array*/
    for (i=0; i < strlen(operand); i++)
        operand[i]=cut[i];;
}

void identifyError(char *error, int num0fLine) {
    printf("Error occurred at line %d: %s\n", num0fLine, error);
}

void identifyWarning(char *warning, int num0fLine) {
    printf("Warning occurred at line %d: %s\n", num0fLine, warning);
}

int is_reserved_word(char *word) {
    /*Verify whether the received word corresponds to a register, instruction name, or command */
    return (check_reg_name(word) || instructionValidName(word) || check_op_name(word));
}

int checkValidNumber(char num[MaxInputLength], int mark) {
    char *temp = NULL;/* Temporary pointer for strtol */
    long numIn10Base = 0;/* Variable to store the converted number */
    char tempArray[MaxInputLength] = {0};
    /* Check if the input number is not NULL and not an empty string */
    if (num != NULL && num[0] != '\0') {
        /* Convert the string to a long integer in base 10 */
        numIn10Base = strtol(num, &temp, 10);
        make_copy(tempArray, temp);
        /*Deletes white characters from both ends of the string*/
        removeLeftWSpaces(tempArray);
        removeRightWSpaces(tempArray);
        if (tempArray[0] == '\0') {
            /* According to the number of bits that represent a number (12 or 14 bits)
             * the size of the possible number changes and therefore there is a different check */
            if ((mark && numIn10Base <= MAX_NUM_14_BIT && numIn10Base >= MIN_NUM_14_BIT) ||
                (!mark && numIn10Base <= MAX_NUM_12_BIT && numIn10Base >= MIN_NUM_12_BIT))
                return TRUE;/* Number is valid */
        }
        return FALSE;
    }
    return FALSE;
}


int adding_space(char *currLine, char validLineArray[MaxInputLength * 2]) {
    int i = 0;
    int j = 0;
    if (currLine != NULL) {/* Check if the input string is not NULL */
        for (i = 0; i < strlen(currLine); i++) {/* Iterate through each character in the input string */
            if (isspace(currLine[i]) == 0) {/* Check if the current character is not a whitespace character */
                validLineArray[j] = currLine[i];/* Copy the non-whitespace character to the modified string */
                if (currLine[i] == ',') {/* If the character is a comma, add a space after it in the modified string */
                    j++;
                    validLineArray[j] = ' ';/* Add a space after the comma */
                }
                j++;
            }
        }
        validLineArray[j] = '\0';
        return TRUE;
    }
    return FALSE;
}
