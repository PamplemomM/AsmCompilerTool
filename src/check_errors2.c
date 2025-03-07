/*
** EPITECH PROJECT, 2025
** calculate_cor_size2.c
** File description:
** The file for calculate the cor size2.
*/
#include "../include/header_asm.h"

int strip_whitespace(char *str)
{
    int start = 0;
    int end = my_strlen(str) - 1;
    int clean_length = 0;

    if (str == NULL)
        return 0;
    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')
        start++;
    if (str[start] == '\0') {
        str[0] = '\0';
        return 0;
    }
    while (end > start && (str[end] == ' ' || str[end] == '\t' ||
        str[end] == '\n' || str[end] == '\r'))
        end--;
    clean_length = end - start + 1;
    for (int i = 0; i < clean_length; i++)
        str[i] = str[start + i];
    str[clean_length] = '\0';
    return clean_length;
}

static int is_valid_header_line(char *line, const char *header_type)
{
    char *first_quote = NULL;
    char *last_quote = NULL;

    strip_whitespace(line);
    if (my_strncmp(line, header_type, my_strlen(header_type)) != 0)
        return 0;
    first_quote = my_strchr(line, '"');
    last_quote = my_strrchr(line, '"');
    return (first_quote != NULL &&
            last_quote != NULL &&
            first_quote != last_quote);
}

static int validate_string_length(char *str, int max_length)
{
    int length = 0;

    if (str == NULL)
        return ERROR;
    length = my_strlen(str);
    return (length > 0 && length <= max_length) ? SUCCESS : ERROR;
}

int validate_name_line(char *line)
{
    char *name_content = NULL;
    int result = 0;

    if (!is_valid_header_line(line, ".name"))
        return ERROR;
    name_content = extract_string_content(line);
    if (name_content == NULL)
        return ERROR;
    result = validate_string_length(name_content, PROG_NAME_LENGTH);
    free(name_content);
    return result;
}

int validate_comment_line(char *line)
{
    char *comment_content = NULL;
    int result = 0;

    if (!is_valid_header_line(line, ".comment"))
        return ERROR;
    comment_content = extract_string_content(line);
    if (comment_content == NULL)
        return ERROR;
    result = validate_string_length(comment_content, COMMENT_LENGTH);
    free(comment_content);
    return result;
}

int validate_parameter_type(char *param, int expected_type,
    op_t **op_list)
{
    int reg_num = 0;

    if (param[0] == 'r') {
        reg_num = my_getnbr(param + 1);
        return ((expected_type & T_REG) &&
                reg_num >= 1 &&
                reg_num <= REG_NUMBER) ? SUCCESS : ERROR;
    }
    if (param[0] == '%') {
        return (expected_type & T_DIR) ? SUCCESS : ERROR;
    }
    return (expected_type & T_IND) ? SUCCESS : ERROR;
}
