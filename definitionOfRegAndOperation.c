#include "definitionOfRegAndOperation.h"
#include "TagList.h"
#include <string.h>

static const struct regConsts {
    const char *name;
    int num;
/*all valid registers*/
} reg[] = {{"r0", 0},
           {"r1", 1},
           {"r2", 2},
           {"r3", 3},
           {"r4", 4},
           {"r5", 5},
           {"r6", 6},
           {"r7", 7}
};
/* Each operation is defined with its number, opcode, number of operands, and source, destination address*/
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


int check_reg_name(char *word) {
    int i;
    for (i = 0; i <= MAX_NUM_REGISTERS; i++) {
        if (strcmp(word, reg[i].name) == 0)
            return TRUE;
    }
    return FALSE;
}

int get_reg_number(char *word) {
    int i;
    for (i = 0; i <= MAX_NUM_REGISTERS; i++) {
        if (strcmp(word, reg[i].name) == 0)
            return reg[i].num;
    }
    return FALSE;
}

int check_op_name(char *word) {
    int i;
    for (i = 0; i < MAX_OPERATIONS; i++) {
        if (!strcmp(word, the_operations[i].sentence))
            return TRUE;
    }
    return FALSE;
}

int get_opcode(char *word) {
    int i;
    for (i = 0; i < MAX_OPERATIONS; i++) {
        if (!strcmp(word, the_operations[i].sentence))
            return the_operations[i].opcode;
    }
    return NON;
}

int get_num_of_operation(char *word) {
    int i;
    for (i = 0; i < MAX_OPERATIONS; i++) {
        if (strcmp(word, the_operations[i].sentence) == 0)
            return the_operations[i].amount_operation;
    }
    return NON;
}
