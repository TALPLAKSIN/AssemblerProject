#include "OpenMcr.h"

void WriteMcr(FILE *initial_File, int endIndex, FILE *resultFile) {
    while (ftell(initial_File) != endIndex) /* Copy characters from initial_File to resultFile until reaching endIndex */
        fputc(fgetc(initial_File), resultFile);; /* Write a character from initial_File to resultFile */
}

FILE *openAndCheckFile(char *file_name) {
    /* Open the file with "as" extension for reading */
    FILE *inputFile = openTheFile(file_name, "as", "r");
    if (!inputFile) {  /* Check if inputFile is NULL (failed to open) */
        printf("Error: unable to open file %s\n", file_name);/* Print error message */
        return NULL;/* Return NULL to indicate failure */
    }
    if (feof(inputFile)) {/* Check if inputFile is empty (reached end of file immediately) */
        printf("Error: The file is empty %s\n", file_name);/* Print error message */
        fclose(inputFile);/* Close the file */
        return NULL;
    }
    return inputFile;/* Return the opened file pointer */
}

int SearchAndAddMcr(char *file_name) {
    long prevLocation=0; /* Store the previous position */
    char *current_word=NULL;/* Store the current token word*/
    FILE *inputFile=NULL; /* Input file pointer */
    FILE *outputFile=NULL;/* Output file pointer */
    McrList HeadMcrList = NULL;/* Head pointer for the list of mcr */
    McrList mcrTemp = NULL;/* Temporary pointer for mcr */
    char lineValidation[MaxInputLength] = {0};
    char originalLine[MaxInputLength] = {0};
    if ((inputFile = openAndCheckFile(file_name)) == NULL) /* Open and check the input file */
        return FALSE;
    /* Open the output file */
    if ((outputFile = openTheFile(file_name, "am", "w")) == NULL) {
        fclose(inputFile);
        printf("\"Error: unable to open file %s.am\n", file_name);
        return FALSE;
    }
    printf("Staring the PreAssembler phase on the file: %s.as\n", file_name);
    while (!feof(inputFile)) { /* Loop through each line in the input file */
        readAndCopyRow(inputFile, lineValidation, originalLine);
        current_word = strtok(lineValidation, " \t\n\v\f\r"); /* Get the first word*/
        if (current_word != NULL && strcmp(current_word, "mcr") == 0) {  /* Check if the current word is "mcr" */
            current_word = strtok(NULL, " \t\n\v\f\r");  /* Get the next word */
            if (HandelMcrName(current_word)) {/* Check if the mcr name is valid */
                mcrTemp = NewMcr(current_word, ftell(inputFile));/*Save mcr start index*/
                /* Loop until "endmcr" is found */
                while (!current_word || strcmp(current_word, "endmcr") != 0) {
                    setEnd(mcrTemp, ftell(inputFile));/*Save mcr end index*/
                    fgets(lineValidation, MaxInputLength, inputFile);
                    current_word = strtok(lineValidation, " \t\n\v\f\r");
                }/*We will continue scanning through the code until we find finale word*/
                InsertMcrToList(&HeadMcrList, mcrTemp);/*"Add a mcr to the mcr list*/
            } else {/*Error:invalid mcr name: '%s' Sorry PreAssembler on file: %s.as did not succeed!*/
                printf("Error:The mcr name '%s' is invalid\n Apologies,the PreAssembler process for file : %s.as failed\n",
                       current_word,
                       file_name);
                return FALSE;
            }
        } else {
            mcrTemp = (SearchMcr(HeadMcrList, current_word));/* search for the mcr in the list */
            if (mcrTemp != NULL) { /* if it's a mcr */
                prevLocation = ftell(inputFile);/* Save the current file position */
                fseek(inputFile, getStart(mcrTemp), SEEK_SET);/* Move to the start of the mcr */
                WriteMcr(inputFile, getEnd(mcrTemp), outputFile);/* Write the mcr content to the file */
                fseek(inputFile, prevLocation, SEEK_SET);/* Move back to the original position */

            } else {
                fprintf(outputFile, "%s", originalLine); /* Write the original line to the file */
            }
        }
    }
    fclose(inputFile);/* Close the input file */
    fclose(outputFile);/* Close the output file */
    freelistM(HeadMcrList);/* Free the memory allocated for the mcr list */
    printf("Complete the PreAssembler phase on file: %s.as\n", file_name);
    return TRUE;
}


