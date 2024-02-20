
#ifndef M1_TAGLIST_H
#define M1_TAGLIST_H

/*A pointer to a linked list*/
typedef struct nodeTag *TagList;
/*symbol types option*/
typedef enum Type {
    MDEFINE,
    OPERATION,
    DATA,/*data and string*/
    ENTRY,
    EXTERNAL
} Type;
TagList NewTag(char *name, int address) ;
void InsertTagToList(TagList *head, TagList new_tag) ;
TagList SearchTag(TagList tag, char *name) ;
#endif //M1_TAGLIST_H
