/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** The main file for the robot factory.
*/
#include "../include/header_asm.h"
#include <string.h>

int my_error(char const *message, int return_value)
{
    write(2, message, my_strlen(message));
    return return_value;
}

int check_asm_srcfile(char *arg)
{
    int len = my_strlen(arg);

    if (my_strcmp(arg, "-h") == 0) {
        mini_printf("USAGE\n./asm file_name[.s]\nDESCRIPTION\nfile_name ");
        mini_printf("file in assembly language to be converted into ");
        mini_printf("file_name.cor, an executable in the Virtual Machine.\n");
        return SUCCESS;
    }
    if (arg[len - 1] != 's' && arg[len - 2] != '.')
        return ERROR;
    return SUCCESS;
}

int main(int argc, char **argv)
{
    int result;
    char *file;

    if (argc != 2)
        return ERROR;
    if (check_asm_srcfile(argv[1]) == ERROR)
        return ERROR;
    init_op();
    file = open_file(argv[1]);
    if (file == NULL)
        return ERROR;
    if (validate_champion(file) == ERROR)
        return ERROR;
    result = create_cor_file(argv[1], file);
    free_op();
    return result;
}
