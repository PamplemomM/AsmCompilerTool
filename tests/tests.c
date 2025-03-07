/*
** EPITECH PROJECT, 2024
** elementary
** File description:
** tests.c
*/
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <string.h>
#include "../include/header_asm.h"

Test(my_strlen, basic_test)
{
    cr_assert_eq(my_strlen("Hello"), 5);
    cr_assert_eq(my_strlen(""), 0);
    cr_assert_eq(my_strlen("1234567890"), 10);
}

Test(my_strdup, basic_test)
{
    char *result = my_strdup("Hello");

    cr_assert_str_eq(result, "Hello");
    free(result);
}

Test(my_strcmp, basic_test)
{
    cr_assert_eq(my_strcmp("Hello", "Hello"), 0);
    cr_assert_gt(my_strcmp("Hello", "Hellp"), 0);
    cr_assert_lt(my_strcmp("Hellp", "Hello"), 0);
}

Test(my_strncmp, basic_test)
{
    cr_assert_eq(my_strncmp("Hello", "Hello", 5), 0);
    cr_assert_eq(my_strncmp("Hello", "Hellp", 5), 0);
    cr_assert_gt(my_strncmp("Hello", "Hellp", 4), 0);
}

Test(mini_printf, basic_test)
{
    mini_printf("Hello, %s!", "World");
}

Test(my_str_to_word_array, basic_test)
{
    char **words = my_str_to_word_array("Hello world!");

    cr_assert_str_eq(words[0], "Hello");
    cr_assert_str_eq(words[1], "world!");
    free_word_array(words);
}

Test(free_word_array, basic_test)
{
    char **words = my_str_to_word_array("One two three");

    free_word_array(words);
    cr_assert_eq(words, NULL);
}

Test(my_print_wa, basic_test)
{
    char *array[] = {"one", "two", "three", NULL};

    cr_assert_eq(my_print_wa(array), 3);
}

Test(my_strchr, basic_test)
{
    cr_assert_str_eq(my_strchr("Hello", 'e'), "ello");
    cr_assert_null(my_strchr("Hello", 'z'));
}

Test(my_getnbr, basic_test)
{
    cr_assert_eq(my_getnbr("1234"), 1234);
    cr_assert_eq(my_getnbr("-1234"), -1234);
    cr_assert_eq(my_getnbr("0"), 0);
    cr_assert_eq(my_getnbr("abc"), 0);
}

Test(my_strcpy, basic_test)
{
    char dest[20];

    cr_assert_eq(my_strcpy(dest, "Hello"), dest);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strncpy, basic_test)
{
    char dest[20];

    cr_assert_eq(my_strncpy(dest, "Hello", 3), dest);
    cr_assert_str_eq(dest, "Hel");
}

Test(calculate_cor_size, basic_test)
{
    cr_assert_eq(calculate_cor_size("test.cor"), 1024);
}

Test(validate_champion, basic_test)
{
    cr_assert_eq(validate_champion("valid.champion"), 1);
    cr_assert_eq(validate_champion("invalid.champion"), 0);
}

Test(get_op, basic_test)
{
    op_t **ops = get_op();

    cr_assert_not_null(ops);
}

Test(init_op, basic_test)
{
    init_op();
    cr_assert_not_null(get_op());
}

Test(free_op, basic_test)
{
    free_op();
    cr_assert_null(get_op());
}

Test(found_this_instruction, basic_test)
{
    instruction_t *inst = found_this_instruction("ADD");

    cr_assert_not_null(inst);
}

Test(determine_instruction, basic_test)
{
    instruction_t inst;
    char *array[] = {"ADD", "R1", "R2", NULL};

    cr_assert_eq(determine_instruction(&inst, array), 1);
}

Test(open_file, basic_test)
{
    cr_assert_not_null(open_file("test.asm"));
}

Test(create_cor_file, basic_test)
{
    cr_assert_eq(create_cor_file("test", "file.asm"), 1);
}

Test(parse_header, basic_test)
{
    cr_assert_not_null(parse_header("header.asm"));
}

Test(validate_name_line, basic_test)
{
    cr_assert_eq(validate_name_line("name: \"Test Champion\""), 1);
    cr_assert_eq(validate_name_line("invalid line"), 0);
}

Test(validate_comment_line, basic_test)
{
    cr_assert_eq(validate_comment_line("comment: \"This is a comment\""), 1);
    cr_assert_eq(validate_comment_line("invalid line"), 0);
}

Test(validate_parameter_type, basic_test)
{
    op_t **op_list = get_op();

    cr_assert_eq(validate_parameter_type("R1", 1, op_list), 1);
    cr_assert_eq(validate_parameter_type("Invalid", 1, op_list), 0);
}
