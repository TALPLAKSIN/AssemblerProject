#include "McrList.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
struct nodeMcr{
    char *name;/* name of the node */
    int start;/* start index of the macro */
    int end; /* length of the macro */
    McrList next;  /* Next link */
};
McrList NewMcr(char *name, int start) {
    McrList new_mcr = (McrList) calloc(1, sizeof(struct nodeMcr));
    new_mcr->name = (char *) calloc(1, (strlen(name) + 1) * sizeof(char));
    strcpy(new_mcr->name, name);
    new_mcr->start = start;
    new_mcr->end = 0;
    new_mcr->next = NULL;
    return new_mcr;
}
