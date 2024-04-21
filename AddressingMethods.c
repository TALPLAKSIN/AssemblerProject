#include "AddressingMethods.h"

int instructionValidName(char *name) {
    int i;
    for (i = 0; i < MAX_NUM_INSTRUCTION; i++) {
        if (strcmp(name, instructionNames[i].name) == 0)
            return TRUE;
    }
    return FALSE;
}

int validateCommand(char *sentence, int *instructionCounter, FILE *fileValidLabels, int num0fLine, TagList *HeadTagList,char originalLine[]) {
    int opNumber;
    int mark;
    char validLineArray[MaxInputLength] = {0};
    opNumber = get_num_of_operation(sentence);/*Get the operation number from the command*/
    (*instructionCounter)++;/* Increment the instruction counter */
    if (opNumber == 0) {/* If the command doesn't require any operands */
        if (!make_copy(validLineArray, strtok(NULL, " \t\n\v\f\r")))
            return TRUE;/* Return TRUE if no characters are found*/
        identifyError("for this command no Operand allowed or any characters", num0fLine);
        return FALSE;
    }
    mark = make_copy(validLineArray, strtok(NULL, ""));
    if (mark && validLineArray[0] != ',') {
        /* Remove left and right whitespaces*/
        removeLeftWSpaces(validLineArray);
        removeRightWSpaces(validLineArray);
        if (opNumber == 1) /* if the command require one operand */
            return validDestOneOp(sentence, instructionCounter, fileValidLabels, num0fLine, validLineArray,HeadTagList, originalLine);
        else /* if the command require two operands */
            return validDestSourceTwoOp(sentence, instructionCounter, fileValidLabels, num0fLine, validLineArray,HeadTagList,originalLine);
    }/*Handle error cases for missing operand or illegal commas*/
    if (!mark) /* if its empty - Missing operand*/
        identifyError("Missing operand", num0fLine);
    else  /* if it starts with a comma - illegal comma */
        identifyError("illegal commas found right after the command name", num0fLine);
    return FALSE;
}

addressingMode getAddressingMode(char *operand, FILE *fileValidLabels, int mark,TagList *HeadTagList,char originalLine[]) {
    int i = 0;
    char *tag;
    char num_one_operand[MaxInputLength] = {0};
    if (operand != NULL && operand[0] != '\0') {
        if (check_reg_name(operand))/*if it legal register, its directRegisterAddress */
            return directRegisterAddress;
        if (HandelTagName(operand)) {
            if (mark)/*store all labels in the file and,completing this pass, verify that they have all been accurately defined*/
                fprintf(fileValidLabels, "%s\n", operand);
            return directAddress;
        } /*if an address begins with '#' followed by a number, its immediateAddress*/
        if (operand[i] == '#'&& strlen(operand)>1&&operand[i+1] != '#')
            operand = strtok(operand, "#");
        if (checkValidNumber(operand, FALSE))
            return immediateAddress;
        if (HeadTagList!=NULL && checkAndReplaceDefine(HeadTagList, operand,originalLine))
            return immediateAddress;
        make_copy(num_one_operand, operand);
        /*if an address begins with '[]' and inside has a valid number, its constantIndexAddress*/
        tag = strtok(num_one_operand, "[");
        if (operand[strlen(operand - 1) == ']']) {
            if (HandelTagName(tag)) {
                if (mark)/*store all labels in the file and,completing this pass, verify that they have all been accurately defined*/
                    fprintf(fileValidLabels, "%s\n", tag);
                tag = strtok(NULL, "]");
                if (checkValidNumber(tag, FALSE))
                    return constantIndexAddress;
                if (HeadTagList!=NULL && checkAndReplaceDefine(HeadTagList, tag, originalLine))
                    return constantIndexAddress;
            }
        }
    }
    return NON; /* Return NON if the addressing not adjusted or the operand is invalid */
}