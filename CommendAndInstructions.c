
#include "CommendAndInstructions.h"
int instructionsFormat(TagList *HeadTagList, char *curWord, int *DC, FILE *checksEntry, int countLine, TagList *TagTemp,
                       int *markValues, long prevLocation, FILE *inputFile) {
    if (!strcmp(".define", curWord))
        return checkDefineFormat(HeadTagList, strtok(NULL, ""), DC, countLine, TagTemp);

}
int checkDefineFormat(TagList *HeadTagList, char *line, int *DC, int countLine, TagList *TagTemp) {}