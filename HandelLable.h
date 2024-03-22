
#ifndef M1_HANDELLABLE_H
#define M1_HANDELLABLE_H
#include "TagList.h"
#include "OperationLine.h"
#define MAX_LABEL_LENGTH 32
int HandelTagName(char *name);
int handel_label(TagList *HeadTagList, char *labelName, int IC, int countLine, TagList *TagTemp);
int handel_label_not_found(FILE *validLabelFile, TagList *HeadTagList);
#endif //M1_HANDELLABLE_H
