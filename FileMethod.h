#ifndef M1_FILEMETHOD_H
#define M1_FILEMETHOD_H
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_LINE_LENGTH 80
void fullNameToFile(char *fileN, char *extension, char *fullFileName) ;
FILE *open_file(char *file_name, char *fileExtension, char *mode) ;
#endif
