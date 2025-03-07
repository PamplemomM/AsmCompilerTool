/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** The main file for the robot factory.
*/
#include "../include/header_asm.h"

static char *read_line(int fd, int size)
{
    char *buffer = malloc(sizeof(char) * (size + 1));
    int i = 0;
    int res = 0;

    if (buffer == NULL)
        return NULL;
    while (i < size) {
        res = read(fd, &buffer[i], 1);
        if (res <= 0 || buffer[i] == '\n')
            break;
        i++;
    }
    if (res <= 0 && i == 0) {
        free(buffer);
        return NULL;
    }
    buffer[i] = '\0';
    return buffer;
}

static char *dup_result(char *result, char *line, int len)
{
    static size_t total_size = 0;
    char *temp = realloc(result, total_size + len + 2);

    if (temp == NULL)
        return NULL;
    result = temp;
    my_strcpy(result + total_size, line);
    total_size += len;
    result[total_size] = '\n';
    result[total_size + 1] = '\0';
    total_size++;
    return result;
}

static char *read_file(int fd)
{
    char *result = NULL;
    char *new_result = NULL;
    int size = 256;
    char *line = read_line(fd, size);

    while (line != NULL) {
        new_result = dup_result(result, line, my_strlen(line));
        free(line);
        line = read_line(fd, size);
        if (new_result == NULL) {
            free(result);
            return NULL;
        }
        result = new_result;
    }
    free(line);
    return result;
}

char *open_file(char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    char *result = NULL;

    if (fd < 0)
        return NULL;
    result = read_file(fd);
    close(fd);
    return result;
}

char *get_cor_file(char const *argv_file)
{
    int file_len = my_strlen(argv_file);
    char *cor_file = malloc(sizeof(char) * (file_len + 5));
    int i = 0;

    my_strcpy(cor_file, argv_file);
    if (cor_file == NULL)
        return NULL;
    i = file_len - 1;
    while (i >= 0 && argv_file[i] != '.')
        i--;
    if (i >= 0 && cor_file[i + 1] == 's' && cor_file[i + 2] == '\0')
        my_strcpy(cor_file + i, ".cor");
    return cor_file;
}

int create_cor_file(char *arg, char *file)
{
    int fd;
    char *cor_file;

    mini_printf("%s\n", file);
    cor_file = get_cor_file(arg);
    fd = open(cor_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return ERROR;
    free(cor_file);
    write_header(fd, parse_header(file));
    if (parse_instructions(file, fd) == ERROR) {
        free(file);
        return ERROR;
    }
    free(file);
    close(fd);
    return SUCCESS;
}
