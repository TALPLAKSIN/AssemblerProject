#include "definitionOfRegAndOperation.h"
#include "TagList.h"
#include <string.h>

/*Defining and creating all the legal registers in one array and putting a value directly*/
static const struct regConsts {
    const char *name;
    int num;
} reg[] = {{"r0", 0},
           {"r1", 1},
           {"r2", 2},
           {"r3", 3},
           {"r4", 4},
           {"r5", 5},
           {"r6", 6},
           {"r7", 7}
};
/*Defining and creating all the legal commands in
 * one array that includes all the relevant features
 * such as: name, number, number of operands,
 * legal addressing method for the source operand and
 * legal addressing method for the target operand
 * and putting legal values directly*/
static const struct operationConsts {
    const char *sentence;
    int opcode;
    int amount_operation;
    int start_opcode;
    int end_opcode;
} the_operations[] = {{"mov", 0,  2, ALL_OPERATION,     WITHOUT_FIRST_OPERATION},
                      {"cmp", 1,  2, ALL_OPERATION,     ALL_OPERATION},
                      {"add", 2,  2, ALL_OPERATION,     WITHOUT_FIRST_OPERATION},
                      {"sub", 3,  2, ALL_OPERATION,     WITHOUT_FIRST_OPERATION},
                      {"not", 4,  1, 0,                 WITHOUT_FIRST_OPERATION},
                      {"clr", 5,  1, 0,                 WITHOUT_FIRST_OPERATION},
                      {"lea", 6,  2, ONE_TWO_OPERATION, WITHOUT_FIRST_OPERATION},
                      {"inc", 7,  1, 0,                 WITHOUT_FIRST_OPERATION},
                      {"dec", 8,  1, 0,                 WITHOUT_FIRST_OPERATION},
                      {"jmp", 9,  1, 0,                 ONE_THREE_OPERATION},
                      {"bne", 10, 1, 0,                 ONE_THREE_OPERATION},
                      {"red", 11, 1, 0,                 WITHOUT_FIRST_OPERATION},
                      {"prn", 12, 1, 0,                 ALL_OPERATION},
                      {"jsr", 13, 1, 0,                 ONE_THREE_OPERATION},
                      {"rts", 14, 0, 0, 0},
                      {"hlt", 15, 0, 0, 0}};

/*Checking for a valid name for a register*/
int check_reg_name(char *word) {
    int i=0;
    for (i = 0; i <= MAX_NUM_REGISTERS; i++) {
        if (strcmp(word, reg[i].name) == 0)
            return TRUE;
    }
    return FALSE;
}
/*Checking for a valid value for a register*/
int get_reg_number(char *word) {
    int i=0;
    for (i = 0; i <= MAX_NUM_REGISTERS; i++) {
        if (strcmp(word, reg[i].name) == 0)
            return reg[i].num;
    }
    return FALSE;
}
/*Checking for a valid name for a operation*/
int check_op_name(char *word) {
    int i=0;
    for (i = 0; i < MAX_OPERATIONS; i++) {
        if (!strcmp(word, the_operations[i].sentence))
            return TRUE;
    }
    return FALSE;
}
/*Receiving an opcode of a command*/
int get_opcode(char *word) {
    int i=0;
    for (i = 0; i < MAX_OPERATIONS; i++) {
        if (!strcmp(word, the_operations[i].sentence))
            return the_operations[i].opcode;
    }
    return NOT_OCCUR;
}
/*Receiving a num of operation of a command*/
int get_num_of_operation(char *word) {
    int i=0;
    for (i = 0; i < MAX_OPERATIONS; i++) {
        if (strcmp(word, the_operations[i].sentence) == 0)
            return the_operations[i].amount_operation;
    }
    return NOT_OCCUR;
}
