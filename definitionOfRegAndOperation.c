#include "definitionOfRegAndOperation.h"
#include "TagList.h"
#include <string.h>
static const struct registerConsts {
    const char *name;
    int value;
    /*An array representing all valid registers*/
}registers[] = {{"r0", 0},
                {"r1", 1},
                {"r2", 2},
                {"r3", 3},
                {"r4", 4},
                {"r5", 5},
                {"r6", 6},
                {"r7", 7}
};
static const struct operationConsts {
    const char *command;
    int opcode;
    int numOfOperation;
    int startOp;
    int endOp;
/*An array representing all legal operations, their number,
 amount of parameters, source address, destination address, for each method*/
} operation[] = {{"mov", 0,  2, ALL_OPERATION,     WITHOUT_FIRST_OPERATION},
                 {"cmp", 1,  2, ALL_OPERATION,     ALL_OPERATION},
                 {"add", 2,  2, ALL_OPERATION,     WITHOUT_FIRST_OPERATION},
                 {"sub", 3,  2, ALL_OPERATION,     WITHOUT_FIRST_OPERATION},
                 {"not", 4,  1, 0,                 WITHOUT_FIRST_OPERATION},
                 {"clr", 5,  1, 0,                 WITHOUT_FIRST_OPERATION},
                 {"lea", 6,  2, ONE_TWO_OPERATION, WITHOUT_FIRST_OPERATION},
                 {"inc", 7,  1, 0,                 WITHOUT_FIRST_OPERATION},
                 {"dec", 8,  1, 0,                 WITHOUT_FIRST_OPERATION},
                 {"jmp", 9,  1, 0,                 WITHOUT_FIRST_OPERATION},
                 {"bne", 10, 1, 0,                 WITHOUT_FIRST_OPERATION},
                 {"red", 11, 1, 0,                 WITHOUT_FIRST_OPERATION},
                 {"prn", 12, 1, 0,                 ALL_OPERATION},
                 {"jsr", 13, 1, 0,                 WITHOUT_FIRST_OPERATION},
                 {"rts", 14, 0, 0, 0},
                 {"hlt", 15, 0, 0, 0}};


int check_reg_name(char *validName) {
    int i;
    for (i = 0; i <= MAX_NUM_REGISTERS; i++) {
        if (strcmp(validName, registers[i].name) == 0)
            return TRUE;
    }
    return FALSE;
}
int get_reg_number(char *validName) {
    int i;
    for (i = 0; i <= MAX_NUM_REGISTERS; i++) {
        if (strcmp(validName, registers[i].name) == 0)
            return registers[i].value;
    }
    return FALSE;
}
int check_op_name(char *command) {
    int i;
    for (i = 0; i < MAX_OPERATIONS; i++) {
        if (!strcmp(command, operation[i].command))
            return TRUE;
    }
    return FALSE;
}
int get_opcode(char *command)}{
    int i;
    for (i = 0; i < MAX_OPERATIONS; i++) {
        if (!strcmp(command, operation[i].command))
            return operation[i].opcode;
    }
    return NON;
}

int get_num_of_operation(char *command) {
    int i;
}