#ifndef MCRLIST_H
#define MCRLIST_H

#define TRUE 1
#define MAX_MCR_LENGTH 32
#define FALSE 0

/*A pointer to a new_mcr list*/
typedef struct nodeMcr *McrList;

/*
   This function create new mcr

   parameters:
                @param name - the name of the mcr to create
                @param start - save the address of the new mcr
    return:
                @return non
 */
McrList NewMcr(char *name, int start);

/*
   This function add new node to the mcr list
   parameters:
                @param head - the head of the mcr list
                @param new_mcr - the mcr being adding to the list
    return:
                @return non
 */
void InsertMcrToList(McrList *head, McrList new_mcr);

/*
   This function checks if the name appears in the mcr list
   parameters:
                @param name - the name of the mcr to search
                @param mcr - a pointer to the mcr list
    return:
                @return non
 */
McrList SearchMcr(McrList mcr, char *name);

/*
   This function checks if the name of the mcr is valid
   parameters:
                @param name - the name of mcr
    return:
                @return TRUE if the name valid, otherwise FALSE
 */
int HandelMcrName(char *name);

/*
   This function identifies the start of mcr
   parameters:
                @param nodeMcr - the node represent start index of mcr
    return:
                @return nodeMcr
 */
int getStart(McrList nodeMcr);

/*
   This function identifies the end of mcr
   parameters:
                @param nodeMcr - the node represent end index of mcr
    return:
                @return nodeMcr
 */
int getEnd(McrList nodeMcr);

/*
   This function set the end index of the mcr
   parameters:
                @param nodeMcr - the name of mcr that set the end index
                @param end - save the index end of mcr
    return:
                @return non
 */
void setEnd(McrList nodeMcr, int end);

/*
   This function free the mcr list
   parameters:
                @param head - the head of the mcr list
    return:
                @return non
 */
void freelistM(McrList head);

char *getNameM(McrList nodeMcr);

McrList getNext(McrList nodeMcr);

void setStart(McrList nodeMcr, int start);

#endif
