
#ifndef M1_COMMENDANDINSTRUCTIONS_H
#define M1_COMMENDANDINSTRUCTIONS_H
#include "HandelLable.h"
static const struct instructionName {
    const char *name;
} instructionNames[] = {
        {".define"},
        {".entry"},
        {".extern"},
        {".string"},
        {".data"},
};
enum flagsNames {
    ICcounter, DCcounter, EX, EN, ERROR
};
#endif //M1_COMMENDANDINSTRUCTIONS_H
