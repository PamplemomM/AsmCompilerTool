/*
** EPITECH PROJECT, 2025
** op.c
** File description:
** The file for op.
*/
#include "../include/header_asm.h"

op_t **get_op(void)
{
    static op_t *op_list = NULL;

    return &op_list;
}

static int init_op2(op_t *op_list)
{
    op_list[8] = (op_t){"zjmp", 1, {T_DIR}, 9, 20, "jump if zero"};
    op_list[9] = (op_t){"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG,
        T_REG}, 10, 25, "load index"};
    op_list[10] = (op_t){"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR |
        T_REG}, 11, 25, "store index"};
    op_list[11] = (op_t){"fork", 1, {T_DIR}, 12, 800, "fork"};
    op_list[12] = (op_t){"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10,
        "long load"};
    op_list[13] = (op_t){"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR |
        T_REG, T_REG}, 14, 50, "long load index"};
    op_list[14] = (op_t){"lfork", 1, {T_DIR}, 15, 1000, "long fork"};
    op_list[15] = (op_t){"aff", 1, {T_REG}, 16, 2, "aff"};
    op_list[16] = (op_t){NULL, 0, {0}, 0, 0, 0};
    *get_op() = op_list;
    return SUCCESS;
}

void init_op(void)
{
    op_t *op_list = malloc(sizeof(op_t) * 18);

    if (op_list == NULL)
        return;
    op_list[0] = (op_t){"live", 1, {T_DIR}, 1, 10, "alive"};
    op_list[1] = (op_t){"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load"};
    op_list[2] = (op_t){"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store"};
    op_list[3] = (op_t){"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition"};
    op_list[4] = (op_t){"sub", 3, {T_REG, T_REG, T_REG}, 5, 10,
        "soustraction"};
    op_list[5] = (op_t){"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND |
        T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3"};
    op_list[6] = (op_t){"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND |
        T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3"};
    op_list[7] = (op_t){"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND |
        T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3"};
    init_op2(op_list);
}

int free_op(void)
{
    op_t *op_list = *get_op();

    if (op_list != NULL) {
        free(op_list);
        *get_op() = NULL;
    }
    return SUCCESS;
}

// op_t op_tab[] = {
//     {"live", 1, {T_DIR}, 1, 10, "alive"},
//     {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load"},
//     {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store"},
//     {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition"},
//     {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction"},
//     {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
//         "et (and  r1, r2, r3   r1&r2 -> r3"},
//     {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
//         "ou  (or   r1, r2, r3   r1 | r2 -> r3"},
//     {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
//         "ou (xor  r1, r2, r3   r1^r2 -> r3"},
//     {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero"},
//     {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
//         "load index"},
//     {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
//         "store index"},
//     {"fork", 1, {T_DIR}, 12, 800, "fork"},
//     {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load"},
//     {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
//         "long load index"},
//     {"lfork", 1, {T_DIR}, 15, 1000, "long fork"},
//     {"aff", 1, {T_REG}, 16, 2, "aff"},
//     {0, 0, {0}, 0, 0, 0}
// };
