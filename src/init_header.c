/*
** EPITECH PROJECT, 2025
** init_header.c
** File description:
** The file for parsing the header.
*/
#include "../include/header_asm.h"

static char *get_inside(char *line, char **file)
{
    int len;
    char *result = NULL;
    char *end = NULL;
    char *start = my_strchr(line, '"');

    if (start == NULL)
        return NULL;
    start++;
    end = my_strchr(start, '"');
    if (end == NULL)
        return NULL;
    len = end - start;
    result = malloc(len + 1);
    if (result == NULL)
        return NULL;
    my_strncpy(result, start, len);
    result[len] = '\0';
    if (file != NULL)
        *file = end + 1;
    return result;
}

header_t *parse_header(char *file)
{
    header_t *header = malloc(sizeof(header_t));
    char *current = file;
    char *name = get_inside(current, &current);
    char *comment = get_inside(current, &current);

    if (header == NULL || name == NULL || comment == NULL)
        return NULL;
    header->magic = convert_big_endian(COREWAR_EXEC_MAGIC);
    my_strncpy(header->prog_name, name, PROG_NAME_LENGTH);
    my_strncpy(header->comment, comment, COMMENT_LENGTH);
    header->prog_size = convert_big_endian(calculate_cor_size(file));
    mini_printf("name = %s, comment = %s, size = %d\n", name, comment,
        header->prog_size);
    free(name);
    free(comment);
    return header;
}

int write_header(int fd, header_t *header)
{
    int magic = convert_big_endian(header->magic);

    write(fd, &header->magic, sizeof(header->magic));
    write(fd, header->prog_name, sizeof(header->prog_name));
    write(fd, &header->prog_size, sizeof(header->prog_size));
    write(fd, header->comment, sizeof(header->comment));
    free(header);
    return SUCCESS;
}
