#include "convertInstructions.h"

void dealWithInstructions(TagList *HeadTagList, char *action, int *dataCounter, FILE *data_file) {
    if (!strcmp(".data", action))/*Checking if this it is a data order and handling accordingly*/
        convertDataToBaseFour(strtok(NULL, ""), dataCounter, data_file);
    if (!strcmp(".string", action))/*Checking if this it is a string order and handling accordingly*/
        convertStringToBaseFour(strtok(NULL, ""), dataCounter, data_file);
}

void convertDataToBaseFour(char *currLine, int *dataCounter, FILE *data_file) {
    char *nextNumber = NULL;
    char validLineArray[MaxInputLength] = {0};
    /*save the real line without changing it*/
    make_copy(validLineArray, currLine);
    /*take the first number*/
    nextNumber = strtok(validLineArray, " \t\n\v\f\r,");
    while (nextNumber != NULL) {/*throw all the number in data instruction*/
        convertToBaseFour(nextNumber, FALSE, data_file, dataCounter);/*write the number to the data_file*/
        nextNumber = strtok(NULL, " \t\n\v\f\r,");/*take the next number*/
    }
}

void convertStringToBaseFour(char *currLine, int *dataCounter, FILE *data_file) {
    int i=0;
    char validLineArray[MaxInputLength] = {0};
    /*save the real line without changing it*/
    make_copy(validLineArray, currLine);
    for (i = 1; validLineArray[i] != '\"'; i++)/*throw all the char in string instruction*/
        convertToBaseFour(&validLineArray[i], TRUE, data_file,dataCounter);/*write the char to the data_file*/
    *dataCounter = *dataCounter + 1;/*Adds one to the data counter*/
    if (*dataCounter < 1000)/*complete '0' to the file if necessary*/
        fprintf(data_file, "0");
    fprintf(data_file, "%d\t*******\n", *dataCounter);/*write 0 line to the data_file*/

}









