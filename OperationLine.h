#ifndef OPERATIONLINE_H
#define OPERATIONLINE_H


#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 80
/* According to the number of bits that represent a number (12 or 14 bits)
 * the size of the possible number changes and therefore there is a different check */
#define MAX_NUM_14_BIT 16383
#define MIN_NUM_14_BIT -16383
#define MAX_NUM_12_BIT 4095
#define MIN_NUM_12_BIT -4095


/*
   This function remove all the white spaces at the start of a string
   parameters:
                @param currLine - the line to be deleted white spaces
    return:
                @return non
 */
void removeLeftWSpaces(char currLine[MAX_LINE_LENGTH]);

/*
   This function remove all the white spaces at the end of a string
   parameters:
                @param currLine - the line to be deleted white spaces
    return:
                @return non
 */
void removeRightWSpaces(char currLine[MAX_LINE_LENGTH]);

/*
   This function copy received line to array
   parameters:
                @param validLineArray - An array that keeps the line,which all the tests make on
                                    the line to check validation by dividing it into parts as required
                @param currLine - received line
    return:
                @return non
 */
int make_copy(char validLineArray[MAX_LINE_LENGTH], char *currLine);


/*
   This function cut out operand from received line and changing line to only the operand
   parameters:
                @param currLine - received line
    return:
                @return non
 */
void make_cut(char operand[MAX_LINE_LENGTH]);


/*
   This function outputs an error message if there is an error in the code
   parameters:
                @param error - an error message corresponding to the error appearing in the code
                @param num0fLine - the line that  error appearing in the code
    return:
                @return non
 */
void identifyError(char *error, int num0fLine);

/*
   This function outputs a warning message if there is a warning in the code
   parameters:
                @param warning - a warning message corresponding to the warning appearing in the code
                @param num0fLine - the line that  warning appearing in the code
    return:
                @return non
 */
void identifyWarning(char *warning, int num0fLine);

/*
   This function checks if the received word is a save word for example(register..)
   parameters:
                @param word - received word
    return:
                @return TRUE if it save word, otherwise FALSE
 */
int is_reserved_word(char *word);

/*
   This function checks if the number in the array are valid
   parameters:
                @param num - the array to be checked
                @param mark - save the index end of mcr

    return:
                @return TRUE if valid, otherwise FALSE
 */
int checkValidNumber(char num[MAX_LINE_LENGTH], int mark);

/*
   This function remove all white spaces and save the received string in array
   and after comma add space,
   parameters:
                @param validLineArray - An array that keeps the line,which all the tests make on
                                    the line to check validation by dividing it into parts as required
                @param currLine - received line

    return:
                @return TRUE if it is done properly and the line not null,
                        otherwise FALSE
 */
int adding_space(char *currLine, char validLineArray[MAX_LINE_LENGTH * 2]);

#endif

