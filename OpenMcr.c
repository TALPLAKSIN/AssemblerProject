#include "OpenMcr.h"
#include "McrList.h"
#include  "FileMethod.h"
#define MAX_LINE_LENGTH 80
void WriteMcr(FILE *inputFile, int end, FILE *outFile) {
    while (ftell(inputFile) != end)
        fputc(fgetc(inputFile), outFile);
}