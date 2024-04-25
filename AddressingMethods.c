#include "AddressingMethods.h"

int instructionValidName(char *name) {
    int i = 0;
    /*Goes through all the command names and checks if it matches one of them*/
    for (; i < MAX_NUM_INSTRUCTION; i++) {
        if (strcmp(name, instructionNames[i].name) == 0)
            return TRUE;
    }
    return FALSE;
}

int validateCommand(char *sentence, int *instructionCounter, FILE *fileValidLabels, int num0fLine, TagList *HeadTagList,
                    char originalLine[]) {
    int opNumber = 0;/*Represents the amount of operands of the command*/
    int mark = 0;
    char validLineArray[MaxInputLength] = {0};
    opNumber = get_num_of_operation(sentence);
    (*instructionCounter)++;/*Adds one to the instruction counter*/
    if (opNumber == 0) {/*A command with no operands at all*/
        if (!make_copy(validLineArray, strtok(NULL, " \t\n\v\f\r")))/*save the real one without changing it*/
            return TRUE;
        identifyError("This command has no operands at all, therefore any additional character is forbidden",
                      num0fLine);
        return FALSE;
    }/*save the real one without changing it*/
    mark = make_copy(validLineArray, strtok(NULL, ""));
    if (mark && validLineArray[0] != ',') {
        /*Deletes white characters from both ends of the string*/
        removeLeftWSpaces(validLineArray);
        removeRightWSpaces(validLineArray);
        if (opNumber == 1) /*A command with one operand*/
            return validDestOneOp(sentence, instructionCounter, fileValidLabels, num0fLine, validLineArray, HeadTagList,
                                  originalLine);
        else /*A command with two operands*/
            return validDestSourceTwoOp(sentence, instructionCounter, fileValidLabels, num0fLine, validLineArray,
                                        HeadTagList, originalLine);
    }
    if (!mark) /*When an operand is missing*/
        identifyError("Operand is missing", num0fLine);
    else  /*Error - start with a comma*/
        identifyError("The command line must not start with a comma", num0fLine);
    return FALSE;
}


addressingMode
getAddressingMode(char *operand, FILE *fileValidLabels, int mark, TagList *HeadTagList, char originalLine[]) {
    int i = 0;
    char *tag=NULL;
    char num_one_operand[MaxInputLength] = {0};
    char temp_operand[MaxInputLength] = {0};
    if (operand != NULL && operand[i] != '\0') {/*Checking whether isn't null*/
        if (check_reg_name(operand))/*Checking whether an operand is a register*/
            return directRegisterAddress;
        if (HandelTagName(operand)) {/*Checking whether is legal tag*/
            /*Save all the labels by writing them to the appropriate file and at
             * the end of the testing phase as one of the last tests we will go
             * through the file and make sure that they have all been defined as required*/
            if (mark)
                fprintf(fileValidLabels, "%s\n", operand);
            return directAddress;
        }
        /*Checking whether is a number or a number and a character '#' before it --> is a immediateAddress*/
        if (operand[i] == '#' && strlen(operand) > 1 && operand[i + 1] != '#') {
            operand = strtok(operand, "#"); /*Checking if it is a DEFINE and setting it to its value*/
            if (checkValidNumber(operand, FALSE) ||
                (HeadTagList != NULL && checkAndReplaceDefine(HeadTagList, operand, originalLine)))
                return immediateAddress;
            else
                return NOT_OCCUR;
        }
        /*save the real operand without changing it*/
        make_copy(temp_operand, operand);
        make_copy(num_one_operand, operand);
        /*if an address begins with '[]' and inside has a valid number --> constantIndexAddress*/
        tag = strtok(temp_operand, "[");/*remove the first char '['*/
        if (operand[strlen(operand)- 1] == ']') {/*Checking if the last char is ']'*/
            if (HandelTagName(tag)) {/*Checking whether is legal tag*/
                /*Save all the labels by writing them to the appropriate file and at
                 * the end of the testing phase as one of the last tests we will go
                 * through the file and make sure that they have all been defined as required*/
                if (mark)
                    fprintf(fileValidLabels, "%s\n", tag);
                make_cut(num_one_operand);
                /*Deletes white characters from both ends of the operand*/
                removeLeftWSpaces(num_one_operand);
                removeRightWSpaces(num_one_operand);
                if (checkValidNumber(num_one_operand, FALSE))/*Checking whether is a number --> is a immediateAddress*/
                    return constantIndexAddress;
                /*Checking if it is a DEFINE and setting it to its value*/
                if (HeadTagList != NULL && checkAndReplaceDefine(HeadTagList, num_one_operand, originalLine))
                    return constantIndexAddress;
            }
        }
    }
    return NOT_OCCUR; /*Return NON when there is no legal address method*/
}

int validDestOneOp(char *sentence, int *instructionCounter, FILE *fileValidLabels, int num0fLine, char validLineArray[],
                   TagList *HeadTagList, char originalLine[]) {
    /*Receiving a value representing the addressing method of the destination operand*/
    addressingMode destination_operand = getAddressingMode(validLineArray, fileValidLabels, TRUE, HeadTagList,
                                                           originalLine);
    (*instructionCounter)++;/*Adds one to the instruction counter*/
    /*All instructions can have their destination address method be directRegisterAddress or directAddress*/
    if (destination_operand == directAddress || destination_operand == directRegisterAddress)
        return TRUE;
    /*only prn can have destination address method be immediateAddress*/
    if ((strcmp(sentence, "prn") == 0) && (destination_operand == immediateAddress))
        return TRUE;
    (*instructionCounter)++;
    /*Checking a constantIndexAddress according to its restrictions*/
    if (destination_operand == constantIndexAddress &&
        ((strcmp(sentence, "dec") == 0) || (strcmp(sentence, "red") == 0) || (strcmp(sentence, "prn") == 0) ||
         (strcmp(sentence, "not") == 0) || (strcmp(sentence, "clr") == 0) || (strcmp(sentence, "inc") == 0)))
        return TRUE;
    (*instructionCounter) -= 2;/*Lowering two from the command counter if it is not a known addressing method*/
    if (destination_operand == NOT_OCCUR)/*Error in operand*/
        identifyError("Invalid definition of a Operand!", num0fLine);
    else/*Error in destination*/
        identifyError("Invalid destination address!", num0fLine);
    return FALSE;
}


int validDestSourceTwoOp(char *sentence, int *instructionCounter, FILE *fileValidLabels, int num0fLine,
                         char validLineArray[], TagList *HeadTagList, char originalLine[]) {
    char num_one_operand[MaxInputLength] = {0};
    char num_second_operand[MaxInputLength] = {0};
    addressingMode source_operand = NOT_OCCUR;
    addressingMode destination_operand = NOT_OCCUR;
    /*save the real first operand without changing it*/
    make_copy(num_one_operand, strtok(validLineArray, ","));
    /*save the real second operand without changing it*/
    make_copy(num_second_operand, strtok(NULL, ""));
    /*Deletes white characters from both ends of the string*/
    removeLeftWSpaces(num_second_operand);
    removeRightWSpaces(num_second_operand);
    /*Deletes white characters from end of the string*/
    removeRightWSpaces(num_one_operand);
    /*Mark's value appear as true or false corresponding to the need to write the label in the file for further tests*/
    source_operand = getAddressingMode(num_one_operand, fileValidLabels, TRUE, HeadTagList, originalLine);
    destination_operand = getAddressingMode(num_second_operand, fileValidLabels, TRUE, HeadTagList, originalLine);

    if (source_operand != NOT_OCCUR &&
        destination_operand != NOT_OCCUR) {/*Checking that both addressing methods are legal*/
        /*Checking all the legal combinations of the two addressing methods and promoting the instruction counter accordingly*/
        if ((strcmp(sentence, "lea") != 0) || source_operand == constantIndexAddress ||
            source_operand == directAddress) {
            if (destination_operand != immediateAddress || (strcmp(sentence, "cmp") == 0)) {
                if (source_operand == directRegisterAddress && destination_operand == directRegisterAddress)
                    (*instructionCounter)++;/*Adds one to the instruction counter*/
                if (source_operand == directRegisterAddress && destination_operand != directRegisterAddress)
                    (*instructionCounter)++;/*Adds one to the instruction counter*/
                if (source_operand != directRegisterAddress && destination_operand == directRegisterAddress)
                    (*instructionCounter)++;/*Adds one to the instruction counter*/
                if (source_operand == constantIndexAddress)
                    (*instructionCounter) = (*instructionCounter) + 2;/*Adds tow to the instruction counter*/
                if (destination_operand == constantIndexAddress)
                    (*instructionCounter) = (*instructionCounter) + 2;/*Adds tow to the instruction counter*/
                if (source_operand == immediateAddress || source_operand == directAddress)
                    (*instructionCounter)++;/*Adds one to the instruction counter*/
                if (destination_operand == immediateAddress)
                    (*instructionCounter)++;/*Adds one to the instruction counter*/
                return TRUE;
            } else/*Error in destination*/
                identifyError("Invalid destination address!", num0fLine);
        } else/*Error in source*/
            identifyError("Invalid source address!", num0fLine);
        return FALSE;
    }
    if (source_operand == NOT_OCCUR)/*Error in firstOperands*/
        identifyError("Invalid definition of firstOperands name!", num0fLine);
    else/*Error in secondOperand*/
        identifyError("Invalid definition of secondOperand name!", num0fLine);
    return FALSE;
}



