
#ifndef OPENMCR_H
#define OPENMCR_H

#include "McrList.h"
#include "FileMethod.h"

#define MAX_LINE_LENGTH 80

/*
   This function writing the mcr retirement in the file
   parameters:
                @param initial_File - the received file
                @param endIndex - save the index end of mcr
                @param resultFile -  file that contains retirement mcr
    return:
                @return non
 */
void WriteMcr(FILE *input_file, int end, FILE *resultFile);

/*
   This function open the received file and checks his validation
   parameters:
                @param file_name - a pointer to the received file
    return:
                @return non
 */
FILE *openAndCheckFile(char *file_name);

/*
   This function checks validation of the mcr save the start and end index of mcr and
   goes through the program and retirement all the mcr present in it and this function
   completed the PreAssembler process.
   parameters:
                @param file_name - a pointer to the received file
    return:
                @return TRUE if it valid ,otherwise FALSE
 */
int SearchAndAddMcr(char *file_name);

#endif


