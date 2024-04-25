#include "TagList.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct nodeTag {
    char *name;/* name of the node */
    int used;/* Flag to indicate if the tag is used */
    int valueOrSize;/* for define represent value, for data represent size array*/
    int address; /* Address associated with the tag */
    Type type;/* Type of the tag */
    TagList next;   /* Pointer to the next nodeTag in the list */
};


TagList NewTag(char *name, int address) {
    TagList new_tag = (TagList) calloc(1, sizeof(struct nodeTag));
    new_tag->name = (char *) calloc(1, (strlen(name) + 1) * sizeof(char));
    strcpy(new_tag->name, name);
    new_tag->used = 0;/* Initially not used */
    new_tag->valueOrSize = 0;/* Default value/size */
    new_tag->address = address;/* Set the address */
    new_tag->next = NULL; /* Initialize next pointer to NULL */
    new_tag->type = CODE;/* Default type is CODE */
    return new_tag;
}

void InsertTagToList(TagList *head, TagList new_tag) {
    /* If the list is empty, set the head to the new tag */
    if ((*head) == NULL)
        *head = new_tag;
    else {
        /* If the list is not empty, insert the new tag at the beginning of the list */
        new_tag->next = (*head);
        /* Update the head to point to the new tag */
        (*head) = new_tag;
    }
}

TagList SearchTag(TagList tag, char *name) {
    TagList temp=NULL;
    temp = tag;/* Initialize temp to the start of the list */
    if (tag == NULL || name == NULL)
        return NULL;
    if (strcmp(tag->name, name) == 0)/* Check if the current tag name matches the name */
        return temp;/* Return the current tag if found */
    return SearchTag(tag->next, name);/* Recursively search the next tag in the list */
}


void allUsed(TagList tag, int phase) {
    int flag = TRUE;
    while (tag != NULL) {
        if (tag->used != OCCUR) {/* Check if tag is not marked as used */
            if (flag) {/* If no warnings have been printed yet */
                if (phase == 0) { /* Phase 0 is for mcr */
                    printf("Warning occurred at the process, macros we didn't use: '%s'", tag->name);
                    flag = FALSE;/* Set flag to indicate warning printed */
                } else {/*message belonging to the phase one*/
                    if (!(strcmp(tag->name, "MAIN") == 0) && tag->type != MDEFINE) {
                        printf("Warning occurred at the process, tag we didn't use: '%s'", tag->name);
                        flag = FALSE;/* Set flag to indicate warning printed */
                    }
                }
            } else if (!(strcmp(tag->name, "MAIN") == 0) && tag->type != MDEFINE)
                printf(",'%s'", tag->name);/* Print additional unused tags */
        }
        tag = tag->next;/* Move to the next tag */
    }
    if (!flag)
        printf("\n"); /* Print newline if warnings were printed */
}

/*Removing the head of the list from the TagList and promoting tje head one step forward*/
void moveHead(TagList *head) {
    TagList temp = *head;
    *head = (*head)->next;
    freeLinked(temp);
}
/*Receiving name of tag*/
char *getName(TagList tag) {
    return tag->name;
}

/*Receiving address of tag*/
int getAddress(TagList tag) {
    return tag->address;
}
/*Receiving valueOrSize of tag*/
int getValueOrSize(TagList tag) {
    return tag->valueOrSize;
}
/*Receiving type of tag*/
Type getType(TagList tag) {
    return tag->type;
}
/*Receiving next of tag*/
TagList getNextTag(TagList tag) {
    return tag->next;
}
/*Changing used of tag*/
void setUsed(TagList tag, int used) {
    tag->used = used;
}
/*Changing valueOrSize of tag*/
void setValueOrSize(TagList tag, int valueOrSize) {
    tag->valueOrSize = valueOrSize;
}
/*Changing address of tag*/
void setAddress(TagList tag, int address) {
    tag->address = address;
}
/*Changing Type of tag*/
void setType(TagList tag, Type type) {
    tag->type = type;
}

void freeLinked(TagList tag) {
    free(tag->name);
    free(tag);
}

void freelist(TagList head) {
    TagList prev=NULL;/* Pointer to the previous node */
    TagList current = head;/* Pointer to the current node */
    while (current != NULL) {/* Loop until the end of the list */
        prev = current;; /* Save the current node */
        current = current->next;/* Move to the next node */
        freeLinked(prev);/* Free the memory allocated for the current node */
    }
}

void print1(TagList tag) {
    unsigned long i=0;
    while (tag != NULL) {
        printf("%s", tag->name);
        for (i = strlen(tag->name); i < 15; i++)
            printf(" ");
        if (tag->type == MDEFINE)
            printf("MDEFINE   \t");
        if (tag->type == CODE)
            printf("CODE      \t");
        if (tag->type == DATA)
            printf("DATA      \t");
        if (tag->type == ENTRY)
            printf("ENTRY     \t");
        if (tag->type == EXTERNAL)
            printf("EXTERNAL  \t");
        if (tag->type == MDEFINE)
            printf("%d\n", tag->valueOrSize);
        else
            printf("%d\n", tag->address);
        tag = tag->next;/* move to check the next node*/
    }
}

void changeICTags(TagList *tag, int instructionCounter) {
    TagList temp = *tag;/* Temporary pointer to the tag list */
    while (temp != NULL) {/* Loop through the tag list */
        if (temp->type == DATA)/* Check if it's a data instruction */
            temp->address += instructionCounter;/* Update the address by adding the instruction counter */
        temp = temp->next;/* Move to the next node */
    }
}
