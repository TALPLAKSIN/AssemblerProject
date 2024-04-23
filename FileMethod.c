#include  "FileMethod.h"
#include <ctype.h>

void extensionToFileName(char *fileName, char *extension, char *completeFileName) {
    strcat(completeFileName, fileName);/*Add the name of the file*/
    completeFileName[strlen(fileName)] = '.';
    strcat(completeFileName + (strlen(fileName)) + 1, extension);/*Add a extension to the file*/
}

FILE *openTheFile(char *fileName, char *extension, char *modeFile) {
    char fileNameWithExtension[MaxFileNAME] = {0};
    FILE *file_To_Open;
    extensionToFileName(fileName, extension, fileNameWithExtension);
    /*Opening the file with matching extension according to received mode*/
    file_To_Open = fopen(fileNameWithExtension, modeFile);
    return file_To_Open;
}

void WriteDefine(char *define, char *value, char line[]) {
    int j = 0, i = 0;
    int temp;
    int start = 0;
    char originalLine[MaxInputLength] = {0};
    for (j = 0; j < strlen(line); j++)
        originalLine[j] = line[j];
    if (j < MaxInputLength)
        originalLine[j + 1] = '\0';
    j = 0;
    while (j < strlen(define)) {/*we know define is exist*/
        if (line[j + start] == define[j]) {
            j++;
        } else {
            j = 0;
            start++;
        }
    }
    j = 0;
    while (j < strlen(value)) {
        line[start + j] = value[j];
        j++;
    }
    start += j;
    i = (int) strlen(value);
    j = (int) strlen(define);
    i -= j;
    j = 0;
    if (j < i) {
        for (; start + j < strlen(originalLine) && start + j < strlen(line); j++)
            line[start + j] = originalLine[start + j - i];
        if (start + j < MaxInputLength)
            line[start + j] = '\0';
    } else {
        while ((start + j + (strlen(define) - strlen(value))) < strlen(originalLine)) {
            line[start + j] = line[start + j + (strlen(define) - strlen(value))];
            j++;
        }
        line[start + j] = '\n';
        j++;
        while (start + j < strlen(originalLine)) {
            line[start + j] = '\0';
            j++;
        }
    }
}


void deleteFile(char *file_name, char *file_with_extension) {
    char fileWithExtension[MaxFileNAME] = {0};
    extensionToFileName(file_name, file_with_extension, fileWithExtension);
    remove(fileWithExtension);
}

void closeTheFiles(FILE *inputFile, FILE *fileValidLabels, FILE *ValidEntryFile) {
    fclose(inputFile);
    fclose(fileValidLabels);
    fclose(ValidEntryFile);
    deleteFile("EntryFile", "am");
    deleteFile("LabelFile", "am");
}

void readAndCopyRow(FILE *fileN, char lineValidation[MaxInputLength], char originalLine[MaxInputLength]) {
    int i;
    int temp;
    int flag = 0;
    for (i = 0; i < MaxInputLength; i++) {
        if (flag)
            lineValidation[i] = '\0';
        else {
            if ((temp = fgetc(fileN)) != '\n' && temp != EOF)
                lineValidation[i] = (char) temp;
            else {
                flag = 1;
                lineValidation[i] = '\n';
            }
        }
    }
    for (i = 0; i < MaxInputLength; i++)
        originalLine[i] = lineValidation[i];
}

void finishFiles(char *file_name, FILE *input_file, FILE *entry_file, FILE *extern_file,
                 FILE *instructions_file, FILE *data_file) {
    char c1;
    char c2;
    fclose(input_file);
    if (extern_file != NULL) {/*Checking if the file is empty*/
        fseek(extern_file, 0, SEEK_SET);
        c1 = (char) fgetc(extern_file);
        if (c1 != '\0' && isalpha(c1) == 0) deleteFile(file_name, "ext");/*Deleting an empty file*/
        else fclose(extern_file);/*close the file if its be created */
    }
    if (entry_file != NULL) {/*Checking if the file is empty*/
        fseek(entry_file, 0, SEEK_SET);
        c2 = (char) fgetc(entry_file);
        if (c2 != '\0' && isalpha(c2) == 0) deleteFile(file_name, "ent");/*Deleting an empty file*/
        else fclose(entry_file);
    }/*Closing and deleting files*/
    fclose(instructions_file);
    fclose(data_file);
    deleteFile(file_name, "cmd");
    deleteFile(file_name, "data");
}


void unitesFiles(char *file_name, FILE *instructions_file, FILE *data_file) {
    char c;
    FILE *object_file = openTheFile(file_name, "ob", "w");
    fseek(instructions_file, 0, SEEK_SET);
    fseek(data_file, 0, SEEK_SET);
    /*Receiving a character from the command file and writing it in the new file*/
    while ((c = fgetc(instructions_file)) != EOF)
        fputc(c, object_file);
    /*Receiving a character from the data file and writing it in the new file*/
    while ((c = fgetc(data_file)) != EOF)
        fputc(c, object_file);
    fclose(object_file);
}