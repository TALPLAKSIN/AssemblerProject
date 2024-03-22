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
        else
            findError("label can't be a reserved word", countLine);
        return FALSE;
    }
    if (restOfLine[0] != '\0')
        printf("Error occurred at line %d: Invalid label name: %s\n", countLine, restOfLine);
    else
        findError("the label cannot be empty", countLine);
    return FALSE;
}

int handel_label_not_found(FILE *validLabelFile, TagList *HeadTagList) {
    int flag = TRUE;
    char lineCheck[MAX_LINE_LENGTH] = {0};
    TagList TagTemp = NULL;
    char *currentLabel = NULL;
    fseek(validLabelFile, 0, SEEK_SET);
    while (!feof(validLabelFile)) {
        memset(lineCheck, 0, MAX_LINE_LENGTH);
        /* iterating through each line(in every line exist 1 label) of the checksLabelFile file */
        fgets(lineCheck, MAX_LINE_LENGTH, validLabelFile);
        currentLabel = strtok(lineCheck, " \t\n\v\f\r");
        if (!currentLabel) {
            printf("\n");
            return flag;
        }
    }
}