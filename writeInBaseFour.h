#ifndef WRITEINBASEFOUR_H
#define WRITEINBASEFOUR_H

#include "ValidFile.h"

/*
    This function convert 2 bits to a base 4 character based on the values of number1, number2, and flag,
    following different conditions for each case
    parameters:
                @param number1 - the right bit
                @param number2 - the left bit
                @param File -  a pointer to the file to write in it
                @param mark - indicates whether received 2 bits or a number that represents 2 bits
    return:
                @return non

*/
void writeTwoBitToFile(int number1, int number2, FILE *File, int mark);

/*
    This function receives a parameter and rewrites it in base 4

    parameters:
                @param argument -the argument to be change
                @param mark - Indicates whether the parameter is of type string or number
                @param data_file -  a pointer to data file
                @param dataCounter - a pointer to DC counter
    return:
                @return non

*/
void convertToBaseFour(char *argument, int mark, FILE *data_file, int *dataCounter);

/*
    This function receives an operand and rewrites it in base 4

    parameters:
                @param num -the number to be change
                @param BIT_A_R_E - indicate the type - Absolute,External,Relocatable
                @param instructions_file -  a pointer to the instructions file
                @param instructionCounter - a pointer to the IC counter
    return:
                @return non

*/
void convertOperandToBaseFour(int num, int BIT_A_R_E, FILE *instructions_file, int *instructionCounter);

/*
    This function receives a parameter and converts it's number to a base 4 and writes it to a file

    parameters:
                @param operation_code -the opcode of the parameter
                @param instructions_file -  a pointer to the instructions file
    return:
                @return non

*/
void convertOpcodeToBaseFour(int operation_code, FILE *instructions_file);

/*
    This function convert the first word in the line to base 4

    parameters:
                @param BIT_A_R_E - indicate the type - Absolute,External,Relocatable
                @param destination_operand - destination operand address
                @param source_operand - source operand address
                @param operation_code -  argument's operations
                @param instructions_file -  a pointer to the instructions file
                @param instructionCounter - a pointer to the IC counter
    return:
                @return non

*/
void
convertFirstWordToBaseFour(int operation_code, int source_operand, int destination_operand, int BIT_A_R_E,
                           FILE *instructions_file,
                           int *instructionCounter);


#endif





