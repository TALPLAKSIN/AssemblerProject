#include "HandelLable.h"

int HandelTagName(char *word) {
    int i=0;
    /*check if the word is not NULL, starts with an alphabet character, and is within the maximum label length*/
    if (word != NULL && isalpha(word[0]) && strlen(word) <= MAX_LABEL_LENGTH) {
        /*Check each character in the word to ensure it contains only alphanumeric characters*/
        for (i = 0; i < strlen(word); i++) {
            if (!isalnum(word[i]))
                return FALSE;
        }
        return TRUE;
    }
    return FALSE;/*Return FALSE if the word is NULL, doesn't start with an alphabet character, or exceeds the maximum label length*/
}

int HandelLabel(TagList *HeadTagList, char *name_of_label, int instructionCounter, int num0fLine, TagList *TagTemp) {
    char validLineArray[MaxInputLength] = {0};
    /*Remove newline character from the tag*/
    name_of_label[strlen(name_of_label) - 1] = '\0';
    make_copy(validLineArray, name_of_label);
    /*Deleting all white characters to the right and left of the string*/
    removeLeftWSpaces(validLineArray);
    removeRightWSpaces(validLineArray);
    if (HandelTagName(validLineArray)) {
        /*Search for the label in the tag list*/
        *TagTemp = SearchTag(*HeadTagList, validLineArray);
        /*If the label doesn't exist and is not a reserved word, create a new tag and add it to the tag list*/
        if (!(*TagTemp) &&
            (!is_reserved_word(validLineArray))) {/*check that we have a legal label and exist in the tagList*/
            *TagTemp = NewTag(validLineArray, instructionCounter);
            InsertTagToList(HeadTagList, *TagTemp);/*it's valid , we can to add to the tag list*/
            return TRUE;
        }
        if ((*TagTemp) != NULL)/*forbidden multiple definitions of the same label*/
            identifyError( "Only allowed definition of a label once", num0fLine);
        else/*label cannot be a reserved word*/
            identifyError("The label must not complex from reserved word", num0fLine);
        return FALSE;
    }
    if (validLineArray[0] != '\0')
        printf("Error occurred at line %d: Invalid label name: %s\n", num0fLine, validLineArray);
    else/*Label cannot be empty*/
        identifyError("A label must not contain anything", num0fLine);
    return FALSE;
}


int handel_label_not_found(FILE *fileValidLabels, TagList *HeadTagList) {
    int flag = TRUE;
    char lineCheck[MaxInputLength] = {0};/*store each line from fileValidLabels*/
    TagList TagTemp = NULL; /*Temporary tag list pointer*/
    char *currentLabel = NULL;/*Pointer to the current label*/
    fseek(fileValidLabels, 0, SEEK_SET);/*Move the file pointer to the beginning of fileValidLabels*/
    while (!feof(fileValidLabels)) {
        memset(lineCheck, 0, MaxInputLength);
        /* iterating through each line(in every line exist 1 label) of the fileValidLabels file */
        fgets(lineCheck, MaxInputLength, fileValidLabels);
        currentLabel = strtok(lineCheck, " \t\n\v\f\r");/*extract the label*/
        /*If no label is found, return flag*/
        if (!currentLabel) {
            if (!flag)
                printf("\n");
            return flag;
        }/*Verify whether the label exists within the tag list*/
        TagTemp = SearchTag(*HeadTagList, currentLabel);
        if (TagTemp != NULL) {
            /*Set the "used" flag of the tag to TRUE (label is used in the code)*/
            setUsed(TagTemp, TRUE);
            continue;
        } else {/*Handle case where label is not found in the tag list*/
            if (flag)
                printf("No declaration of this labels: '%s'", currentLabel);
            else
                printf(",'%s'", currentLabel);
            flag = FALSE;/* Set flag to indicate label not found*/
        }
    }
    return TRUE;
}


int handel_label_entry(FILE *ValidEntryFile, TagList *HeadTagList) {
    char lineCheck[MaxInputLength] = {0};
    TagList TagTemp = NULL;
    char *currentLabel=NULL;
    /* Move the file pointer to the beginning of ValidEntryFile */
    fseek(ValidEntryFile, 0, SEEK_SET);
    while (!feof(ValidEntryFile)) { /* Loop through each line in ValidEntryFile until EOF is reached */
        currentLabel = NULL;
        memset(lineCheck, 0, MaxInputLength);
        /* Read a line from ValidEntryFile into lineCheck buffer */
        fgets(lineCheck, MaxInputLength, ValidEntryFile);
        currentLabel = strtok(lineCheck, " \t\n\v\f\r");/*extract the label */
        /* If no label is found, it means there's an empty line */
        if (!currentLabel)
            return TRUE;
        TagTemp = SearchTag(*HeadTagList, currentLabel);/*checks if the label is defined in the tag list */
        /* Check if the label is defined and not of type EXTERNAL */
        if ((TagTemp) != NULL &&(getType(TagTemp) != EXTERNAL)) {
            setType(TagTemp, ENTRY);/* Set the type of the label as ENTRY */
            continue;/* Continue to the next line */
        }
        if (!(TagTemp) || getType(TagTemp) == EXTERNAL) {
            if (!(TagTemp))/*no declaration on this label*/
                printf("This label has not been defined\n");
            else/*a label can be entry or external*/
                printf("label can get an entry or an external type,but cannot use both options at the same time\n");
            return FALSE;
        }
    }
    return TRUE;
}
