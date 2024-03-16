//
// Created by טל פלקסין on 02/03/2024.
//

#ifndef M1_VALIDFILE_H
#define M1_VALIDFILE_H
#include "TagList.h"
#include "OperationLine.h"
#include "HandelLable.h"
enum flagsNames {
    ICcounter, DCcounter, EX, EN, ERROR
};

TagList SearchAndAddSymbol(char *fileName,int *markValues);
#endif //M1_VALIDFILE_H
