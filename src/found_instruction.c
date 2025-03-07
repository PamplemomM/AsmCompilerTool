/*
** EPITECH PROJECT, 2025
** found_instructions.c
** File description:
** The file that will found the instructions for the robot factory.
*/
#include "../include/header_asm.h"

instruction_t *found_this_instruction(char *str)
{
    op_t **op_list = get_op();
    instruction_t *inst = malloc(sizeof(instruction_t));

    if (inst == NULL)
        return NULL;
    for (int i = 0; (*op_list)[i].mnemonique != NULL; i++) {
        mini_printf("Checking op_list[%d]: %s\n", i, (*op_list)[i].mnemonique);
        if (my_strcmp(str, (*op_list)[i].mnemonique) == 0) {
            inst->op = (*op_list)[i];
            mini_printf("Instruction found! %s\n", (*op_list)[i].mnemonique);
            return inst;
        }
    }
    free(inst);
    mini_printf("Instruction not found\n");
    return NULL;
}

int determine_instruction(instruction_t *inst, char **array)
{
    int i = 0;

    while (array[i] != NULL) {
        inst->param_types[i] = T_IND;
        if (array[i][0] == 'r' && array[i][1] < '9' && array[i][1] > '0')
            inst->param_types[i] = T_REG;
        if (array[i][0] == '%')
            inst->param_types[i] = T_DIR;
        inst->params[i] = my_getnbr(array[i]);
        i++;
    }
    return (inst->op.nbr_args == i) ? SUCCESS : ERROR;
}

int convert_big_endian(int nb)
{
    return ((nb >> 24) & 0xFF) | ((nb >> 8) & 0xFF00) | ((nb << 8) & 0xFF0000)
        | ((nb << 24) & 0xFF000000);
}
