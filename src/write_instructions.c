/*
** EPITECH PROJECT, 2025
** write_instructions.c
** File description:
** The file for writing the instructions into the cor file.
*/
#include "../include/header_asm.h"

int write_op_code(int fd, instruction_t *inst)
{
    int op_code = inst->op.code;

    write(fd, &op_code, 1);
    return SUCCESS;
}

int create_coding_byte(instruction_t *inst)
{
    int result = 0;
    int value = 0;

    for (int i = 0; i < inst->op.nbr_args; i++) {
        value = (3 - i) * 2;
        if (inst->param_types[i] == T_REG)
            result += (1 << value);
        if (inst->param_types[i] == T_DIR)
            result += (2 << value);
        if (inst->param_types[i] == T_IND)
            result += (3 << value);
    }
    return result;
}

static int write_dir(int fd, int value, int size)
{
    int big_endian_value = convert_big_endian(value);

    if (size == 2) {
        write(fd, ((char *)&big_endian_value) + 2, 2);
    } else {
        write(fd, &big_endian_value, 4);
    }
    return SUCCESS;
}

int write_instruction(int fd, instruction_t *inst)
{
    int value = 0;
    int param_type = 0;
    int size = 0;

    for (int i = 0; i < inst->op.nbr_args; i++) {
        value = inst->params[i];
        param_type = inst->param_types[i];
        if (param_type == T_REG)
            write(fd, &value, 1);
        if (param_type == T_DIR) {
            size = (inst->op.type[i] == T_DIR) ? 4 : 2;
            write_dir(fd, value, size);
        }
        if (param_type == T_IND)
            write(fd, &value, 2);
    }
    return SUCCESS;
}
