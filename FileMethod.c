
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
void removeFile(char *fileN, char *file_with_extension) {
    char fileWithExtension[MAX_FILE_NAME] = {0};
    fullNameToFile(fileN, file_with_extension, fileWithExtension);
    remove(fileWithExtension);
}

void readAndCopyRow(FILE *fileN, char lineCheck[MAX_LINE_LENGTH], char lineCopy[MAX_LINE_LENGTH]) {
    int i;
    int temp;
    int flag = 0;
    for(i=0;i<MAX_LINE_LENGTH;i++){
        if(flag)
            lineCheck[i]='\0';
        else{
            if((temp=fgetc(fileN))!='\n' && temp!=EOF)
                lineCheck[i]=(char)temp;
            else {
                flag = 1;
                lineCheck[i]='\n';
            }
        }
    }
    for(i=0;i<MAX_LINE_LENGTH;i++) {
        lineCopy[i] = lineCheck[i];
        printf("%c", lineCopy[i]);
    }
    printf("\n");
}

