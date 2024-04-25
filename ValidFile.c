#include "ValidFile.h"

TagList HandelAndAddTag(char *file_name,int *flagsArray) {
    FILE *inputFile=NULL;/*Input file pointer*/
    FILE *outputFile=NULL;/*Output file pointer*/
    FILE *fileValidLabels=NULL;/*File for all labels that appear in te code */
    FILE *ValidEntryFile=NULL;/*File for all entry labels that appear in te code */
    TagList HeadTagList = NULL;/*Head of the tag list*/
    TagList TagTemp = NULL;/*Temporary tag pointer*/
    char lineValidation[MaxInputLength] = {0};
    char originalLine[MaxInputLength] = {0};
    char *current_word = NULL; /*  Current word pointer */
    int num0fLine = 0;/*Line number counter */
    int instructionCounter = 100; /*instruction counter*/
    int dataCounter = 0;/*data counter*/
    long prevLocation=0;/*Previous location in file*/
    char c3='\0';
    /*Open necessary files*/
    inputFile = openTheFile(file_name, "am", "r");
    outputFile = openTheFile("tempFile", "am", "w+");
    fileValidLabels = openTheFile("LabelFile", "am","w+");
    ValidEntryFile = openTheFile("EntryFile", "am","w+");
    /*Check if input file opened successfully*/
    if (!inputFile) {
        identifyError("Failed to open the input file.", num0fLine);
        flagsArray[ERROR] = OCCUR;
        return NULL;
    }
    printf("Beginning primary iteration on the file: %s...\n", file_name);
    while (!feof(inputFile)) { /*Iterating through the input file*/
        TagTemp = NULL;
        prevLocation = ftell(inputFile);
        readAndCopyRow(inputFile, lineValidation, originalLine);
        num0fLine++;
        /* a pointer to the current word */
        current_word = strtok(lineValidation, " \t\n\v\f\r");
        /*Skip empty lines or comments */
        if (!current_word || current_word[0] == ';')
            continue;/*continue to the next line*/
        if (current_word[strlen(current_word) - 1] == ':') {/* Check for label declaration */
            /* Handle label*/
            if (!HandelLabel(&HeadTagList, current_word, instructionCounter, num0fLine,
                             &TagTemp)) {
                flagsArray[ERROR] = OCCUR;/* In case of an error*/
                continue;
            } else {
                current_word = strtok(NULL, " \t\n\v\f\r");
                if (!current_word) {
                    identifyError("A label declaration without any content", num0fLine);
                    flagsArray[ERROR] = OCCUR;
                    continue;
                }
                else if (!strcmp(".define", current_word)) {
                    identifyError("You must not define a label on a line that is a DEFAIN definition statement", num0fLine);
                    flagsArray[ERROR] = OCCUR;
                    continue;
                }
            }
        }
        if (current_word[0] == '.') { /*Verifying if it is an instruction */
            /* Handle instruction*/
            if (!instructionsFormat(&HeadTagList, current_word, &dataCounter, ValidEntryFile, num0fLine, &TagTemp,
                                    flagsArray, prevLocation, inputFile, originalLine)) {
                flagsArray[ERROR] = OCCUR;/* In case of an error*/
            }
            fprintf(outputFile, "%s", originalLine);/*Copy the original line*/
            continue;
        }
        if (check_op_name(current_word)) {/*Verifying if it is a command */
            if (!validateCommand(current_word, &instructionCounter, fileValidLabels, num0fLine, &HeadTagList,
                                 originalLine)) {
                flagsArray[ERROR] = OCCUR;/* In case of an error*/
                continue;
            }
        } else {
            printf("Error occurred at line %d: Invalid command: '%s'\n", num0fLine, current_word);
            flagsArray[ERROR] = OCCUR;/* if a occurred an error */
        }
        fprintf(outputFile, "%s", originalLine);/*Copy the original line*/
    }
    deleteFile(file_name, "am");
    inputFile = openTheFile(file_name, "am", "w");
    fseek(outputFile, 0, SEEK_SET);
    while (!feof(outputFile)) {
        c3=(char)fgetc(outputFile);
        if(c3!=EOF)
            fputc(c3, inputFile);
    }
    deleteFile("tempFile", "am");
    changeICTags(&HeadTagList,instructionCounter); /* Update instruction counter tags */
    if (!handel_label_entry(ValidEntryFile, &HeadTagList))
        flagsArray[ERROR] = OCCUR;/* In the file, there is an 'entry' label that does not valid.*/
    if (!handel_label_not_found(fileValidLabels, &HeadTagList))
        flagsArray[ERROR] = OCCUR;/*There is a label present in the file that has not been defined*/
    /* Update final instructionCounter and dataCounter for phase 2*/
    flagsArray[ICcounter] = instructionCounter;
    flagsArray[DCcounter] = dataCounter;
    closeTheFiles(inputFile, fileValidLabels, ValidEntryFile);/* free all files*/
    if (HeadTagList != NULL)
        allUsed(HeadTagList, 1);/*unused tags*/
    if (flagsArray[ERROR] == OCCUR) {/*  In case of an error - stop the process and free/delete all memory*/
        printf("phase one on the received file: %s.am has failed\n", file_name);
        deleteFile(file_name, "am");
        freelist(HeadTagList);/* free the tag list */
        return NULL;
    }
    /* Print success message */
    printf("Complete primary iteration on file: %s.am!\n", file_name);
    return HeadTagList;
}


