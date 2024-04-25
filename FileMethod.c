#include  "FileMethod.h"
#include <ctype.h>

void extensionToFileName(char *fileName, char *extension, char *completeFileName) {
    /*Concatenate the original file name to the complete file name*/
    strcat(completeFileName, fileName);/*Add the name of the file*/
    /* Add a period (.) to separate the file name and extension*/
    completeFileName[strlen(fileName)] = '.';
    /*Concatenate the extension to the complete file name after the period*/
    strcat(completeFileName + (strlen(fileName)) + 1, extension);/*Add extension to the file*/
}

FILE *openTheFile(char *fileName, char *extension, char *modeFile) {
    char fileNameWithExtension[MaxFileNAME] = {0};/* Array to store the complete file name with extension*/
    FILE *file_To_Open=NULL;/*file pointer to be returned*/
    extensionToFileName(fileName, extension, fileNameWithExtension);
    /*Open the file with the complete file name and specified extension*/
    file_To_Open = fopen(fileNameWithExtension, modeFile);
    return file_To_Open;
}

void WriteDefine(char *define, char *value, char line[]) {
    int j = 0, i = 0;
    int start = 0;
    char originalLine[MaxInputLength] = {0};
    /*Copy the original line into the originalLine array*/
    for (j = 0; j < strlen(line); j++)
        originalLine[j] = line[j];
    if (j < MaxInputLength)
        originalLine[j + 1] = '\0';/*Ensure there no garbage characters at the end of the line*/
    j = 0;
    while (j < strlen(define)) {/*Finding the starting position of the DEFAINE in the line*/
        if (line[j + start] == define[j]) {
            j++;
        } else {
            j = 0;
            start++;
        }
    }
    j = 0;
    while (j < strlen(value)) {/*Copying the DEFAINE value instead of its name*/
        line[start + j] = value[j];
        j++;
    }
    start += j;/*Update the start position*/
    i = (int) strlen(value);
    j = (int) strlen(define);
    i -= j;
    j = 0;
    /*Copying the rest of the line properly according to
     * division into cases:
     * cases1: when the value of the DEFAINE is shorter than its name
     * cases2: when the value of the constant is longer than its name*/
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
        line[start + j] = '\n';/*Add a newline character in the end of the line*/
        j++;
        while (start + j < strlen(originalLine)) {
            line[start + j] = '\0';/*rest of the line put '\0'*/
            j++;
        }
    }
}


void deleteFile(char *file_name, char *file_with_extension) {
    char fileWithExtension[MaxFileNAME] = {0};/*Array to store the complete file name with extension*/
    extensionToFileName(file_name, file_with_extension, fileWithExtension);
    /*Remove the file using the complete file name with extension*/
    remove(fileWithExtension);
}

void closeTheFiles(FILE *inputFile, FILE *fileValidLabels, FILE *ValidEntryFile) {
    /*Close the input file, file containing valid labels, and valid entry file*/
    fclose(inputFile);
    fclose(fileValidLabels);
    fclose(ValidEntryFile);
    /*Delete the files "EntryFile.am" and "LabelFile.am"*/
    deleteFile("EntryFile", "am");
    deleteFile("LabelFile", "am");
}

void readAndCopyRow(FILE *fileN, char lineValidation[MaxInputLength], char originalLine[MaxInputLength]) {
    int i=0;
    int temp=0;
    int flag = 0;
    /*Reading a line from the file and copying it to the array*/
    for (i = 0; i < MaxInputLength; i++) {
        if (flag)
            lineValidation[i] = '\0';/*rest of the line put '\0'*/
        else {/*Read a character from the file*/
            if ((temp = fgetc(fileN)) != '\n' && temp != EOF)
                lineValidation[i] = (char) temp;
            else {/*terminate the copy from the file*/
                flag = 1;/*Set flag to indicate end of line*/
                lineValidation[i] = '\n';
            }
        }
    }/*Copy lineValidation to originalLine*/
    for (i = 0; i < MaxInputLength; i++)
        originalLine[i] = lineValidation[i];
}

void finishFiles(char *file_name, FILE *input_file, FILE *entry_file, FILE *extern_file,
                 FILE *instructions_file, FILE *data_file) {
    fclose(input_file);/*Close the input file*/
    if (extern_file != NULL)/*close the file if its be created */
        fclose(extern_file);
    if (entry_file != NULL) /*close the file if its be created */
        fclose(entry_file);
    fclose(instructions_file);
    fclose(data_file);
    deleteFile(file_name, "cmd");
    deleteFile(file_name, "data");
}


void unitesFiles(char *file_name, FILE *instructions_file, FILE *data_file) {
    char c='\0';
    /* Open the object file for writing*/
    FILE *object_file = openTheFile(file_name, "ob", "w");
    /*Move file pointers to the beginning of instructions_file and data_file*/
    fseek(instructions_file, 0, SEEK_SET);
    fseek(data_file, 0, SEEK_SET);
    /*Copy characters from instructions_file to object_file*/
    while ((c = fgetc(instructions_file)) != EOF)
        fputc(c, object_file);
    /* Copy characters from data_file to object_file*/
    while ((c = fgetc(data_file)) != EOF)
        fputc(c, object_file);
    /*Close the object_file*/
    fclose(object_file);
}
