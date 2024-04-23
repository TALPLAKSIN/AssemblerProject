#ifndef ENCODEANDWRITETOFILE_H
#define ENCODEANDWRITETOFILE_H

#include "convertAddress.h"

/*
   This function checks all the labels and for each label entry writes it to the file

    parameters:
                @param file_name - the name of the file
                @param HeadTagList - Tag list pointer
                @param entry_file - a pointer to entry file
                @param flagsArray - array represent a flag (5 cell - ICcounter, DCcounter, EX, EN, ERROR)
    return:
                @return non
*/
void dealWithEntry(char *file_name, TagList *HeadTagList, FILE *entry_file, int *flagsArray);

/*
    This function is the main function of the second phase and the last phase in the assembler.
    which dealing with encoding all the lines appearing in the received file.

    parameters:
                @param file_name - the name of the file
                @param HeadTagList - Tag list pointer
                @param flagsArray - array represent a flag (5 cell - ICcounter, DCcounter, EX, EN, ERROR)


    return:
                @return final object file
*/
int convertFileToBase4(char *file_name, TagList *HeadTagList, int *flagsArray);

#endif





