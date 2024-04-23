#ifndef COMMENDANDINSTRUCTIONS_H
#define COMMENDANDINSTRUCTIONS_H

#include "HandelLable.h"


static const struct instructionNames {
    const char *name;
/*instruction names*/
} instructionNames[] = {
        {".define"},
        {".entry"},
        {".extern"},
        {".string"},
        {".data"},
};

enum flagsNames {
    ICcounter, DCcounter, EX, EN, ERROR
};

/*
   This function checks whether the current word is one of instruction names
   for example (define,entry,data..) and call to handel with chosen instruction
   parameters:
                @param HeadTagList - Tag list pointer
                @param current_word - a pointer of current word to check instruction
                @param dataCounter - a pointer to DC counter
                @param ValidEntryFile -  file that contains all the entry label names that appears
                @param num0fLine -   a pointer to the number current line
                @param TagTemp- new Tag list pointer
                @param flagsArray - array represent a flag (5 cell - ICcounter, DCcounter, EX, EN, ERROR )
                @param prevLocation - hold the prev location
                @param input_file- a pointer to the received file
                @param originalLine - An array containing the current line for check without changing the line for example without cutting
    return:
                @return instruction method if it valid ,otherwise FALSE
 */

int
instructionsFormat(TagList *HeadTagList, char *current_word, int *dataCounter, FILE *ValidEntryFile, int num0fLine,
                   TagList *TagTemp,
                   int *flagsArray, long prevLocation, FILE *input_file, char originalLine[]);

/*
   This function checks .entry instruction validation
   parameters:
                @param HeadTagList - Tag list pointer
                @param tag - the line
                @param dataCounter - a pointer to DC counter
                @param ValidEntryFile -  file that contains all the entry label names that appears
                @param num0fLine -  a pointer to the number current line
                @param TagTemp- new Tag list pointer of the instruction
    return:
                @return TRUE if the instruction is valid ,otherwise FALSE
 */
int checkEntryFormat(TagList *HeadTagList, char *tag, int *dataCounter, FILE *ValidEntryFile, int num0fLine,
                     TagList *TagTemp);

/*
   This function checks .extern instruction validation
   parameters:
                @param HeadTagList - Tag list pointer
                @param tag - the line
                @param dataCounter - a pointer to DC counter
                @param num0fLine -  a pointer to the number current line
                @param TagTemp- new Tag list pointer of the instruction
    return:
                @return TRUE if the instruction is valid ,otherwise FALSE
 */
int checkExternFormat(TagList *HeadTagList, char *tag, int *dataCounter, int num0fLine, TagList *TagTemp);

/*
   This function checks .string instruction validation
   parameters:
                @param HeadTagList - Tag list pointer
                @param curLine - the line
                @param dataCounter - a pointer to DC counter
                @param num0fLine -  a pointer to the number current line
                @param TagTemp- new Tag list pointer of the instruction
    return:
                @return TRUE if the instruction is valid ,otherwise FALSE
 */

int checkStringFormat(TagList *HeadTagList, char *curLine, int *dataCounter, int num0fLine, TagList *TagTemp);

/*
   This function checks .data instruction validation
   parameters:
                @param HeadTagList - Tag list pointer
                @param curLine - the line
                @param dataCounter - a pointer to DC counter
                @param num0fLine -  a pointer to the line
                @param TagTemp- new Tag list pointer
                @param prevLocation - hold the prev location
                @param inputFile- a pointer to the received file
                @param originalLine - An array containing the current line for check without changing the line for example without cutting
    return:
                @return instruction method if it valid ,otherwise FALSE
 */
int checkDataFormat(TagList *HeadTagList, char *curLine, int *dataCounter, int num0fLine, TagList *TagTemp,
                    long prevLocation,
                    FILE *inputFile, char originalLine[]);

/*
   This function checks .define instruction validation
   parameters:
                @param HeadTagList - Tag list pointer
                @param curLine - the line
                @param dataCounter - a pointer to DC counter
                @param num0fLine -  a pointer to the number current line
                @param TagTemp- new Tag list pointer of the instruction
    return:
                @return TRUE if the instruction is valid ,otherwise FALSE
 */
int checkDefineFormat(TagList *HeadTagList, char *curLine, int *dataCounter, int num0fLine, TagList *TagTemp);

/*
   This function checks if a Mcr definition exists in the tag list, retrieves its value,
   converts it to a string, and replaces the Mcr definition in the provided
    parameters:
                @param HeadTagList - Tag list pointer
                @param defineName - define name
                @param originalLine - An array containing the current line for check without changing the line for example without cutting
    return:
                @return TRUE if definition was successfully replaced ,otherwise FALSE

 */
int checkAndReplaceDefine(TagList *HeadTagList, char *defineName, char originalLine[]);

#endif


