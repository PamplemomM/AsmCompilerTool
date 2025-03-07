/*
** EPITECH PROJECT, 2025
** header_asm.h
** File description:
** The header for the RobotFactory project.
*/

#ifndef ASM_H
    #define ASM_H

    #include "op.h"
    #include <stddef.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>

    //defines :
    #define SUCCESS 0
    #define ERROR 84


typedef struct {
    int has_name;
    int has_comment;
    int instruction_count;
} ValidationState_t;

// Instruction structure
typedef struct instruction_s {
    op_t op;
    int params[3];
    int param_types[3];
    int address;
} instruction_t;


// ----------- LIB FUNCTIONS -----------

// --- lib_c_functions.c ---
int my_strlen(char const *str);
char *my_strdup(char const *src);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
int mini_printf(const char *format, ...);

// --- my_str_to_word_array.c ---
char **my_str_to_word_array(char *str);
void free_word_array(char **wa);
int my_print_wa(char **wa);

// --- my_strchr.c ---
char *my_strchr(char const *str, int c);
int my_getnbr(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int nb);
char *my_strrchr(const char *str, int c);

// --- my_strtok.c ---
char *my_strtok(char *str, const char *delim);

// ----------- ASM FUNCTIONS -----------

// --- calculate_cor_size.c ---
int calculate_cor_size(char *file);

// --- check_errors.c ---
char *extract_string_content(char *line);
int validate_champion(char *file_content);

// --- check_errors2.c ---
int strip_whitespace(char *str);
int validate_name_line(char *line);
int validate_comment_line(char *line);
int validate_parameter_type(char *param, int expected_type,
    op_t **op_list);

// --- op.c ---
op_t **get_op(void);
void init_op(void);
int free_op(void);

// --- found_instruction.c ---
instruction_t *found_this_instruction(char *str);
int determine_instruction(instruction_t *inst, char **array);
int convert_big_endian(int nb);

// --- init_asm.c ---
char *open_file(char *filepath);
char *get_cor_file(char const *argv_file);
int create_cor_file(char *arg, char *file);

// --- init_header.c ---
header_t *parse_header(char *file);
int write_header(int fd, header_t *header);

// --- parse_instructions.c ---
int parse_instructions(char *file, int fd);
char *get_line(char *file, int *i);

// --- write_instructions.c ---
int write_op_code(int fd, instruction_t *inst);
int create_coding_byte(instruction_t *inst);
int write_instruction(int fd, instruction_t *inst);

#endif /* ASM_H */
