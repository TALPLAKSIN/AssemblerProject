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
};