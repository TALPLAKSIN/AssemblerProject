#include "HandelLable.h"
int HandelTagName(char *name) {
    int i;
    if (name != NULL && isalpha(name[0]) && strlen(name) <= MAX_LABEL_LENGTH) {
        for (i = 0; i < strlen(name) ;i++) {
            if (!isalnum(name[i]))
                return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}
int handel_label(TagList *HeadTagList, char *labelName, int IC, int countLine, TagList *TagTemp) {
    char restOfLine[MAX_LINE_LENGTH]={0};
    labelName[strlen(labelName) - 1] = '\0'; /*we are cutting '\n' from it*/
    copy(restOfLine, labelName);
    LeftSpaces(restOfLine);
    if (HandelTagName(restOfLine)) {
        *TagTemp = SearchTag(*HeadTagList, restOfLine);
        if (!(*TagTemp) &&(!savedWord(restOfLine))) {/*check that we have a legal label and exist in the symbolList*/
            InsertTagToList(HeadTagList, *TagTemp);/*we have a legal label --> add to the symbol list*/
            return TRUE;
    }
        if ((*TagTemp) != NULL)
            findError("Found multiple definition of the same label", countLine);
}