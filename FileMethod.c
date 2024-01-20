
#include  "FileMethod.h"
#define MAX_FILE_NAME 32
void fullNameToFile(char *fileN, char *extension, char *fullFileName) {
    strcat(fullFileName, fileN);/*Add the name of the file*/
    fullFileName[strlen(fileN)] = '.';
    strcat(fullFileName + (strlen(fileN)) + 1, extension);/*Add a extension to the file*/
}