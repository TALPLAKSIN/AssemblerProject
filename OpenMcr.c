#include "OpenMcr.h"

void WriteMcr(FILE *initial_File, int endIndex, FILE *resultFile) {
    while (ftell(initial_File) != endIndex)
        fputc(fgetc(initial_File), resultFile);
}

FILE *openAndCheckFile(char *file_name) {
    FILE *inputFile = openTheFile(file_name, "as", "r");
    if (!inputFile) {
        printf("Error: unable to open file %s\n", file_name);
        return NULL;
    }
    if (feof(inputFile)) {
        printf("Error: The file is empty %s\n", file_name);
        fclose(inputFile);
        return NULL;
    }
    return inputFile;
}

int SearchAndAddMcr(char *file_name) {
    long prevLocation;
    char *current_word;
    FILE *inputFile;
    FILE *outputFile;
    McrList HeadMcrList = NULL;
    McrList mcrTemp = NULL;
    char lineValidation[MaxInputLength] = {0};
    char originalLine[MaxInputLength] = {0};
    if ((inputFile = openAndCheckFile(file_name)) == NULL)
        return 0;
    if ((outputFile = openTheFile(file_name, "am", "w")) == NULL) {
        fclose(inputFile);
        printf("\"Error: unable to open file %s.am\n", file_name);
        return 0;
    }
    printf("Staring the PreAssembler phase on the file: %s.as\n", file_name);
    while (!feof(inputFile)) { /*over all file, line by line*/
        readAndCopyRow(inputFile, lineValidation, originalLine);
        current_word = strtok(lineValidation, " \t\n\v\f\r"); /* get the first word in the line. */
        if (current_word != NULL && strcmp(current_word, "mcr") == 0) { /*mcr start detection*/
            current_word = strtok(NULL, " \t\n\v\f\r"); /* get the next word in the line. */
            if (HandelMcrName(current_word)) {
                mcrTemp = NewMcr(current_word, ftell(inputFile));/*Save mcr start position*/
                while (!current_word || strcmp(current_word, "endmcr") != 0) {
                    setEnd(mcrTemp, ftell(inputFile));/*Save mcr end position*/
                    fgets(lineValidation, MaxInputLength, inputFile);
                    current_word = strtok(lineValidation, " \t\n\v\f\r");
                }/*We will go through the text until we find an ending word for the mcr (given that it always exists)*/
                InsertMcrToList(&HeadMcrList, mcrTemp);/*Insert a mcr into the list of mcr*/
            } else {
                printf("Error:invalid macr name: '%s'\n Sorry PreAssembler on file: %s.as did not succeed!\n",
                       current_word,
                       file_name);
                return 0;
            }
        } else {
            mcrTemp = (SearchMcr(HeadMcrList, current_word));/*Checking for potential mcr words*/
            if (mcrTemp != NULL) { /* if it's a mcr */
                prevLocation = ftell(inputFile);
                fseek(inputFile, getStart(mcrTemp), SEEK_SET);
                /* we write the mcr's code instead of the mcr call */
                WriteMcr(inputFile, getEnd(mcrTemp), outputFile);
                fseek(inputFile, prevLocation, SEEK_SET);
            } else {
                fprintf(outputFile, "%s", originalLine);/*Copy the row without change*/
            }
        }
    }
    fclose(inputFile);
    fclose(outputFile);
    freelistM(HeadMcrList);
    printf("Complete the PreAssembler phase on file: %s.as\n", file_name);
    return 1;
}


