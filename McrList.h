//
// Created by טל פלקסין on 15/01/2024.
//

#ifndef M1_MCRLIST_H
#define M1_MCRLIST_H
#define TRUE 1
#define MAX_LABEL_LENGTH 32
#define FALSE 0

/*A pointer to a linked list*/
typedef struct nodeMcr *McrList;

McrList NewMcr(char *name, int start) ;
void InsertMcrToList(McrList *head, McrList new_mcr) ;
McrList SearchMcr(McrList mcr, char *name) ;
int HandelMcrName(char *name) ;
char *getName(McrList linked) ;
int getStart(McrList linked) ;
int getEnd(McrList linked) ;
McrList getNext(McrList linked);
void setStart(McrList linked, int start) ;
void setEnd(McrList linked, int end) ;
void freelist(McrList head) ;

#endif //M1_MCRLIST_H
