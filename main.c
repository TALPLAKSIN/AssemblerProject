#include <stdio.h>
#include "ValidFile.h"

int main(int argc, char **argv) {
    /* each cell of the markValues array represent a flag (5 cell - ICcounter, DCcounter, EX, EN, ERROR ) */
    int markValues[FLAGS] = {NON, NON, NON, NON, NON};
    if (argc < 2) {
        printf("Error - Invalid number of arguments\n");
        return 0;
    }
}