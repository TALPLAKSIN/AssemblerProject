
#ifndef M1_TAGLIST_H
#define M1_TAGLIST_H

/*A pointer to a linked list*/
typedef struct nodeTag *TagList;
#define TRUE 1
#define FALSE 0
#define FLAGS 5
#define NON 9999/*no exist*/
#define EXIST 1
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
void allUsed(TagList tag, int phase);
TagList SearchTag(TagList tag, char *name) ;
void moveHead(TagList *head);
char* getName(TagList tag) ;
/*int getAddress(TagList tag) ;*/
int getValueOrSize(TagList tag);
Type getType(TagList tag) ;
/*TagList getNext(TagList tag) ;*/
void setUsed(TagList tag, int used) ;
void setAddress(TagList tag, int address) ;
void setType(TagList tag, Type type) ;
void setValueOrSize(TagList tag, int valueOrSize) ;
void freeLinked(TagList tag) ;
void freelist(TagList head) ;
void update_IC_symbols(TagList *linked, int IC) ;

#endif //M1_TAGLIST_H
