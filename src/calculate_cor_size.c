/*
** EPITECH PROJECT, 2025
** calculate_cor_size.c
** File description:
** The file for calculate the cor size.
*/
#include "../include/header_asm.h"

static int get_param_size(int param_type, op_t *op)
{
    if (param_type == T_REG)
        return 1;
    if (param_type == T_IND)
        return 2;
    if (param_type == T_DIR)
        return (op->code >= 9 && op->code <= 12) ? 2 : 4;
    return 0;
}

static char *skip_empty_and_comments(char *line)
{
    while (line != NULL && (line[0] == '\0' || line[0] == '#')) {
        line = my_strchr(line, '\n');
        if (line != NULL)
            line++;
    }
    mini_printf("Ligne après nettoyage : '%s'\n", line ? line : "NULL");
    return line;
}

static int skip_bad(char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    return SUCCESS;
}

static char *skip_labels(char *line)
{
    while (*line != '\0' && *line != '\n') {
        if (*line == ':') {
            line++;
            skip_bad(line);
            return line;
        }
        line++;
    }
    return line;
}

static char *get_instruction_name(char *line)
{
    static char name[256] = {0};
    int i = 0;

    while (*line == ' ' || *line == '\t')
        line++;
    while (*line != ' ' && *line != '\t' && *line != '\0' &&
        *line != '\n' && i < 255) {
        name[i] = *line;
        *line++;
        i++;
    }
    name[i] = '\0';
    mini_printf("Nom de l'instruction extrait : '%s'\n", name);
    return name;
}

static op_t *find_instruction_in_list(char *name, op_t *op_list)
{
    for (int i = 0; op_list[i].mnemonique != NULL; i++) {
        mini_printf("Comparaison avec : '%s'\n", op_list[i].mnemonique);
        if (my_strcmp(name, op_list[i].mnemonique) == 0)
            return &op_list[i];
    }
    mini_printf("Instruction '%s' non trouvée.\n", name);
    return NULL;
}

static int calculate_parameters_size(op_t *op)
{
    int total_size = 0;

    for (int i = 0; i < op->nbr_args; i++) {
        total_size += get_param_size(op->type[i], op) + 1;
    }
    return total_size + 1;
}

static int calculate_cor_size_loop(char *file, op_t *op_list)
{
    char *line = file;
    int total_size = 0;
    char *instruction_name = NULL;
    op_t *inst = NULL;

    while (line != NULL) {
        line = skip_empty_and_comments(line);
        if (line == NULL)
            break;
        line = skip_labels(line);
        instruction_name = get_instruction_name(line);
        inst = find_instruction_in_list(instruction_name, op_list);
        if (inst != NULL && inst->nbr_args > 1)
            total_size += 1;
        if (inst != NULL)
            total_size += calculate_parameters_size(inst);
        line = my_strchr(line, '\n');
        line += (line != NULL) ? 1 : 0;
    }
    return total_size;
}

int calculate_cor_size(char *file)
{
    op_t *op_list = *get_op();

    return calculate_cor_size_loop(file, op_list);
}
