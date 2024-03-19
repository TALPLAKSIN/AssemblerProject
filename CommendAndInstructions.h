
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
int
instructionsFormat(TagList *HeadTagList, char *curWord, int *DC, FILE *checksEntry, int countLine, TagList *TagTemp,
                   int *markValues, long prevLocation, FILE *inputFile);
int checkDefineFormat(TagList *HeadTagList, char *line, int *DC, int countLine, TagList *TagTemp);
#endif //M1_COMMENDANDINSTRUCTIONS_H
