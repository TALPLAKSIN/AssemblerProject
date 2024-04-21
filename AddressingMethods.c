#include "AddressingMethods.h"

int instructionValidName(char *name) {
    int i;
    for (i = 0; i < MAX_NUM_INSTRUCTION; i++) {
        if (strcmp(name, instructionNames[i].name) == 0)
            return TRUE;
    }
    return FALSE;
}

int validateCommand(char *sentence, int *instructionCounter, FILE *fileValidLabels, int num0fLine, TagList *HeadTagList,
                    char originalLine[]) {
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
            return validDestOneOp(sentence, instructionCounter, fileValidLabels, num0fLine, validLineArray, HeadTagList,
                                  originalLine);
        else /* if the command require two operands */
            return validDestSourceTwoOp(sentence, instructionCounter, fileValidLabels, num0fLine, validLineArray,
                                        HeadTagList, originalLine);
    }/*Handle error cases for missing operand or illegal commas*/
    if (!mark) /* if its empty - Missing operand*/
        identifyError("Missing operand", num0fLine);
    else  /* if it starts with a comma - illegal comma */
        identifyError("illegal commas found right after the command name", num0fLine);
    return FALSE;
}

addressingMode
getAddressingMode(char *operand, FILE *fileValidLabels, int mark, TagList *HeadTagList, char originalLine[]) {
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
        if (operand[i] == '#' && strlen(operand) > 1 && operand[i + 1] != '#')
            operand = strtok(operand, "#");
        if (checkValidNumber(operand, FALSE))
            return immediateAddress;
        if (HeadTagList != NULL && checkAndReplaceDefine(HeadTagList, operand, originalLine))
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
                if (HeadTagList != NULL && checkAndReplaceDefine(HeadTagList, tag, originalLine))
                    return constantIndexAddress;
            }
        }
    }
    return NON; /* Return NON if the addressing not adjusted or the operand is invalid */
}

int validDestOneOp(char *sentence, int *instructionCounter, FILE *fileValidLabels, int num0fLine, char validLineArray[],
                   TagList *HeadTagList, char originalLine[]) {
    addressingMode destination_operand = getAddressingMode(validLineArray, fileValidLabels, TRUE, HeadTagList,
                                                           originalLine);
    (*instructionCounter)++;/* Increment the instruction counter to point the next cell */
    if (destination_operand == directAddress || destination_operand == directRegisterAddress)
        return TRUE;
    if ((strcmp(sentence, "prn") == 0) && (destination_operand == immediateAddress))
        return TRUE;
    (*instructionCounter)++;/* increase IC to point the next cell */
    if (destination_operand == constantIndexAddress &&
        ((strcmp(sentence, "dec") == 0) || (strcmp(sentence, "red") == 0) || (strcmp(sentence, "prn") == 0) ||
         (strcmp(sentence, "not") == 0) || (strcmp(sentence, "clr") == 0) || (strcmp(sentence, "inc") == 0)))
        return TRUE;
    (*instructionCounter) -= 2;
    if (destination_operand == NON)
        identifyError("Invalid definition of a Operand!", num0fLine);
    else
        identifyError("Invalid destination address!", num0fLine);
    return FALSE;
}

int validDestSourceTwoOp(char *sentence, int *instructionCounter, FILE *fileValidLabels, int num0fLine,
                         char validLineArray[], TagList *HeadTagList, char originalLine[]) {
    char num_one_operand[MaxInputLength] = {0};
    char num_second_operand[MaxInputLength] = {0};
    addressingMode source_operand;
    addressingMode destination_operand;
    make_copy(num_one_operand, strtok(validLineArray, ","));
    make_copy(num_second_operand, strtok(NULL, ""));
    removeLeftWSpaces(num_second_operand);
    removeRightWSpaces(num_second_operand);
    removeRightWSpaces(num_one_operand);
    /*flag used to mark witch labels should be saved for validation in the fileValidLabels file */
    source_operand = getAddressingMode(num_one_operand, fileValidLabels, TRUE, HeadTagList, originalLine);
    destination_operand = getAddressingMode(num_second_operand, fileValidLabels, TRUE, HeadTagList, originalLine);
    if (source_operand != NON && destination_operand != NON) {
        /*check all the forbidden conjunctions and do negative */
        if ((strcmp(sentence, "lea") != 0) || source_operand == constantIndexAddress ||
            source_operand == directAddress) {
            if (destination_operand != immediateAddress || (strcmp(sentence, "cmp") == 0)) {
                if (source_operand == directRegisterAddress && destination_operand == directRegisterAddress)
                    (*instructionCounter)++;/* increase IC counter for 2 register parameter like r4,r5 */
                if (source_operand == directRegisterAddress && destination_operand != directRegisterAddress)
                    (*instructionCounter)++;
                if (source_operand != directRegisterAddress && destination_operand == directRegisterAddress)
                    (*instructionCounter)++;
                if (source_operand == constantIndexAddress)
                    (*instructionCounter) = (*instructionCounter) + 2;
                if (destination_operand == constantIndexAddress)
                    (*instructionCounter) = (*instructionCounter) + 2;
                if (source_operand == immediateAddress || source_operand == directAddress)
                    (*instructionCounter)++;
                if (destination_operand == immediateAddress)
                    (*instructionCounter)++;
                return TRUE;
            } else
                identifyError("Invalid destination address!", num0fLine);
        } else
            identifyError("Invalid source address!", num0fLine);
        return FALSE;
    }
    if (source_operand == NON)
        identifyError("Invalid definition of firstOperands name!", num0fLine);
    else
        identifyError("Invalid definition of secondOperand name!", num0fLine);
    return FALSE;
}



