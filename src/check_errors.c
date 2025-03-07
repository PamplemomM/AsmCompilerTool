/*
** EPITECH PROJECT, 2025
** calculate_cor_size.c
** File description:
** The file for calculate the cor size.
*/
#include "../include/header_asm.h"

static int parse_parameters(char *param_str, char **params, int *param_count)
{
    char *token;

    *param_count = 0;
    token = my_strtok(token ? NULL : param_str, ",");
    while (token != NULL) {
        strip_whitespace(token);
        if (*param_count >= 3)
            return ERROR;
        params[(*param_count)] = my_strdup(token);
        (*param_count)++;
        token = my_strtok(token ? NULL : param_str, ",");
    }
    return SUCCESS;
}

char *extract_string_content(char *line)
{
    char *first_quote = my_strchr(line, '"');
    char *last_quote = my_strrchr(line, '"');
    int content_length = 0;
    char *content = NULL;

    if (!first_quote || !last_quote || first_quote == last_quote)
        return NULL;
    content_length = last_quote - first_quote - 1;
    content = malloc(content_length + 1);
    if (!content)
        return NULL;
    my_strncpy(content, first_quote + 1, content_length);
    content[content_length] = '\0';
    return content;
}

static int free_parameters(char **params, int param_count)
{
    for (int i = 0; i < param_count; i++) {
        free(params[i]);
    }
    return ERROR;
}

static int validate_instruction_line3(char *param_str, op_t **op_list,
    op_t *op_info)
{
    char *params[3] = {NULL};
    int param_count = 0;
    int result = SUCCESS;

    if (!param_str)
        return ERROR;
    if (parse_parameters(param_str, params, &param_count) != SUCCESS)
        return ERROR;
    if (param_count != op_info->nbr_args)
        return free_parameters(params, param_count);
    for (int i = 0; i < param_count; i++) {
        if (validate_parameter_type(params[i], op_info->type[i],
            op_list) != SUCCESS) {
            result = ERROR;
            break;
        }
    }
    free_parameters(params, param_count);
    return result;
}

static int is_valid_label(char *label)
{
    for (int i = 0; label[i] != ':' && label[i] != '\0'; i++) {
        if (!my_strchr(LABEL_CHARS, label[i]))
            return ERROR;
    }
    return SUCCESS;
}

static int validate_instruction_line2(char *line, char **op_name)
{
    char *instruction_start = my_strchr(line, ':');

    if (instruction_start) {
        *instruction_start = '\0';
        if (is_valid_label(line) != SUCCESS)
            return ERROR;
        instruction_start++;
        while (*instruction_start == ' ' || *instruction_start == '\t' ||
            *instruction_start == '\n' || *instruction_start == '\r' ||
            *instruction_start == '\f' || *instruction_start == '\v')
            instruction_start++;
        line = instruction_start;
    }
    *op_name = my_strtok(line, " \t");
    return SUCCESS;
}

static int validate_instruction_line(char *line, op_t **op_list)
{
    char *op_name = NULL;
    op_t *op_info = NULL;
    char *param_str = NULL;

    if (validate_instruction_line2(line, &op_name) || !op_name)
        return ERROR;
    for (int i = 0; (*op_list)[i].mnemonique != NULL; i++) {
        if (my_strcmp(op_name, (*op_list)[i].mnemonique) == 0) {
            op_info = &((*op_list)[i]);
            break;
        }
    }
    if (!op_info)
        return ERROR;
    param_str = my_strtok(NULL, "");
    return validate_instruction_line3(param_str, op_list, op_info);
}

static int validate_champion_loop(char *file_content, char *line,
    ValidationState_t *state, op_t **op_list)
{
    strip_whitespace(line);
    if (my_strlen(line) == 0 || line[0] == '#') {
        return SUCCESS;
    }
    if (my_strncmp(line, ".name", 5) == 0) {
        if (validate_name_line(line) != SUCCESS)
            return ERROR;
        state->has_name = 1;
        return SUCCESS;
    }
    if (my_strncmp(line, ".comment", 8) == 0) {
        if (validate_comment_line(line) != SUCCESS)
            return ERROR;
        state->has_comment = 1;
        return SUCCESS;
    }
    if (validate_instruction_line(line, op_list) != SUCCESS)
        return ERROR;
    state->instruction_count++;
    free(line);
}

static int check_multiple_header(char const *line)
{
    static int name_cnt = 0;
    static int comment_cnt = 0;
    char *check_line = my_strchr(line, '.');

    if (check_line == NULL)
        return SUCCESS;
    if (my_strncmp(check_line, ".name", 5) == 0)
        name_cnt++;
    if (my_strncmp(check_line, ".comment", 8) == 0)
        comment_cnt++;
    return (name_cnt > 1 || comment_cnt > 1) ? ERROR : SUCCESS;
}

int validate_champion(char *file_content)
{
    ValidationState_t state = {0};
    int i = 0;
    char *line;
    op_t **op_list = get_op();

    if (file_content == NULL || my_strlen(file_content) == 0)
        return ERROR;
    line = get_line(file_content, &i);
    while (line != NULL) {
        if (validate_champion_loop(file_content, line, &state,
            op_list) == ERROR || check_multiple_header(line) == ERROR) {
            free(line);
            return ERROR;
        }
        free(line);
        line = get_line(file_content, &i);
    }
    if (!state.has_name || !state.has_comment)
        return ERROR;
    return SUCCESS;
}
