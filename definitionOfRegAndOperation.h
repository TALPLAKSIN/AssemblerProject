#ifndef DEFINITIONOFREGANDOPERATION_H
#define DEFINITIONOFREGANDOPERATION_H

#define MAX_NUM_REGISTERS 7
#define MAX_OPERATIONS 16
#define ONE_TWO_OPERATION 2
#define ONE_THREE_OPERATION 2
#define WITHOUT_FIRST_OPERATION 3
#define ALL_OPERATION 4


/*
   This function checks if register name is valid for example (r0,r1..r7)
   parameters:
                @param word -the pointer to the register name
    return:
                @return TRUE if it valid register,otherwise FALSE
 */
int check_reg_name(char *word);

/*
   This function return  register number if it valid for example (r0,r1..r7)
   parameters:
                @param word -the pointer to the register
    return:
                @return register number,otherwise FALSE
 */
int get_reg_number(char *word);

/*
   This function checks if operation name is valid for example (mov,cmp..)
   parameters:
                @param word -the pointer to the command  name
    return:
                @return TRUE if its valid operation,otherwise FALSE
 */
int check_op_name(char *word);

/*
   This function return the opcode operation number if it valid operation for example (mov-->opcode = 0)
   parameters:
                @param word -the pointer to the operation
    return:
                @return opcode number,otherwise NON
 */
int get_opcode(char *word);

/*
   This function return the number of operation if it valid operation
   parameters:
                @param word -the pointer to the operation
    return:
                @return umber of operation,otherwise NON
 */
int get_num_of_operation(char *word);


#endif
