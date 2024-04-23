#ifndef VALIDFILE_H
#define VALIDFILE_H

#include "AddressingMethods.h"

/*
  This function is the main function of the first phase after the pre-assembler phase of the program.
  which proving the validation of all the lines appearing in the received file,call the right method to
  all the instruction, and printed messages on the screen of errors and warnings and updates the counters
  parameters:
                @param file_name - the received file
                @param flagsArray - array represent a flag (5 cell - ICcounter, DCcounter, EX, EN, ERROR)
  return:
                @return non
 */
TagList HandelAndAddTag(char *file_name, int *flagsArray);

#endif


