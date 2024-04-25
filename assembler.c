#include "OpenMcr.h"
#include "ValidFile.h"
#include "encodeAndWriteToFile.h"
/**
 * @author Refael Camus and Tal Plaksin
 * @brief The process of the assembler is to build a file
 * containing machine code, from a given file of a program written in the
 * language Assembly. This is the first step in the program's path,
 * until the code is ready to run on hardware the computer.
 * @date 24.04.2024
 */


/*I asked the moderator ,and it can be assumed that all the files that are accepted to run have the as extension*/
int main(int argc, char **argv) {
    /* each cell of the flagsArray array represent a flag (5 cell - ICcounter, DCcounter, EX, EN, ERROR ) */
    int flagsArray[FLAGS] = {NOT_OCCUR, NOT_OCCUR, NOT_OCCUR, NOT_OCCUR, NOT_OCCUR};/*We will initialize the array to AAAA which represents an initial value*/
    TagList HeadTagList = NULL;
    int i=0;
    if (argc < 2) {/*Checking that there is a correct amount of arguments*/
        printf("Error shade by two arguments\n");
        return 0;
    }
    for (i = 1; i < argc; i++) {
        /*The MCR phase where we interpret the macros that exist in the file*/
        if (!SearchAndAddMcr(argv[i]))
            continue;
        /*Creating a linked list of labels cold "HeadTagList" and checking the validations of the file*/
        HeadTagList = HandelAndAddTag(argv[i],flagsArray);
        if (flagsArray[ERROR] == OCCUR)
            continue;
        /*The final translation step of the entire file to base 4*/
        convertFileToBase4(argv[i], &HeadTagList,flagsArray);
        freelist(HeadTagList);
    }
    return 0;
}



