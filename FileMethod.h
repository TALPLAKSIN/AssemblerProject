#ifndef M1_FILEMETHOD_H
#define M1_FILEMETHOD_H
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_LINE_LENGTH 80
void fullNameToFile(char *fileN, char *extension, char *fullFileName) ;
FILE *open_file(char *file_name, char *fileExtension, char *mode) ;
void removeFile(char *fileN, char *file_with_extension) ;
void readAndCopyRow(FILE *fileN, char lineCheck[MAX_LINE_LENGTH], char lineCopy[MAX_LINE_LENGTH]);
#endif
