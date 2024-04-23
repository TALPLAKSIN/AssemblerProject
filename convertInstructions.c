#include "convertInstructions.h"

void dealWithInstructions(TagList *HeadTagList, char *action, int *dataCounter, FILE *data_file) {
    if (!strcmp(".data", action))
        convertDataToBaseFour(strtok(NULL, ""), dataCounter, data_file);
    if (!strcmp(".string", action))
        convertStringToBaseFour(strtok(NULL, ""), dataCounter, data_file);
}

void convertDataToBaseFour(char *currLine, int *dataCounter, FILE *data_file) {
    char *nextNumber = NULL;
    char validLineArray[MaxInputLength] = {0};
    make_copy(validLineArray, currLine);
    nextNumber = strtok(validLineArray, " \t\n\v\f\r,");/* cut the first number from the string */
    while (nextNumber != NULL) {
        convertToBaseFour(nextNumber, FALSE, data_file, dataCounter);/*encoding the input and write to the data_file*/
        nextNumber = strtok(NULL, " \t\n\v\f\r,");/* cut the next number from the string */
    }
}

void convertStringToBaseFour(char *currLine, int *dataCounter, FILE *data_file) {
    int i;
    char validLineArray[MaxInputLength] = {0};
    make_copy(validLineArray, currLine);
    for (i = 1; validLineArray[i] != '\"'; i++) {/*over the string char by char*/
        convertToBaseFour(&validLineArray[i], TRUE, data_file,
                          dataCounter);/*encoding the input and write to the data_file*/
    }
    *dataCounter = *dataCounter + 1;
    if (*dataCounter < 1000)
        fprintf(data_file, "0");
    fprintf(data_file, "%d\t*******\n", *dataCounter);/*encoding 0 line in the end of the string*/

}









