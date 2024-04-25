#include "writeInBaseFour.h"

void writeTwoBitToFile(int number1, int number2, FILE *File, int mark) {
    if (mark) {/*Getting 2 digits in binary base and writing the corresponding character in base 4*/
        if (number1 == 1 && number2 == 1)
            fputc('!', File);
        else if (number1 == 0 && number2 == 1)
            fputc('%', File);
        else if (number1 == 1 && number2 == 0)
            fputc('#', File);
        else
            fputc('*', File);
    } else {/*Getting a digit in decimal base and writing the corresponding character in base 4*/
        if (number1 == 3)
            fputc('!', File);
        else if (number1 == 2)
            fputc('%', File);
        else if (number1 == 1)
            fputc('#', File);
        else
            fputc('*', File);
    }
}

void convertToBaseFour(char *argument, int mark, FILE *data_file, int *dataCounter) {
    int i=0;
    int number=0;
    int num1=0;
    int num2=0;
    char *temp=NULL;
    *dataCounter = *dataCounter + 1;/*Adds one to the data counter*/
    if (*dataCounter < 1000)
        fprintf(data_file, "0");/*complete '0' to the file if necessary*/
    fprintf(data_file, "%d\t", *dataCounter);/*write the current data counter on the file*/
    if (!mark)
        number = strtol(argument, &temp, 10);/*convert the string to number in base 10*/
    else
        number = (int) (*argument);/*the ascii value of the received char*/
    for (i = 6; i >= 0; i--) {/*write to the file*/
        num1 = (number & (1 << (i * 2))) == 0 ? 0 : 1;
        num2 = (number & (1 << (i * 2 + 1))) == 0 ? 0 : 1;
        writeTwoBitToFile(num1, num2, data_file, 1);
    }
    fprintf(data_file, "\n");
}

void convertOperandToBaseFour(int num, int BIT_A_R_E, FILE *instructions_file, int *instructionCounter) {
    int i=0;
    int num1=0;
    int num2=0;
    if (*instructionCounter < 1000)
        fprintf(instructions_file, "0");/*complete '0' to the file if necessary*/
    fprintf(instructions_file, "%d\t", *instructionCounter);/*write the current instruction counter on the file*/
    for (i = 5; i >= 0; i--) {/*write to the file*/
        num1 = (num & (1 << (i * 2))) == 0 ? 0 : 1;
        num2 = (num & (1 << (i * 2 + 1))) == 0 ? 0 : 1;
        writeTwoBitToFile(num1, num2, instructions_file, 1);
    }
    writeTwoBitToFile(BIT_A_R_E, BIT_A_R_E, instructions_file, 0); /*encoding ARE*/
    fprintf(instructions_file, "\n");
}

void convertOpcodeToBaseFour(int operation_code, FILE *instructions_file) {
    int num1=0;
    int num2=0;
    /*write opcode to the file*/
    num1 = (operation_code & (1 << 2)) == 0 ? 0 : 1;
    num2 = (operation_code & (1 << 3)) == 0 ? 0 : 1;
    writeTwoBitToFile(num1, num2, instructions_file, 1);
    num1 = (operation_code & (1 << 0)) == 0 ? 0 : 1;
    num2 = (operation_code & (1 << 1)) == 0 ? 0 : 1;
    writeTwoBitToFile(num1, num2, instructions_file, 1);
}

void convertFirstWordToBaseFour(int operation_code, int source_operand, int destination_operand, int BIT_A_R_E,
                                FILE *instructions_file, int *instructionCounter) {
    *instructionCounter = *instructionCounter + 1;
    if (*instructionCounter < 1000)
        fprintf(instructions_file, "0");/*complete '0' to the file if necessary*/
    fprintf(instructions_file, "%d\t**", *instructionCounter);/*write the current instruction counter on the file*/
    /*write to the file*/
    convertOpcodeToBaseFour(operation_code, instructions_file);/* encoding 4 bit that represent opcode on the file */
    writeTwoBitToFile(source_operand, source_operand, instructions_file,
                      0);/*write source address to the file*/
    writeTwoBitToFile(destination_operand, destination_operand, instructions_file,
                      0);/*write destination address to the file*/
    writeTwoBitToFile(BIT_A_R_E, BIT_A_R_E, instructions_file, 0);/*write ARE to the file*/
    fprintf(instructions_file, "\n");
}

