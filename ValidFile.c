//
// Created by טל פלקסין on 02/03/2024.
//
#include  "FileMethod.h"
#include "ValidFile.h"
TagList SearchAndAddSymbol(char *fileName,int *markValues) {/* each cell of the markValues array represent a flag (5 cell - ICcounter, DCcounter, EX, EN, ERROR ) */
    FILE *inputFile, *checksLabelFile, *checksEntry;/* a FILE pointer to received file and 2 check file (Label and Entry) */
    char lineCheck[MAX_LINE_LENGTH] = {0}, lineCopy[MAX_LINE_LENGTH] = {0};
    TagList HeadTagList = NULL, TagTemp = NULL;
    char *curWord = NULL; /* Holds the current word */
    int countLine = 0;/* Holds the number of the current line */
    int IC = 100;
    int DC = 0;
    long prevLocation;
    inputFile = open_file(fileName, "am", "r");/*open the received file for reading and check the process */
    /*open the Label File to write all labels that appear in received file, that we check after */
    checksLabelFile = open_file("LabelFile", "am", "w+");
    checksEntry = open_file("EntryFile", "am", "w+");/*open Entry File to write all labels with .entry declaration */
    if (!inputFile) {/* If the file couldn't be opened for reading */
        findError("Couldn't open input file!", countLine);
        markValues[ERROR] = EXIST;
        return NULL;
    }
    printf("Started first iteration on the file: %s...\n", fileName);

    while (!feof(inputFile)) {/*over all file, line by line*/
    TagTemp = NULL;
    prevLocation = ftell(inputFile);
    readAndCopyRow(inputFile, lineCheck, lineCopy);
    countLine++;
    curWord = strtok(lineCheck, " \t\n\v\f\r");/* cut the first word in the line */
    if (!curWord || curWord[0] == ';')/* if line is empty or note ( ';' represent a note) */
        continue;/*continue to the next line*/
    } else {
}

