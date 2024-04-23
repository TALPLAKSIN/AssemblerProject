#ifndef CONVERTADDRESS_H
#define CONVERTADDRESS_H

#include "convertInstructions.h"

/*
     This method corresponding function and handel the address

    parameters:
                @param operand_mode - the mode of relevant addressing mode
                @param HeadTagList - Tag list pointer
                @param parameter - the parameter that should be encoded
                @param instructionCounter - a pointer to the IC counter
                @param instructions_file -  a pointer to the instructions file
                @param extern_file -  a pointer to extern file
                @param num1_Or_num2 - Indicates whether it is a destination or a source

    return:
                @return non
*/
void dealWithAddress(addressingMode operand_mode, TagList *HeadTagList, char *parameter, int *instructionCounter,
                     FILE *instructions_file, FILE *extern_file, int num1_Or_num2);

/*
    This function based on the number of operands (which it receives) calls the appropriate method to convert to base 4

    parameters:
                @param HeadTagList - Tag list pointer
                @param sentence - the sentence that be converted.
                @param instructionCounter - a pointer to the IC counter
                @param instructions_file -  a pointer to the instructions file
                @param extern_file -  a pointer to extern file

    return:
                @return non
*/
void convertSentenceToBase4(TagList *HeadTagList, char *sentence, int *instructionCounter, FILE *instructions_file,
                            FILE *extern_file);

/*
   This function is intended for methods with one operand and converts them to base 4

    parameters:
                @param HeadTagList - Tag list pointer
                @param sentence - the sentence that be converted.
                @param instructionCounter - a pointer to the IC counter
                @param instructions_file -  a pointer to the instructions file
                @param extern_file - a pointer to extern file
    return:
                @return non
*/
void convertOneOperand(TagList *HeadTagList, char *sentence, int *instructionCounter, FILE *instructions_file,
                       FILE *extern_file);

/*
  This method is intended for methods with two operand and converts them to base 4

    parameters:
                @param HeadTagList - Tag list pointer
                @param sentence - the sentence that be converted.
                @param instructionCounter - a pointer to the IC counter
                @param instructions_file -  a pointer to the instructions file
                @param extern_file - a pointer to extern file
    return:
                @return non
*/
void convertTwoOperand(TagList *HeadTagList, char *sentence, int *instructionCounter, FILE *instructions_file,
                       FILE *extern_file);

/*
     This function converts an immediate type address method to base 4

    parameters:
                @param parameter - the parameter to encode
                @param instructionCounter - a pointer to the IC counter
                @param instructions_file -  a pointer to the instructions file
    return:
                @return non
*/
void convertImmediateToBase4(char *parameter, int *instructionCounter, FILE *instructions_file);

/*
     This function converts a const Index type address method to base 4

    parameters:
                @param HeadTagList - Tag list pointer
                @param parameter - the parameter to encode
                @param instructionCounter - a pointer to the IC counter
                @param instructions_file -  a pointer to the instructions file
                @param extern_file - a pointer to extern file
    return:
                @return non
*/
void convertConstIndexToBase4(char *parameter, int *instructionCounter, FILE *instructions_file, TagList *HeadTagList,
                              FILE *extern_file);

/*
   This function converts a direct type address method to base 4

    parameters:
                @param HeadTagList - Tag list pointer
                @param parameter - the parameter to encode
                @param instructionCounter - a pointer to the IC counter
                @param instructions_file -  a pointer to the instructions file
                @param extern_file - a pointer to extern file
    return:
                @return non
*/

void convertDirectToBase4(TagList *HeadTagList, char *parameter, int *instructionCounter, FILE *instructions_file,
                          FILE *extern_file);

#endif





