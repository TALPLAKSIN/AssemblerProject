#ifndef HANDELLABLE_H
#define HANDELLABLE_H

#define MAX_LABEL_LENGTH 32

#include "TagList.h"
#include "OperationLine.h"
#include "FileMethod.h"

/*
   This function checks if the tag name is valid
   parameters:
                @param word - a pointer to name to check
    return:
                @return TRUE if the name is valid ,otherwise FALSE
 */
int HandelTagName(char *word);

/*
   This function checks label validation and if it is valid add it to tag list
   parameters:
                @param HeadTagList - Tag list pointer
                @param name_of_label - the label name
                @param instructionCounter - a pointer to IC counter
                @param num0fLine -  a pointer to the number current line
                @param TagTemp- create new Tag list pointer
    return:
                @return TRUE if the instruction is valid ,otherwise FALSE
 */
int HandelLabel(TagList *HeadTagList, char *name_of_label, int instructionCounter, int num0fLine, TagList *TagTemp);

/*
   This function checks if the labels that appears in the received file is defined in Tag list
   parameters:
                @param HeadTagList - Tag list pointer
                @param fileValidLabels - the file that contains all the labels appears in received file
    return:
                @return TRUE if the labels defined ,otherwise FALSE
 */
int handel_label_not_found(FILE *fileValidLabels, TagList *HeadTagList);

/*
   This function checks if .entry labels that appears in the received file is defined in Tag list
   parameters:
                @param HeadTagList - Tag list pointer
                @param ValidEntryFile - file that contains all the entry label names that appears
                @param ValidEntryFile - file that contains all the entry label names that appears
    return:
                @return TRUE if the .entry labels defined ,otherwise FALSE
 */
int handel_label_entry(FILE *ValidEntryFile, TagList *HeadTagList);

#endif


