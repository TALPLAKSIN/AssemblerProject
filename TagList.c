#include "TagList.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct nodeTag {
    char *name;/* name of the node */
    int used;
    int valueOrSize;/* for define represent value, for data represent size array*/
    int address; /* Address of the symbol */
    Type type;/* Tag type */
    TagList next;  /* Next linked */
};


TagList NewTag(char *name, int address) {
    TagList new_tag = (TagList) calloc(1, sizeof(struct nodeTag));
    new_tag->name = (char *) calloc(1, (strlen(name) + 1) * sizeof(char));
    strcpy(new_tag->name, name);
    new_tag->used = 0;
    new_tag->valueOrSize = 0;
    new_tag->address = address;
    new_tag->next = NULL;
    new_tag->type = OPERATION;
    return new_tag;
}


void InsertTagToList(TagList *head, TagList new_tag) {
    if ((*head) == NULL) /* if the list is empty */
        *head = new_tag;
    else {
        /*Make next of new node as head*/
        new_tag->next = (*head);
        /*move the head to point to the new node*/
        (*head) = new_tag;
    }
}

TagList SearchTag(TagList tag, char *name) {
    TagList temp;
    temp = tag;
    if (tag == NULL || name == NULL)
        return NULL;
    if (strcmp(tag->name, name) == 0)
        return temp;
    return SearchTag(tag->next, name);
}

void allUsed(TagList tag, int phase) {
    int flag = TRUE;
    while (tag != NULL) {
        if (tag->used != EXIST) {/*see unused link*/
            if (flag) {/*the flag marks the first time we see unused link*/
                if (phase == 0)/*message belonging to a reader layout at  phase zero */
                    printf("Warning occurred at the process, macros we didn't use: '%s'", tag->name);
                else/*message belonging to the phase one*/
                    printf("Warning occurred at the process, symbols we didn't use: '%s'", tag->name);
                flag = FALSE;
            } else
                printf(",'%s'", tag->name);/*Printing another unused name*/
        }
        tag = tag->next;/* move to check the next node*/
    }
    if (!flag)
        printf("\n");
}


void moveHead(TagList *head) {
    TagList temp = *head;
    *head = (*head)->next;
    freeLinked(temp);
}

char *getName(TagList tag) {
    return tag->name;
}


/*int getAddress(TagList tag) {
    return tag->address;
}*/

int getValueOrSize(TagList tag) {
    return tag->valueOrSize;
}

Type getType(TagList tag) {
    return tag->type;
}

/*TagList getNext(TagList tag) {
    return tag->next;
}*/

void setUsed(TagList tag, int used) {
    tag->used = used;
}

void setValueOrSize(TagList tag, int valueOrSize) {
    tag->valueOrSize = valueOrSize;
}

void setAddress(TagList tag, int address) {
    tag->address = address;
}

void setType(TagList tag, Type type) {
    tag->type = type;
}

void freeLinked(TagList tag) {
    free(tag->name);
    free(tag);
}

void freelist(TagList head) {
    TagList prev, current = head;
    while (current != NULL) {
        prev = current;
        current = current->next;
        freeLinked(prev);
    }
}

void update_IC_symbols(TagList *linked, int IC) {
    TagList temp = *linked;
    while (temp != NULL) {
        if (temp->type == DATA)/* if it's a data instruction */
            temp->address += IC;/* updates the IC counter */
        temp = temp->next;
    }
}
