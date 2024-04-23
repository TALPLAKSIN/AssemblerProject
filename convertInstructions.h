#ifndef CONVERTINSTRUCTIONS_H
#define CONVERTINSTRUCTIONS_H

#include "writeInBaseFour.h"

/*
    This function differentiates between a data prompt and a string prompt and makes a call to a method that will be coded accordingly

    parameters:
                @param HeadTagList - Tag list pointer
                @param action - the instruction that be converted.
                @param dataCounter - a pointer to DC counter
                @param data_file -  a pointer to data file
    return:
                @return non
*/
void dealWithInstructions(TagList *HeadTagList, char *action, int *dataCounter, FILE *data_file);

/*
    This function convert data instructions to base 4

    parameters:
                @param currLine - the line that be convert
                @param dataCounter - a pointer to DC counter
                @param data_file -  a pointer to data file
    return:
                @return non

*/
void convertDataToBaseFour(char *currLine, int *dataCounter, FILE *data_file);

/*
    This function convert string instructions to base 4

    parameters:
                @param currLine - the line that be converted.
                @param instructionCounter - a pointer to the IC counter
                @param data_file -  a pointer to data file
    return:
                @return non

*/
void convertStringToBaseFour(char *currLine, int *DC, FILE *data_file);


#endif





