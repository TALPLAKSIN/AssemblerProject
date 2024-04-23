#include "ValidFile.h"

TagList HandelAndAddTag(char *file_name,int *flagsArray) {/* each cell of the flagsArray array represent a flag (5 cell - ICcounter, DCcounter, EX, EN, ERROR ) */
    FILE *inputFile;/*received file*/
    FILE *outputFile;
    FILE *fileValidLabels;/*check file for the labels that appears in received */
    FILE *ValidEntryFile;/*check file for the  entry labels that appears in received */
    TagList HeadTagList = NULL;
    TagList TagTemp = NULL;
    char lineValidation[MaxInputLength] = {0};
    char originalLine[MaxInputLength] = {0};
    char *current_word = NULL; /* a pointer to current word */
    int num0fLine = 0;/*count line of the current line */
    int instructionCounter = 100; /*instruction counter*/
    int dataCounter = 0;/*data counter*/
    long prevLocation;

    inputFile = openTheFile(file_name, "am", "r");
    outputFile = openTheFile("tempFile", "am", "w+");
    fileValidLabels = openTheFile("LabelFile", "am",
                                  "w+");/*open validFile to write all labels that declare in received file */
    ValidEntryFile = openTheFile("EntryFile", "am",
                                 "w+");/*open Entry File to write all labels with .entry declaration */
    if (!inputFile) {/* If the file couldn't be opened for reading */
        identifyError("Couldn't open input file!", num0fLine);
        flagsArray[ERROR] = EXIST;
        return NULL;
    }
    printf("Beginning primary iteration on the file: %s...\n", file_name);
    while (!feof(inputFile)) { /*Go line by line in the received file*/
        TagTemp = NULL;
        prevLocation = ftell(inputFile);
        readAndCopyRow(inputFile, lineValidation, originalLine);
        num0fLine++;
        current_word = strtok(lineValidation, " \t\n\v\f\r");/* cut the first word in the line */
        if (!current_word || current_word[0] == ';')/*A comment or a blank line*/
            continue;/*continue to the next line*/
        if (current_word[strlen(current_word) - 1] == ':') {/*Checking whether a label*/
            if (!HandelLabel(&HeadTagList, current_word, instructionCounter, num0fLine,
                             &TagTemp)) {/*checks validate of the label*/
                flagsArray[ERROR] = EXIST;/* if a occurred an error */
                continue;
            } else {
                current_word = strtok(NULL, " \t\n\v\f\r");/* cut the next word in the line */
                if (!current_word) {
                    identifyError("Found an empty label declaration", num0fLine);
                    flagsArray[ERROR] = EXIST;/* if  occurred an error */
                    continue;
                }
            }
        }
        if (current_word[0] == '.') { /*Checking whether is instruction*/
            if (!instructionsFormat(&HeadTagList, current_word, &dataCounter, ValidEntryFile, num0fLine, &TagTemp,
                                    flagsArray, prevLocation, inputFile, originalLine)) {
                flagsArray[ERROR] = EXIST;/* if a occurred an error */
            }
            fprintf(outputFile, "%s", originalLine);/*Copy the row without change*/
            continue;
        } /* if the current word is a command */
        if (check_op_name(current_word)) {
            if (!validateCommand(current_word, &instructionCounter, fileValidLabels, num0fLine, &HeadTagList,
                                 originalLine)) {
                flagsArray[ERROR] = EXIST;/* if a occurred an error */
                continue;
            }
        } else {
            printf("Error occurred at line %d: Invalid command: '%s'\n", num0fLine, current_word);
            flagsArray[ERROR] = EXIST;/* if a occurred an error */
        }
        fprintf(outputFile, "%s", originalLine);/*Copy the row without change*/
    }
    deleteFile(file_name, "am");
    inputFile = openTheFile(file_name, "am", "w");
    fseek(outputFile, 0, SEEK_SET);
    while (!feof(outputFile))
        fputc(fgetc(outputFile), inputFile);
    deleteFile("tempFile", "am");
    changeICTags(&HeadTagList,
                 instructionCounter); /* Updating all data and string tag (add IC final value to their address counter) */
    if (!handel_label_entry(ValidEntryFile, &HeadTagList))
        flagsArray[ERROR] = EXIST;/* exist .entry label that not valid in the file*/
    if (!handel_label_not_found(fileValidLabels, &HeadTagList))
        flagsArray[ERROR] = EXIST;/* exist label that not defined in the file*/
    flagsArray[ICcounter] = instructionCounter;/*save final IC to be use in the second phase*/
    flagsArray[DCcounter] = dataCounter;/*save final DC to be use in the second phase*/
    closeTheFiles(inputFile, fileValidLabels, ValidEntryFile);/* free all files*/
    if (HeadTagList != NULL)
        allUsed(HeadTagList, 1);/*this method checks for unused tags*/
    if (flagsArray[ERROR] == EXIST) {/* if a error occurred we stop the process and free/delete all memory we used*/
        printf("First iteration on file: %s.am failed!\n", file_name);
        deleteFile(file_name, "am");
        freelist(HeadTagList);/* free the linked-lists */
        return NULL;
    }
    printf("Complete primary iteration on file: %s.am!\n", file_name);
    print1(HeadTagList);
    return HeadTagList;
}

