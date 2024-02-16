#include "OpenMcr.h"
#include "McrList.h"
#include  "FileMethod.h"
#define MAX_LINE_LENGTH 80
void WriteMcr(FILE *inputFile, int end, FILE *outFile) {
    while (ftell(inputFile) != end)
        fputc(fgetc(inputFile), outFile);
}

FILE *openAndCheckFile(char *fileName) {
    FILE *inputFile = open_file(fileName, "test.as", "r");
    if (!inputFile) {
        printf("Error: unable to open file %s\n", fileName);
        return NULL;
    }
    if (feof(inputFile)) {
        printf("Error: The file is empty %s\n", fileName);
        fclose(inputFile);
        return NULL;
    }
    return inputFile;
}

int SearchAndAddMcr(char *fileName) {
    long prevLocation;
    char *curWord;
    FILE *inputFile, *outputFile;
    McrList HeadMcrList = NULL, mcrTemp = NULL;
    char lineCheck[MAX_LINE_LENGTH] = {0}, lineCopy[MAX_LINE_LENGTH] = {0};
    if ((inputFile = openAndCheckFile(fileName)) == NULL)
        return 0;
    if ((outputFile = open_file(fileName, "am", "w")) == NULL) {
        fclose(inputFile);
        printf("\"Error: unable to open file %s.am\n", fileName);
        return 0;
    }
    printf("Execution of PreAssembler on the file: %s.as\n", fileName);
    while (!feof(inputFile)) { /*over all file, line by line*/
        readAndCopyRow(inputFile,lineCheck,lineCopy);
        curWord = strtok(lineCheck, " \t\n\v\f\r"); /* get the first word in the line. */
        if (curWord != NULL && strcmp(curWord, "mcr") == 0) { /*mcr start detection*/
            curWord = strtok(NULL, " \t\n\v\f\r"); /* get the next word in the line. */
            if (HandelMcrName(curWord)) {
                mcrTemp = NewMcr(curWord, ftell(inputFile));/*Save macro start position*/
                while (!curWord || strcmp(curWord, "endmcr") != 0) {
                    setEnd(mcrTemp, ftell(inputFile));/*Save macro end position*/
                    fgets(lineCheck, MAX_LINE_LENGTH, inputFile);
                    curWord = strtok(lineCheck, " \t\n\v\f\r");
                }/*We will go through the text until we find an ending word for the macro (given that it always exists)*/
                InsertMcrToList(&HeadMcrList, mcrTemp);/*Insert a macro into the list of macros*/
            } else {
                printf("Error:invalid macro name: '%s'\n Sorry PreAssembler on file: %s.as did not succeed!\n", curWord,
                       fileName);
                return 0;
            }
        } else {
            mcrTemp = (SearchMcr(HeadMcrList, curWord));/*Checking for potential macro words*/
            if (mcrTemp != NULL) { /* if it's a mcr */
                prevLocation = ftell(inputFile);
                fseek(inputFile, getStart(mcrTemp), SEEK_SET);
                /* we write the macro's code instead of the macro call */
                WriteMcr(inputFile, getEnd(mcrTemp), outputFile);
                fseek(inputFile, prevLocation, SEEK_SET);
            } else {
                fprintf(outputFile, "%s", lineCopy);/*Copy the row without change*/
            }
        }
    }
    fclose(inputFile);
    fclose(outputFile);
    freelist(HeadMcrList);
    printf("we have successfully completed the process PreAssembler on file: %s.as\n", fileName);
    return 1;
}

