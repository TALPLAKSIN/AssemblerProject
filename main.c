#include "OpenMcr.h"
#include "ValidFile.h"
#include "encodeAndWriteToFile.h"
/**
 * @author Refael Camus and Tal Plaksin
 * @brief The process of the assembler is to build a file
 * containing machine code, from a given file of a program written in the
 * language Assembly. This is the first step in the program's path,
 * until the code is ready to run on hardware the computer.
 * @date 19.03.2023
 */


/* According to the lecturer, it can be assumed that all the received files have an 'as' extension  לבדוקקקק*/
int main(int argc, char **argv) {
    /* each cell of the flagsArray array represent a flag (5 cell - ICcounter, DCcounter, EX, EN, ERROR ) */
    int flagsArray[FLAGS] = {NON, NON, NON, NON, NON};
    TagList HeadTagList = NULL;
    int i;
    if (argc < 2) {
        printf("Error - Invalid number of arguments\n");
        return 0;
    }
    for (i = 1; i < argc; i++) {
        if (!SearchAndAddMcr(argv[i]))/* layout of all existing macros */
            continue;
        HeadTagList = HandelAndAddTag(argv[i],
                                      flagsArray); /* checking the validation of the file and create a tagList*/
        if (flagsArray[ERROR] == EXIST)
            continue;
        convertFileToBase4(argv[i], &HeadTagList,
                           flagsArray); /* when the file is valid, encoding it in spacial binary */
        freelist(HeadTagList);
    }
    return 0;
}



