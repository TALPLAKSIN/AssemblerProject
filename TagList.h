#ifndef TAGLIST_H
#define TAGLIST_H

#define MAX_TAG_LENGTH 32
#define TRUE 1
#define FALSE 0
#define FLAGS 5
#define NON 9999/*no exist*/
#define EXIST 1
/*A pointer to a tag list*/
typedef struct nodeTag *TagList;
/*tag types option*/
typedef enum Type {
    MDEFINE,
    CODE,
    DATA,/*data and string*/
    ENTRY,
    EXTERNAL
} Type;

/*
   This function create new tag

   parameters:
                @param name - the name of the tag to create
                @param start - save the address of the new tag
    return:
                @return non
 */
TagList NewTag(char *name, int address);

/*
   This function add new node to the tag list
   parameters:
                @param head - the head of the tag list
                @param new_mcr - the mcr being adding to the list
    return:
                @return non
 */
void InsertTagToList(TagList *head, TagList new_tag);

/*
   This function prints on the screen all the unused tags
   parameters:
                @param tag - the tag list
                @param phase - in witch phase the function call
    return:
                @return non
 */
void allUsed(TagList tag, int phase);

/*
   This function checks if the name appears in the tag list
   parameters:
                @param name - the name of the tag to search
                @param mcr - a pointer to the tag list
    return:
                @return non
 */
TagList SearchTag(TagList tag, char *name);

/*
   This function changed the head of the list to be the next
   parameters:
                @param head - the head in the list we want to change
    return:
                @return nodeMcr
 */
void moveHead(TagList *head);

/*
   This function return the name of the tag
   parameters:
                @param tag -  the tag to get its name
    return:
                @return the name of the tag
 */
char *getName(TagList tag);

/*
   This function return the address of the tag
   parameters:
                @param tag - the tag to get its address
    return:
                @return the address of the tag
 */
int getAddress(TagList tag);

/*
   This function return the type of the tag for example(DATA,ENTRY,EXTERNAL..)
   parameters:
                @param tag - the tag to get its type
    return:
                @return the type of the tag
 */
Type getType(TagList tag);

/*
   This function flag that the tag used
   parameters:
                @param tag - the tag to be mark
    return:
                @return non
 */
void setUsed(TagList tag, int used);

/*
   This function change the address of the tag
   parameters:
                @param tag - the tag to be change address
    return:
                @return the address of the tag
 */
void setAddress(TagList tag, int address);

/*
   This function change the type of the tag
   parameters:
                @param tag - the tag to be change type
    return:
                @return the type of the tag
 */
void setType(TagList tag, Type type);

/*
   This function free the mcr list
   parameters:
                @param tag - the tag of the mcr list
    return:
                @return non
 */
void freeLinked(TagList tag);

/*
   This function free the mcr list
   parameters:
                @param head - the head of the mcr list
    return:
                @return non
 */
void freelist(TagList head);

/*
   This function update the tag list address - IC counter
   parameters:
                @param linked - the head of the tag list
                @param instructionCounter - the IC counter
    return:
                @return non
 */
void changeICTags(TagList *linked, int instructionCounter);

/*
   This function get the name of the next tag
   parameters:
                @param tag - the next tag to get

    return:
                @return non
 */
TagList getNextTag(TagList tag);

/*
   This function set the value of the tag
   parameters:
                @param tag - the tag to get set
                @param valueOrSize - the value to be set to the tag
    return:
                @return non
 */
void setValueOrSize(TagList tag, int valueOrSize);

/*
   This function get the value of the tag
   parameters:
                @param tag - the tag to get the value

    return:
                @return non
 */
int getValueOrSize(TagList tag);


void print1(TagList tag);

#endif


