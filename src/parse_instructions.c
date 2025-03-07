/*
** EPITECH PROJECT, 2025
** parse_instructions.c
** File description:
** The file that will parse the robot factory.
*/
#include "../include/header_asm.h"

static int found_line_len(char *str, int i)
{
    int result = 0;

    if (i > my_strlen(str))
        return 0;
    while (str[i] != '\n' && str[i] != '\0') {
        result++;
        i++;
    }
    return result;
}

char *get_line(char *file, int *i)
{
    int len = 0;
    char *result;
    int j = 0;

    if (file == NULL || i == NULL || file[*i] == '\n')
        return NULL;
    len = found_line_len(file, *i);
    result = malloc(sizeof(char) * (len + 1));
    if (result == NULL)
        return NULL;
    while (file[*i] != '\n' && file[*i] != '\0' && j < len) {
        result[j] = file[*i];
        j++;
        (*i)++;
    }
    result[j] = '\0';
    if (file[*i] == '\n')
        (*i)++;
    return result;
}

int parse_line_instructions(char *file, int *i, char ***array)
{
    char *line;

    if (file[*i] != '\0' && file[*i] != '#' && file[*i] != '\n') {
        line = get_line(file, i);
        if (line == NULL || line[0] == '\0') {
            (*i)++;
            return ERROR;
        }
        mini_printf("Actual line : %s\n", line);
        *array = my_str_to_word_array(line);
        free(line);
        if (*array == NULL)
            return ERROR;
        for (int j = 0; (*array)[j] != NULL; j++)
            mini_printf("Instructions: %s\n", (*array)[j]);
        return SUCCESS;
    }
    (*i)++;
    return ERROR;
}

int get_inst_from_array(instruction_t *inst, char **array)
{
    for (int i = 1; array[i] != NULL; i++) {
        mini_printf("Processing parameter: %s\n", array[i]);
        inst->param_types[i - 1] = T_IND;
        inst->params[i - 1] = my_getnbr(array[i]);
        if (array[i][0] == 'r' && array[i][1] >= '0' && array[i][1] <= '9') {
            inst->param_types[i - 1] = T_REG;
            inst->params[i - 1] = my_getnbr(array[i] + 1);
        }
        if (array[i][0] == '%') {
            inst->param_types[i - 1] = T_DIR;
            inst->params[i - 1] = my_getnbr(array[i] + 1);
        }
    }
    return SUCCESS;
}

static int parse_instruction2(char *file, int *i, int coding_byte, int fd)
{
    char **array;
    instruction_t *inst = NULL;

    if (parse_line_instructions(file, i, &array) == SUCCESS) {
        inst = found_this_instruction(array[0]);
        if (inst != NULL) {
            mini_printf("Writing %s\n", array[0]);
            get_inst_from_array(inst, array);
            write_op_code(fd, inst);
            coding_byte = create_coding_byte(inst);
            write(fd, &coding_byte, 1);
            write_instruction(fd, inst);
        }
        free_word_array(array);
    }
    return SUCCESS;
}

int parse_instructions(char *file, int fd)
{
    int i = 0;
    int coding_byte = 0;
    int result = 0;

    while (file[i] != '\0') {
        parse_instruction2(file, &i, coding_byte, fd);
    }
    return SUCCESS;
}
