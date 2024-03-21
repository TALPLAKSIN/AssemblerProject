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
}operation[] = {{"mov", 0,  2, ALL_OPERATION,     WITHOUT_FIRST_OPERATION},
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



