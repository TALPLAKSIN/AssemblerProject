#include "McrList.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct nodeMcr {
    char *name;/* A pointer to a character string for the name */
    int start;/* An integer to store the start value */
    int end; /* An integer to store the end value */
    McrList next;   /* A pointer to the next node of type McrList */
};


McrList NewMcr(char *name, int start) {
    McrList new_mcr = (McrList) calloc(1, sizeof(struct nodeMcr));/* Allocate memory for the new macro */
    new_mcr->name = (char *) calloc(1, (strlen(name) + 1) * sizeof(char)); /* Allocate memory for the name of the macro */
    strcpy(new_mcr->name, name);/* Copy the name into the new macro's name field */
    new_mcr->start = start;/* Set the starting index of the macro */
    new_mcr->end = 0;/* Initialize the length of the macro to 0 */
    new_mcr->next = NULL;/* Set the next pointer of the new macro to NULL */
    return new_mcr;
}

void InsertMcrToList(McrList *head, McrList new_mcr) {
    if ((*head) == NULL)
        /* If the list is empty, set the head to the new mcr */
        *head = new_mcr;
    else {
        /* If the list is not empty, insert the new mcr at the beginning of the list */
        new_mcr->next = (*head);/*Set the next pointer of the new mcr to the current head */
        /* Update the head to point to the new mcr */
        (*head) = new_mcr;
    }
}

McrList SearchMcr(McrList mcr, char *name) {
    McrList temp=NULL;
    temp = mcr;/* Initialize temp to the start of the list */
    if (mcr == NULL || name == NULL)/* Check for NULL pointers */
        return NULL;
    if (strcmp(mcr->name, name) == 0) /* Check if the current mcr name matches the name */
        return temp;/* Return the current mcr if found */
    return SearchMcr(mcr->next, name);/* Recursively search the next mcr in the list */
}

int HandelMcrName(char *name) {
    int i=0;
    /* Check if name is not NULL, starts with an alphabet, and within the maximum length */
    if (name != NULL && isalpha(name[0]) && strlen(name) <= MAX_MCR_LENGTH) {
        /* Iterate through each character in the name */
        for (i = 0; i < strlen(name); i++) {
            /* Check if the character is alphanumeric or an underscore */
            if (!isalnum(name[i]) && name[i] != '_')
                return FALSE;
        }
        return TRUE;/* Return TRUE if all characters are valid */
    }
    return FALSE;
}
/*Receiving name of MCR*/
char *getNameM(McrList nodeMcr) {
    return nodeMcr->name;
}
/*Receiving start of MCR*/
int getStart(McrList nodeMcr) {
    return nodeMcr->start;
}
/*Receiving end of MCR*/
int getEnd(McrList nodeMcr) {
    return nodeMcr->end;
}
/*Receiving next of MCR*/
McrList getNext(McrList nodeMcr) {
    return nodeMcr->next;
}
/*Changing start of MCR*/
void setStart(McrList nodeMcr, int start) {
    nodeMcr->start = start;
}
/*Changing end of MCR*/
void setEnd(McrList nodeMcr, int end) {
    nodeMcr->end = end;
}

void freelistM(McrList head) {
    McrList prev=NULL;/* Initialize pointers*/
    McrList current = head;
    while (current != NULL) {
        prev = current;/* Store the current node */
        current = current->next; /* Move to the next node */
        free(prev->name);/* Free the memory allocated for the name */
        free(prev);/* Free the memory allocated for the node */
    }
}

