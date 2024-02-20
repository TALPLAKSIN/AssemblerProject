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
