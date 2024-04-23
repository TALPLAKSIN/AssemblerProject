#include "HandelLable.h"

int HandelTagName(char *word) {
    int i;
    if (word != NULL && isalpha(word[0]) && strlen(word) <= MAX_LABEL_LENGTH) {
        for (i = 0; i < strlen(word); i++) {
            if (!isalnum(word[i]))
                return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

int HandelLabel(TagList *HeadTagList, char *name_of_label, int instructionCounter, int num0fLine, TagList *TagTemp) {
    char validLineArray[MaxInputLength] = {0};
    name_of_label[strlen(name_of_label) - 1] = '\0'; /*we are cutting '\n' from it*/
    make_copy(validLineArray, name_of_label);
    removeLeftWSpaces(validLineArray);
    removeRightWSpaces(validLineArray);
    if (HandelTagName(validLineArray)) {
        *TagTemp = SearchTag(*HeadTagList, validLineArray);
        if (!(*TagTemp) &&
            (!is_reserved_word(validLineArray))) {/*check that we have a legal label and exist in the tagList*/
            *TagTemp = NewTag(validLineArray, instructionCounter);
            InsertTagToList(HeadTagList, *TagTemp);/*we have a legal label --> add to the tag list*/
            return TRUE;
        }
        if ((*TagTemp) != NULL)
            identifyError("Found multiple definition of the same label", num0fLine);
        else
            identifyError("label can't be a reserved word", num0fLine);
        return FALSE;
    }
    if (validLineArray[0] != '\0')
        printf("Error occurred at line %d: Invalid label name: %s\n", num0fLine, validLineArray);
    else
        identifyError("the label cannot be empty", num0fLine);
    return FALSE;
}


int handel_label_not_found(FILE *fileValidLabels, TagList *HeadTagList) {
    int flag = TRUE;
    char lineCheck[MaxInputLength] = {0};
    TagList TagTemp = NULL;
    char *currentLabel = NULL;
    fseek(fileValidLabels, 0, SEEK_SET);
    while (!feof(fileValidLabels)) {
        memset(lineCheck, 0, MaxInputLength);
        /* iterating through each line(in every line exist 1 label) of the fileValidLabels file */
        fgets(lineCheck, MaxInputLength, fileValidLabels);
        currentLabel = strtok(lineCheck, " \t\n\v\f\r");
        if (!currentLabel) {
            if (!flag)
                printf("\n");
            return flag;
        }
        TagTemp = SearchTag(*HeadTagList, currentLabel);/*checks if the label is defined in the tag list */
        if (TagTemp != NULL) {
            setUsed(TagTemp, TRUE);
            continue;
        } else {
            if (flag)
                printf("The labels is not declared in the code: '%s'", currentLabel);
            else
                printf(",'%s'", currentLabel);
            flag = FALSE;
        }
    }
    return TRUE;
}


int handel_label_entry(FILE *ValidEntryFile, TagList *HeadTagList) {
    char lineCheck[MaxInputLength] = {0};
    TagList TagTemp = NULL;
    char *currentLabel;
    fseek(ValidEntryFile, 0, SEEK_SET);
    while (!feof(ValidEntryFile)) {
        currentLabel = NULL;
        memset(lineCheck, 0, MaxInputLength);
        /* iterating through each line(in every line exist 1 label) of the ValidEntryFile file */
        fgets(lineCheck, MaxInputLength, ValidEntryFile);
        currentLabel = strtok(lineCheck, " \t\n\v\f\r");
        if (!currentLabel)/* There are empty line */
            return TRUE;
        TagTemp = SearchTag(*HeadTagList, currentLabel);/*checks if the label is defined in the tag list */
        if ((TagTemp) != NULL &&
            (getType(TagTemp) != EXTERNAL)) {/*make sure that the label is not  defined as EXTERNAL type*/
            setType(TagTemp, ENTRY);/* if it's a legal label, type defined as ENTRY */
            continue;
        }
        if (!(TagTemp) || getType(TagTemp) == EXTERNAL) {
            if (!(TagTemp))
                printf("no declaration on this label\n");
            else
                printf("a label can be entry or external, but prohibited both\n");
            return FALSE;
        }
    }
    return TRUE;
}
