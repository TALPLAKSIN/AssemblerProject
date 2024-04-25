#include "convertAddress.h"

void dealWithAddress(addressingMode operand_mode, TagList *HeadTagList, char *parameter, int *instructionCounter,FILE *instructions_file, FILE *extern_file, int num1_Or_num2) {
    *instructionCounter = *instructionCounter + 1;/*Adds one to the instruction counter*/
    /*encoding the extra lines according to the appropriate method*/
    if (operand_mode == constantIndexAddress)
        convertConstIndexToBase4(parameter, instructionCounter, instructions_file, HeadTagList, extern_file);
    else if (operand_mode == immediateAddress)
        convertImmediateToBase4(parameter, instructionCounter, instructions_file);
    else if (operand_mode == directAddress)
        convertDirectToBase4(HeadTagList, parameter, instructionCounter, instructions_file, extern_file);
    else {
        if (num1_Or_num2)/*encoding the register number on the file*/
            convertOperandToBaseFour((get_reg_number(parameter) << 3), 0, instructions_file, instructionCounter);
        else
            convertOperandToBaseFour((get_reg_number(parameter)), 0, instructions_file, instructionCounter);
    }
}


void convertSentenceToBase4(TagList *HeadTagList, char *sentence, int *instructionCounter, FILE *instructions_file,FILE *extern_file) {
    int opNumber=0;
    opNumber = get_num_of_operation(sentence);
    if (opNumber == 0)/*A command with no operands at all*/
        convertFirstWordToBaseFour(get_opcode(sentence), 0, 0, 0, instructions_file, instructionCounter);
    if (opNumber == 1)/*A command with one operand*/
        convertOneOperand(HeadTagList, sentence, instructionCounter, instructions_file, extern_file);
    if (opNumber == 2)/*A command with two operands*/
        convertTwoOperand(HeadTagList, sentence, instructionCounter, instructions_file, extern_file);
}

void convertOneOperand(TagList *HeadTagList, char *sentence, int *instructionCounter, FILE *instructions_file,
                       FILE *extern_file) {
    int opcode = 0;/*Represents the amount of operands of the command*/
    addressingMode destination_operand = NOT_OCCUR;/*Represents the destination address of the command*/
    char *num_second_operand = NULL;
    opcode = get_opcode(sentence);
    num_second_operand = strtok(NULL, " \t\n\v\f\r,");/*save the second operand*/
    destination_operand = getAddressingMode(num_second_operand, NULL, FALSE, 0, NULL);
    /*encoding the first word*/
    convertFirstWordToBaseFour(opcode, 0, destination_operand, 0, instructions_file, instructionCounter);
    /*encoding the extra line*/
    dealWithAddress(destination_operand, HeadTagList, num_second_operand, instructionCounter, instructions_file,
                    extern_file, FALSE);
}

void convertTwoOperand(TagList *HeadTagList, char *sentence, int *instructionCounter, FILE *instructions_file,
                       FILE *extern_file) {
    int opcode = 0;/*Represents the amount of operands of the command*/
    addressingMode source_operand = NOT_OCCUR;/*Represents the source address of the command*/
    addressingMode destination_operand = NOT_OCCUR;/*Represents the destination address of the command*/
    char num_one_operand[MaxInputLength] = {0};
    char num_second_operand[MaxInputLength] = {0};
    char *temp = NULL;
    char *temp2 = NULL;
    opcode = get_opcode(sentence);
    temp = strtok(NULL, " \t\n\v\f\r,");/*save the first operand*/
    temp2 = strtok(NULL, " ");/*save the second operand*/
    make_copy(num_one_operand, temp);/*save the real one operand without changing it*/
    make_copy(num_second_operand, temp2);/*save the real second operand without changing it*/
    /*Deletes white characters from both ends of the string*/
    removeLeftWSpaces(num_one_operand);
    removeRightWSpaces(num_one_operand);
    /*Deletes white characters from both ends of the string*/
    removeLeftWSpaces(num_second_operand);
    removeRightWSpaces(num_second_operand);
    /*Mark's value appear as true or false corresponding to the need to write the label in the file for further tests*/
    source_operand = getAddressingMode(num_one_operand, NULL, FALSE, 0, NULL);
    destination_operand = getAddressingMode(num_second_operand, NULL, FALSE, 0, NULL);
    /*encoding the first word*/
    convertFirstWordToBaseFour(opcode, source_operand, destination_operand, 0, instructions_file, instructionCounter);
    /*encoding the extra line*/
    if (destination_operand == directRegisterAddress && source_operand == directRegisterAddress) {
        *instructionCounter = *instructionCounter + 1; /*encoding them as a one line*/
        convertOperandToBaseFour((get_reg_number(num_one_operand) << 3) | (get_reg_number(num_second_operand)), 0,
                                 instructions_file, instructionCounter);
    } else { /*encoding the extra line*/
        dealWithAddress(source_operand, HeadTagList, num_one_operand, instructionCounter, instructions_file,
                        extern_file, TRUE);
        dealWithAddress(destination_operand, HeadTagList, num_second_operand, instructionCounter, instructions_file,
                        extern_file, FALSE);
    }
}

void convertImmediateToBase4(char *parameter, int *instructionCounter, FILE *instructions_file) {
    char *temp=NULL;
    char num_one_operand[MaxInputLength] = {0};
    int parameter_to_int=0;
    /*Conversion corresponds to base 4 according to the current addressing method*/
    make_copy(num_one_operand, parameter);
    parameter = strtok(num_one_operand, "#");
    parameter_to_int = strtol(parameter, &temp, 10);
    convertOperandToBaseFour(parameter_to_int, 0, instructions_file, instructionCounter);
}

void convertConstIndexToBase4(char *parameter, int *instructionCounter, FILE *instructions_file, TagList *HeadTagList,
                              FILE *extern_file) {
    char validLineArray[MaxInputLength] = {0};
    char *end=NULL;
    char *temp=NULL;
    int parameter_to_int = 0;
    /*Conversion corresponds to base 4 according to the current addressing method*/
    make_copy(validLineArray, parameter);
    parameter = strtok(validLineArray, "[");
    end = strtok(NULL, "[] ");
    parameter_to_int = strtol(end, &temp, 10);
    convertDirectToBase4(HeadTagList, parameter, instructionCounter, instructions_file, extern_file);
    *instructionCounter = *instructionCounter + 1;/*Adds one to the instruction counter*/
    convertOperandToBaseFour((int) parameter_to_int, 0, instructions_file, instructionCounter);
}

void convertDirectToBase4(TagList *HeadTagList, char *parameter, int *instructionCounter, FILE *instructions_file,
                          FILE *extern_file) {
    int BIT_A_R_E = 2;
    TagList temp = NULL;
    temp = SearchTag(*HeadTagList, parameter);/* find the tag a like the label*/
    if (getType(temp) == EXTERNAL) { /*EXTERNAL - write to the extern_file*/
        fprintf(extern_file, "%s\t", getName(temp));
        if (*instructionCounter < 1000)
            fprintf(extern_file, "0");
        fprintf(extern_file, "%d\n", *instructionCounter);
        BIT_A_R_E = 1;
    }/*Conversion corresponds to base 4 according to the current addressing method*/
    convertOperandToBaseFour(getAddress(temp), BIT_A_R_E, instructions_file, instructionCounter);
}


