
#include  "FileMethod.h"
#define MAX_FILE_NAME 32
void fullNameToFile(char *fileN, char *extension, char *fullFileName) {
    strcat(fullFileName, fileN);/*Add the name of the file*/
    fullFileName[strlen(fileN)] = '.';
    strcat(fullFileName + (strlen(fileN)) + 1, extension);/*Add a extension to the file*/
}


FILE *open_file(char *file_name, char *fileExtension, char *mode) {
    char fileNameWithExtension[MAX_FILE_NAME] = {0};
    FILE *file_To_Open;
    fullNameToFile(file_name, fileExtension, fileNameWithExtension);
    /*Opening the file with matching extension according to received mode*/
    file_To_Open = fopen(fileNameWithExtension, mode);
    return file_To_Open;
}
