#include "McrList.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct nodeMcr {
    char *name;/* name of the node */
    int start;/* start index of the mcr */
    int end; /* length of the mcr */
    McrList next;  /* Next nodeMcr */
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
    if ((*head) == NULL) /* if the list is empty */
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
    if (mcr == NULL || name == NULL)
        return NULL;
    if (strcmp(mcr->name, name) == 0)
        return temp;
    return SearchMcr(mcr->next, name);
}

int HandelMcrName(char *name) {
    int i;
    if (name != NULL && isalpha(name[0]) && strlen(name) <= MAX_MCR_LENGTH) {
        for (i = 0; i < strlen(name); i++) {
            if (!isalnum(name[i]) && name[i] != '_')
                return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

char *getNameM(McrList nodeMcr) {
    return nodeMcr->name;
}

int getStart(McrList nodeMcr) {
    return nodeMcr->start;
}

int getEnd(McrList nodeMcr) {
    return nodeMcr->end;
}

McrList getNext(McrList nodeMcr) {
    return nodeMcr->next;
}

void setStart(McrList nodeMcr, int start) {
    nodeMcr->start = start;
}

void setEnd(McrList nodeMcr, int end) {
    nodeMcr->end = end;
}

void freelistM(McrList head) {
    McrList prev, current = head;
    while (current != NULL) {
        prev = current;
        current = current->next;
        free(prev->name);
        free(prev);
    }
}

