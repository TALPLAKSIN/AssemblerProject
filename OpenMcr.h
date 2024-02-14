//
// Created by טל פלקסין on 22/01/2024.
//

#ifndef M1_OPENMCR_H
#define M1_OPENMCR_H
#include <stdio.h>
#include "McrList.h"
#define MAX_LINE_LENGTH 80
void WriteMcr(FILE *inputFile, int end, FILE *outFile) ;
FILE *openAndCheckFile(char *fileName)
;int SearchAndAddMcr(char *fileName);
#endif //M1_OPENMCR_H
