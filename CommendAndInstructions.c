#include "CommendAndInstructions.h"

int
instructionsFormat(TagList *HeadTagList, char *current_word, int *dataCounter, FILE *ValidEntryFile, int num0fLine,TagList *TagTemp,int *flagsArray, long prevLocation, FILE *input_file, char originalLine[]) {
    /* Check if the current word is .define instruction */
    if (!strcmp(".define", current_word))
        return checkDefineFormat(HeadTagList, strtok(NULL, ""), dataCounter, num0fLine, TagTemp);
        /* Check if the current word is .entry instruction */
    else if (!strcmp(".entry", current_word)) {
        flagsArray[EN] = OCCUR; /* indicates that we have entry type label*/
        return checkEntryFormat(HeadTagList, strtok(NULL, ""), dataCounter, ValidEntryFile, num0fLine, TagTemp);
        /* Check if the current word is .extern instruction */
    } else if (!strcmp(".extern", current_word)) {
        flagsArray[EX] = OCCUR;/* indicates that we have extern type label*/
        return checkExternFormat(HeadTagList, strtok(NULL, ""), dataCounter, num0fLine, TagTemp);
        /* Check if the current word is .string instruction */
    } else if (!strcmp(".string", current_word))
        return checkStringFormat(HeadTagList, strtok(NULL, ""), dataCounter, num0fLine, TagTemp);
        /* Check if the current word is .data instruction */
    else if (!strcmp(".data", current_word))
        return checkDataFormat(HeadTagList, strtok(NULL, ""), dataCounter, num0fLine, TagTemp, prevLocation, input_file,
                               originalLine);
    identifyError("An invalid instruction", num0fLine);
    return FALSE;/*If none of the above match, it's an invalid instruction*/
}

int checkDefineFormat(TagList *HeadTagList, char *curLine, int *dataCounter, int num0fLine, TagList *TagTemp) {
    long value=0;
    char validLineArray[MaxInputLength] = {0};
    char validLineArray2[MaxInputLength] = {0};
    char *defineName=NULL;
    if (make_copy(validLineArray, curLine)) {
        /*Deletes white characters from both ends of the string*/
        removeLeftWSpaces(validLineArray);
        removeRightWSpaces(validLineArray);
        defineName = strtok(validLineArray, " \t\n\v\f\r");/*Get define name from the line */
        curLine = strtok(NULL, "");/*a pointer to the next word in the line */
        if (HandelTagName(defineName)) {
            *TagTemp = SearchTag(*HeadTagList, defineName);/*Search for define name in the tag list*/
            /*If the tag doesn't exist,and it's not a reserved word*/
            if (!(*TagTemp) && (!is_reserved_word(defineName))) {
                *TagTemp = NewTag(defineName, *dataCounter); /*Create a new tag*/
                if (make_copy(validLineArray2, curLine)) {
                    /*Deletes white characters from both ends of the string*/
                    removeRightWSpaces(validLineArray2);
                    removeLeftWSpaces(validLineArray2);
                    if (validLineArray2[0] == '=') { /*Check if the line starts with '=' after define name */
                        validLineArray2[0] = ' ';
                        removeLeftWSpaces(validLineArray2);
                        /*Check if the rest is a valid number*/
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
    TagList TagTemp = SearchTag(*HeadTagList, defineName);/*Search for the define tag in the tag list*/
    /* Check if the tag is not found or if it's not of type MDEFINE (macro define)*/
    if (TagTemp == NULL || getType(TagTemp) != MDEFINE)
        return FALSE;
    else {
        /*Convert the value of the define tag to string and store it in the 'value' array*/
        sprintf(value, "%d", getValueOrSize(TagTemp));
        /*Write value into the original line*/
        WriteDefine(getName(TagTemp), value, originalLine);
        return TRUE;
    }
}

int checkEntryFormat(TagList *HeadTagList, char *tag, int *dataCounter, FILE *ValidEntryFile, int num0fLine,
                     TagList *TagTemp) {
    char validLineArray[MaxInputLength]= {0};
    if (*TagTemp != NULL) { /*   whether label before an .entry instruction, then the tag is deleted*/
        identifyWarning(
                "Deleting the new tag because an .entry instruction already exists with a tag with the same name.",
                num0fLine);
        moveHead(HeadTagList);
    }
    if (tag != NULL) {
        tag[strlen(tag) - 1] = '\0'; /*Remove newline character from the tag*/
        memset(validLineArray, 0, MaxInputLength);
        make_copy(validLineArray, tag);
        removeLeftWSpaces(validLineArray);
        removeRightWSpaces(validLineArray);
        tag[strlen(tag) - 1] = '\0'; /* / Remove colon(:) from the tag*/
        /*Check if all valid*/
        if (validLineArray[0] != '\0' &&
            HandelTagName(validLineArray)) {
            /* write it in entry file*/
            fprintf(ValidEntryFile, "%s\n", validLineArray);
            return TRUE;
        }
        if (validLineArray[0] != '\0')
            printf("Error occurred at line %d: Invalid label name: %s\n", num0fLine, tag);
        else
            identifyError("An entry instruction was declared without any label with it", num0fLine);
        return FALSE;
    }
    identifyError("An entry instruction was declared without any label with it", num0fLine);
    return FALSE;
}

int checkExternFormat(TagList *HeadTagList, char *tag, int *dataCounter, int num0fLine, TagList *TagTemp) {
    if (*TagTemp != NULL) {
        identifyWarning(
                "Deleting the new tag because an extern instruction already exists with a tag with the same name",
                num0fLine);
        moveHead(HeadTagList);
    }/*Check if the tag is not NULL and validate it as a label*/
    if (tag != NULL && HandelLabel(HeadTagList, tag, *dataCounter, num0fLine, TagTemp)) {
        setType(*TagTemp,
                EXTERNAL);/*Set the type of the label to EXTERNAL and address to 0 if it's a valid .extern declaration */
        setAddress(*TagTemp, 0);
        return TRUE;
    }
    if (!tag)
        identifyError("An external instruction was declared without any label with it", num0fLine);
    return FALSE;
}

int checkStringFormat(TagList *HeadTagList, char *curLine, int *dataCounter, int num0fLine, TagList *TagTemp) {
    int i = 0;
    int Length = 0;
    int validStr = 0;
    char validLineArray[MaxInputLength] = {0};
    /*If there was a previous tag declaration before .string, set its address and type*/
    if (*TagTemp != NULL) {
        setAddress(*TagTemp, *dataCounter);
        setType(*TagTemp, DATA);
    }
    if (make_copy(validLineArray, curLine)) {
        /*Deletes white characters from both ends of the string*/
        removeRightWSpaces(validLineArray);
        removeLeftWSpaces(validLineArray);
        if (validLineArray[i] != '\0') {/*Check if the string is not empty*/
            /* Check if the string starts with a double quote (") */
            if (validLineArray[i] == '\"') {
                for (i = 1; i < strlen(validLineArray) && validLineArray[i] != '\n' && validLineArray[i] != '\0' &&
                            !validStr; i++) {
                    Length++;/*count the amount of chars*/
                    if (validLineArray[i] == '\"') /* Check if the string ends with a double quote (") */
                        validStr = TRUE;
                }
                if (validStr && Length != 1) {
                    *dataCounter = *dataCounter + Length; /*increase DC according to Length*/
                    if (i == strlen(validLineArray))
                        return TRUE;
                    else {
                        identifyError("Illegal characters were found after the string", num0fLine);
                        return FALSE;
                    }
                } else {
                    if (!validStr)
                        identifyError("Must appear \" at the end of the string", num0fLine);
                    else
                        identifyError("The .string instruction is empty - no characters", num0fLine);
                    return FALSE;
                }
            }
            identifyError("Must appear \" at the start of the string", num0fLine);
            return FALSE;
        }
        identifyError(".string instruction must not contain only white characters", num0fLine);
        return FALSE;
    }
    identifyError("In .string instruction It must contain a string", num0fLine);
    return FALSE;
}

int checkDataFormat(TagList *HeadTagList, char *curLine, int *dataCounter, int num0fLine, TagList *TagTemp,
                    long prevLocation,
                    FILE *inputFile, char originalLine[]) {
    int foundNumbers = 0;
    char *nextNumber = NULL;/*Pointer to the next number in the input line*/
    int sizeArray = 0; /*Size of the data array*/
    char validLineArray[MaxInputLength * 2] = {0};
    char tempNumber[MaxInputLength] = {0};/*Temporary array to store each number*/
    if (*TagTemp != NULL) {
        setAddress(*TagTemp, *dataCounter);
        setType(*TagTemp, DATA);
    }
    /*Add spaces after commas in the input line*/
    if (adding_space(curLine, validLineArray)) {
        /*Check if the current line is not empty and doesn't start or end with a comma*/
        if ((validLineArray[0] != '\0') && (validLineArray[0] != ',') &&
            (validLineArray[strlen(validLineArray) - 2] != ',')) {
            nextNumber = strtok(validLineArray, ",");
            while (nextNumber != NULL) {
                memset(tempNumber, 0, MaxInputLength);
                foundNumbers = TRUE;/*Flag to track if numbers are found in the .data instruction*/
                make_copy(tempNumber, nextNumber);
                removeLeftWSpaces(tempNumber);
                /*Check if the number is valid  and update the data counter*/
                if (tempNumber[0] != '\0' && (checkValidNumber(tempNumber, TRUE) ||
                                              checkAndReplaceDefine(HeadTagList, tempNumber,
                                                                    originalLine))) {/*flag used to mark that the number cloud be 14 bit */
                    (*dataCounter)++;/*update DC*/
                    sizeArray++;
                    nextNumber = strtok(NULL, ",");
                    continue;
                } else {
                    if (tempNumber[0] == '\0')
                        identifyError("A comma must separate two numbers", num0fLine);
                    else if (isdigit(tempNumber[0]) == 0)
                        printf("Error occurred at line %d: invalid define '%s' \n", num0fLine, tempNumber);
                    else
                        printf("Error occurred at line %d: .data instruction has illegal number '%s' \n", num0fLine,
                               tempNumber);
                    return FALSE;
                }
            }
            if (!foundNumbers)
                identifyError("In .data instruction It must contain numbers", num0fLine);
            if (*TagTemp != NULL)
                setValueOrSize(*TagTemp, sizeArray);
            return foundNumbers;
        }
    }
    if (!curLine || validLineArray[0] == '\0')
        identifyError(".data instruction must contain numbers", num0fLine);
    else if (validLineArray[0] == ',')
        identifyError("In .data instruction comma cannot appear at the beginning", num0fLine);
    else
        identifyError("In .data instruction comma cannot appear at the end", num0fLine);
    return FALSE;
}