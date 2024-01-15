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
void InsertMcrToList(McrList *head, McrList new_mcr) {
    if ((*head)==NULL) /* if the list is empty */
        *head = new_mcr;
    else {
        /*Make next of new node as head*/
        new_mcr->next = (*head);
        /*move the head to point to the new node*/
        (*head) = new_mcr;
    }
}

McrList SearchMcr(McrList mcr, char *name) {
    McrList temp;
    temp = mcr;
    if(mcr == NULL || name == NULL)
        return NULL;
    if(strcmp(mcr->name, name) == 0)
        return temp;
    return SearchMcr(mcr->next, name);
}

int HandelMcrName(char *name) {
    int i;
    if (name != NULL && isalpha(name[0]) && strlen(name) <= MAX_LABEL_LENGTH) {
        for (i = 0; i < strlen(name); i++) {
            if (!isalnum(name[i]) && name[i]!='_')
                return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}