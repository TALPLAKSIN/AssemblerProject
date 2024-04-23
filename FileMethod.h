#ifndef FILEMETHOD_H
#define FILEMETHOD_H

#include <string.h>
#include <stdio.h>

#define MaxInputLength 80
#define MaxFileNAME 32

/*
   This function add the needing extension to the file for example (am,ob..)
   parameters:
                @param fileName -the received file that we want to add extension
                @param extension -the extension we want to add
                @param completeFileName - the name of the file after adding the extension
    return:
                @return non
 */
void extensionToFileName(char *fileName, char *extension, char *completeFileName);

/*
   This function opening the received file with the received mode
   parameters:
                @param fileName -the received file
                @param extension -the extension file
                @param modeFile - the mode the file will open
    return:
                @return non
 */
FILE *openTheFile(char *fileName, char *extension, char *modeFile);

/*
   This function detects an existing define in the file and replaces its name with its value
   parameters:
                @param define - the name of the Define
                @param value - A string containing the numeric value of the Define
                @param originalLine - A array store the line where we found the Define to replace in this line
    return:
                @return non
 */
void WriteDefine(char *define, char *value, char originalLine[]);

/*
   This function delete the received file
   parameters:
                @param file_name - the name received file that we want to delete
                @param file_with_extension - the extension of the received file that we want to delete
    return:
                @return non
 */
void deleteFile(char *file_name, char *file_with_extension);

/*
   This function close the received file
   parameters:
                @param inputFile - a pointer to the received file
                @param fileValidLabels - file that contains all the label names that appears
                @param checksEntry - file that contains all the entry label names that appears
    return:
                @return non
 */
void closeTheFiles(FILE *inputFile, FILE *fileValidLabels, FILE *checksEntry);

/*
   This function fets the line from the file, and copies the line into 2 arrays
   parameters:
                @param file_name - a pointer to the received file
                @param lineValidation - An array that keeps the line,which all the tests make on
                                    the line to check validation by dividing it into parts as required
                @param originalLine - An array containing the current line for check without changing the line for example without cutting
    return:
                @return non
 */
void readAndCopyRow(FILE *file_name, char lineValidation[MaxInputLength], char originalLine[MaxInputLength]);

/*
    This function closes the file, checks whether to close entry,
    extern files. Closes and deletes the relevant files

    parameters:
                @param file_name -the name of the file
                @param HeadTagList - Tag list pointer
                @param input_file - the am file we read and encode
                param entry_file -  a pointer to entry file
                @param extern_file - a pointer to extern file
                @param instructions_file -  a pointer to the instructions file
                @param data_file -  a pointer to data file

    return:
                @return non
*/
void finishFiles(char *fileName, FILE *input_file, FILE *entry_file, FILE *extern_file,
                 FILE *instructions_file, FILE *data_file);

/*
    This function unites the instruction file and the data file into one file into the - .ob file

    parameters:
                @param file_name - the name of the file
                @param instructions_file -  a pointer to the instructions file
                @param data_file -  a pointer to data file

    return:
                @return non
*/
void unitesFiles(char *file_name, FILE *instructions_file, FILE *data_file);

#endif
