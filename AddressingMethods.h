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
/*
   This function checks whether the given sentence is valid
   parameters:
                @param sentence - a pointer to the sentence
                @param instructionCounter - a pointer to IC counter
                @param fileValidLabels -  file that contains all the label names that appears
                @param num0fLine -  a pointer to the number current line
                @param HeadTagList - Tag list pointer
                @param originalLine - An array containing the current line for check without changing the line for example without cutting
    return:
                @return TRUE if the command sentence valid ,otherwise FALSE
 */
int validateCommand(char *command, int *IC, FILE *validLabelFile, int countLine, long previousLocation,
                    FILE *inputFile, TagList *HeadTagList);
/*
   This function checks the addressing method and return the type
   parameters:
                @param operand - the operand we check for it his address
                @param fileValidLabels -  file that contains all the label names that appears
                @param mark -  indicates that we have identified a label in the file, and must save the label name
                @param originalLine - An array containing the current line for check without changing the line for example without cutting
    return:
                @return the addressing type if it valid ,otherwise NON
 */
addressingMode getAddressingMode(char *operand, FILE *checksLabelFile, int flag,TagList *HeadTagList,char lineCopy[]);
#endif //M1_ADDRESSINGMETHODS_H
