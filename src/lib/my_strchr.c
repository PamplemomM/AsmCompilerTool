/*
** EPITECH PROJECT, 2024
** robot_factory
** File description:
** my_strchr.c
*/
#include "../../include/header_asm.h"

char *my_strchr(char const *str, int c)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            return (char *)&str[i];
    }
    return NULL;
}

char *my_strrchr(const char *str, int c)
{
    char *last_occurrence = NULL;
    unsigned char target = (unsigned char)c;

    if (str == NULL)
        return NULL;
    while (*str != '\0') {
        if ((unsigned char)*str == target) {
            last_occurrence = (char *)str;
        }
        str++;
    }
    if (target == '\0')
        return (char *)str;
    return last_occurrence;
}

int my_getnbr(char const *str)
{
    int i = 0;
    int res = 0;
    int is_neg = 1;

    if (str == NULL)
        return 0;
    while (str[i] != '\0' && !(str[i] >= '0' && str[i] <= '9')) {
        if (str[i] == '-') {
            is_neg *= -1;
        }
        i++;
    }
    while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9') {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res * is_neg;
}

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strncpy(char *dest, char const *src, int nb)
{
    int i = 0;

    while (src[i] != '\0' && i < nb) {
        dest[i] = src[i];
        i++;
    }
    for (int j = i; j < nb; j++)
        dest[j] = '\0';
    dest[nb] = '\0';
    return dest;
}
