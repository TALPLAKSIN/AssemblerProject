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
