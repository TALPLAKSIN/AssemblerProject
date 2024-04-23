#include "CommendAndInstructions.h"

int
instructionsFormat(TagList *HeadTagList, char *current_word, int *dataCounter, FILE *ValidEntryFile, int num0fLine,
                   TagList *TagTemp,
                   int *flagsArray, long prevLocation, FILE *input_file, char originalLine[]) {
    if (!strcmp(".define", current_word))
        return checkDefineFormat(HeadTagList, strtok(NULL, ""), dataCounter, num0fLine, TagTemp);
    else if (!strcmp(".entry", current_word)) {
        flagsArray[EN] = EXIST; /* marks that we have entry label  */
        return checkEntryFormat(HeadTagList, strtok(NULL, ""), dataCounter, ValidEntryFile, num0fLine, TagTemp);
    } else if (!strcmp(".extern", current_word)) {
        flagsArray[EX] = EXIST;/* marks that we have extern label  */
        return checkExternFormat(HeadTagList, strtok(NULL, ""), dataCounter, num0fLine, TagTemp);
    } else if (!strcmp(".string", current_word))
        return checkStringFormat(HeadTagList, strtok(NULL, ""), dataCounter, num0fLine, TagTemp);
    else if (!strcmp(".data", current_word))
        return checkDataFormat(HeadTagList, strtok(NULL, ""), dataCounter, num0fLine, TagTemp, prevLocation, input_file,
                               originalLine);
    identifyError("found an illegal instruction", num0fLine);
    return FALSE;
}

int checkDefineFormat(TagList *HeadTagList, char *curLine, int *dataCounter, int num0fLine, TagList *TagTemp) {
    long value;
    char validLineArray[MaxInputLength] = {0};/* store the received line  */
    char validLineArray2[MaxInputLength] = {0};
    char *defineName;
    if (make_copy(validLineArray, curLine)) {
        removeLeftWSpaces(validLineArray);
        removeRightWSpaces(validLineArray);
        defineName = strtok(validLineArray, " \t\n\v\f\r");/* cut the next word in the line */
        curLine = strtok(NULL, "");/* cut the next word in the line */
        if (HandelTagName(defineName)) {
            *TagTemp = SearchTag(*HeadTagList, defineName);
            if (!(*TagTemp) && (!is_reserved_word(defineName))) {
                *TagTemp = NewTag(defineName, *dataCounter);
                /*remove white characters from the left and right of the string */
                if (make_copy(validLineArray2, curLine)) {
                    removeRightWSpaces(validLineArray2);
                    removeLeftWSpaces(validLineArray2);
                    if (validLineArray2[0] == '=') {
                        validLineArray2[0] = ' ';
                        removeLeftWSpaces(validLineArray2);
                        if (checkValidNumber(validLineArray2, TRUE)) {
                            value = strtol(validLineArray2, &curLine, 10);
                            setValueOrSize(*TagTemp, (int) value);
                            setType(*TagTemp, MDEFINE);
                            InsertTagToList(HeadTagList, *TagTemp);
                            return TRUE;
                        }
                        identifyError("Invalid number - must be an 10 base number", num0fLine);
                        return FALSE;
                    }
                    identifyError("must be a '=' after define name declaration", num0fLine);
                    return FALSE;
                }
                identifyError("Missing declaration after define tag!", num0fLine);
                return FALSE;
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
    identifyError("Missing declaration after .define instruction!", num0fLine);
    return FALSE;
}

int checkAndReplaceDefine(TagList *HeadTagList, char *defineName, char originalLine[]) {
    char value[MaxInputLength] = {0};
    TagList TagTemp = SearchTag(*HeadTagList, defineName);
    if (TagTemp == NULL || getType(TagTemp) != MDEFINE)
        return FALSE;
    else {
        sprintf(value, "%d", getValueOrSize(TagTemp));
        WriteDefine(getName(TagTemp), value, originalLine);
        return TRUE;
    }
}

int checkEntryFormat(TagList *HeadTagList, char *tag, int *dataCounter, FILE *ValidEntryFile, int num0fLine,
                     TagList *TagTemp) {
    char validLineArray[MaxInputLength];
    if (*TagTemp != NULL) { /* if had a declaration of a label before .entry , then we delete the tag */
        identifyWarning("found an entry instruction with a tag declared to it. new tag got deleted.", num0fLine);
        moveHead(HeadTagList);
    }
    if (tag != NULL) {
        tag[strlen(tag) - 1] = '\0'; /* we are cutting the /n from it,*/
        memset(validLineArray, 0, MaxInputLength);
        make_copy(validLineArray, tag);
        removeLeftWSpaces(validLineArray);
        tag[strlen(tag) - 1] = '\0'; /* we are cutting the colon(:) from it,*/
        if (validLineArray[0] != '\0' &&
            HandelTagName(validLineArray)) {/* if it .entry declaration and all valid, write it in entry file*/
            fprintf(ValidEntryFile, "%s\n", validLineArray);
            return TRUE;
        }
        if (validLineArray[0] != '\0')
            printf("Error occurred at line %d: Invalid label name: %s\n", num0fLine, tag);
        else
            identifyError("Found an entry instruction without any label!", num0fLine);
        return FALSE;
    }
    identifyError("Found an entry instruction without any label!", num0fLine);
    return FALSE;
}

int checkExternFormat(TagList *HeadTagList, char *tag, int *dataCounter, int num0fLine, TagList *TagTemp) {
    if (*TagTemp != NULL) { /* if had a declaration of a label before .extern , then we delete the tag */
        identifyWarning("found an extern instruction with a tag declared to it. new tag got deleted.", num0fLine);
        moveHead(HeadTagList);
    }
    if (tag != NULL && HandelLabel(HeadTagList, tag, *dataCounter, num0fLine, TagTemp)) {
        setType(*TagTemp, EXTERNAL);/*add the type of label, if it all valid and .extern declaration */
        setAddress(*TagTemp, 0);
        return TRUE;
    }
    if (!tag)
        identifyError("Found an extern instruction without any label!", num0fLine);
    return FALSE;
}

int checkStringFormat(TagList *HeadTagList, char *curLine, int *dataCounter, int num0fLine, TagList *TagTemp) {
    int i = 0;
    int Length = 0;
    int validStr = 0;
    char validLineArray[MaxInputLength] = {0};/* store the received line  */
    if (*TagTemp != NULL) {
        setAddress(*TagTemp, *dataCounter);
        setType(*TagTemp, DATA);
    }
    if (make_copy(validLineArray, curLine)) {
        /*remove white characters from the left and right of the string */
        removeRightWSpaces(validLineArray);
        removeLeftWSpaces(validLineArray);
        if (validLineArray[i] != '\0') {
            if (validLineArray[i] == '\"') { /*String must start with " */
                for (i = 1;
                     i < strlen(validLineArray) && validLineArray[i] != '\n' && validLineArray[i] != '\0' &&
                     !validStr; i++) {
                    Length++;
                    if (validLineArray[i] == '\"')
                        validStr = TRUE;/* valid string, ending with "*/
                }
                if (validStr && Length != 1) {
                    *dataCounter = *dataCounter + Length; /*increase DC according to the amount of chars*/
                    if (i == strlen(validLineArray))
                        return TRUE;
                    else {
                        identifyError("Found invalid text after string", num0fLine);
                        return FALSE;
                    }
                } else {
                    if (!validStr)
                        identifyError("valid string must end with \"", num0fLine);
                    else
                        identifyError("Missing chars in .string instruction", num0fLine);
                    return FALSE;
                }
            }
            identifyError("valid string must start with \"", num0fLine);
            return FALSE;
        }
        identifyError("only white spaces its not allow in string instruction", num0fLine);
        return FALSE;
    }
    identifyError("Missing string in .string instruction!", num0fLine);
    return FALSE;
}

int checkDataFormat(TagList *HeadTagList, char *curLine, int *dataCounter, int num0fLine, TagList *TagTemp,
                    long prevLocation,
                    FILE *inputFile, char originalLine[]) {
    int foundNumbers = 0;
    char *nextNumber = NULL;
    int sizeArray = 0;
    char validLineArray[MaxInputLength * 2] = {0};
    char tempNumber[MaxInputLength] = {0};
    if (*TagTemp != NULL) {
        setAddress(*TagTemp, *dataCounter);
        setType(*TagTemp, DATA);
    }
    if (adding_space(curLine, validLineArray)) { /*adding space after comma*/
        if ((validLineArray[0] != '\0') && (validLineArray[0] != ',') &&
            (validLineArray[strlen(validLineArray) - 2] != ',')) {
            nextNumber = strtok(validLineArray, ",");
            while (nextNumber != NULL) {
                memset(tempNumber, 0, MaxInputLength);
                foundNumbers = TRUE;
                make_copy(tempNumber, nextNumber);
                removeLeftWSpaces(tempNumber); /*remove white characters from the left of the string */
                if (tempNumber[0] != '\0' && (checkValidNumber(tempNumber, TRUE) ||
                                              checkAndReplaceDefine(HeadTagList, tempNumber,
                                                                    originalLine))) {/*flag used to mark that the number cloud be 14 bit */
                    (*dataCounter)++;/*increase DC according to the amount of numbers*/
                    sizeArray++;
                    nextNumber = strtok(NULL, ",");
                    continue;
                } else {
                    if (tempNumber[0] == '\0')
                        identifyError("between two commas must be number", num0fLine);
                    else if (isdigit(tempNumber[0]) == 0)
                        printf("Error occurred at line %d: define '%s' invalid! \n", num0fLine, tempNumber);
                    else
                        printf("Error occurred at line %d: number '%s' invalid in .data instruction! \n", num0fLine,
                               tempNumber);
                    return FALSE;
                }
            }
            if (!foundNumbers)
                identifyError("found a .data instruction without any numbers", num0fLine);
            if (*TagTemp != NULL)
                setValueOrSize(*TagTemp, sizeArray);
            return foundNumbers;
        }
    }
    if (!curLine || validLineArray[0] == '\0')
        identifyError("Missing numbers in .data instruction", num0fLine);
    else if (validLineArray[0] == ',')
        identifyError("Invalid ',' at the beginning of .data instruction", num0fLine);
    else
        identifyError("Invalid ',' at the end of .data instruction", num0fLine);
    return FALSE;
}
