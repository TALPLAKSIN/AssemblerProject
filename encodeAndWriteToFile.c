#include "encodeAndWriteToFile.h"

int convertFileToBase4(char *file_name, TagList *HeadTagList, int *flagsArray) {
    /*Pointers to files*/
    FILE *input_file = NULL;
    FILE *instructions_file = NULL;
    FILE *data_file = NULL;
    FILE *entry_file = NULL;
    FILE *extern_file = NULL;

    char currLine[MaxInputLength] = {0};/*current line from the file*/
    char originalLine[MaxInputLength] = {0};/*current line from the file unchanged*/
    char *current_word = NULL;/*A word we cut from the current line*/
    int dataCounter = flagsArray[ICcounter] - 1;/* Data counter */
    int instructionCounter = 99;/* Instruction counter */
    int numOfLine = 0;

    printf("Beginning second iteration on the file: %s...\n", file_name);
    if (flagsArray[EX]!=NOT_OCCUR) /*If there is an indication of an external label we will create a suitable file*/
        extern_file = openTheFile(file_name, "ext", "w+");
    /*open files*/
    input_file = openTheFile(file_name, "am", "r");
    instructions_file = openTheFile(file_name, "cmd", "w+");
    data_file = openTheFile(file_name, "data", "w+");
    /*write Instruction counter and Data counter*/
    fprintf(instructions_file, "\t%d\t%d\n", flagsArray[ICcounter] - 100, flagsArray[DCcounter]);
    /*A call to a method that will perform all the tests and
     * create the appropriate file if necessary for an entry label*/
    dealWithEntry(file_name, HeadTagList, entry_file, flagsArray);
    /*Encoding the file by traversing the entire file*/
    while (!feof(input_file)) {
        /*Receiving a row from the file and copying it to two auxiliary arrays*/
        readAndCopyRow(input_file, currLine, originalLine);
        numOfLine++;
        current_word = strtok(currLine, " \t\n\v\f\r");/*save the current word*/
        if (!current_word || current_word[0] == ';')/*A comment or a blank line*/
            continue;
        if (current_word[strlen(current_word) - 1] == ':')/*Checking whether a label*/
            current_word = strtok(NULL, " \t\n\v\f\r,");/*continue to the next line*/
        if (current_word[0] == '.')  /*Checking whether is instruction*/
            dealWithInstructions(HeadTagList, current_word, &dataCounter, data_file);
        else /*it must be legal we already check it*/
            convertSentenceToBase4(HeadTagList, current_word, &instructionCounter, instructions_file, extern_file);
    }
    printf("Complete second pass on file.\n");
    unitesFiles(file_name, instructions_file, data_file);/* combining 2 files in to final object file*/
    /*  free/delete all memory we used*/
    finishFiles(file_name, input_file, entry_file, extern_file, instructions_file,data_file);
    return 0;
}

void dealWithEntry(char *file_name, TagList *HeadTagList, FILE *entry_file, int *flagsArray) {
    TagList temp = *HeadTagList;
    /*If there is an indication of an entry label we will create a suitable file*/
    if (flagsArray[EN]!=NOT_OCCUR) {
        entry_file = openTheFile(file_name, "ent", "w+");
        while (temp != NULL) {/*Throw allover the TagList*/
            if (getType(temp) == ENTRY) {
                /*Checking type equal ENTRY and write it*/
                fprintf(entry_file, "%s\t", getName(temp));
                if (getAddress(temp) < 1000)
                    fprintf(entry_file, "0");/*complete '0' to the file if necessary*/
                fprintf(entry_file, "%d\n", getAddress(temp));
            }
            temp = getNextTag(temp);
        }
    }
}