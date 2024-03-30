//
// Created by טל פלקסין on 26/02/2024.
//

#ifndef M1_OPERATIONLINE_H
#define M1_OPERATIONLINE_H
#include "FileMethod.h"
#include <ctype.h>
#include <stdlib.h>
#include "definitionOfRegAndOperation.h"
#include "TagList.h"
#include "OperationLine.h"
#include "HandelLable.h"
void LeftSpaces(char line[MAX_LINE_LENGTH]) ;
void RightSpaces(char line[MAX_LINE_LENGTH]) ;
int copy(char restOfLine[MAX_LINE_LENGTH], char *line);
void findError(char *errorMsg, int countLine);
void findWarning(char *warningMsg, int countLine);
#endif //M1_OPERATIONLINE_H
