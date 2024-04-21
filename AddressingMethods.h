//
// Created by טל פלקסין on 20/03/2024.
//
#include "CommendAndInstructions.h"
#include "definitionOfRegAndOperation.h"
#ifndef M1_ADDRESSINGMETHODS_H
#define M1_ADDRESSINGMETHODS_H

#define MAX_NUM_INSTRUCTION 4

/*
   This function checks whether the instruction has valid name
   parameters:
                @param name - tha name of instruction to check
    return:
                @return TRUE if it valid instruction for example(data,string...),otherwise FALSE
 */
int instructionValidName(char *instruction);
int validateCommand(char *command, int *IC, FILE *validLabelFile, int countLine, long previousLocation,
                    FILE *inputFile, TagList *HeadTagList);
addressingMode getAddressingMode(char *operand, FILE *checksLabelFile, int flag,TagList *HeadTagList,char lineCopy[]);
#endif //M1_ADDRESSINGMETHODS_H
