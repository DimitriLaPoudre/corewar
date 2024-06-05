/*
** EPITECH PROJECT, 2023
** robot-factory
** File description:
** param_handling.c
*/

#include "my.h"

static int is_type_good(char type, int i, int inst)
{
    char nb = op_tab[inst - 1].type[i];

    if ((nb | type) != nb)
        return 0;
    return 1;
}

static int isnum(char *str)
{
    int i = 0;

    if (str[i] == '-' || str[i] == '+')
        i++;
    for (; str[i] != '\0'; i++)
        if (!('0' <= str[i] && str[i] <= '9'))
            return 0;
    return 1;
}

static int isreg(char *str)
{
    int nb = 0;

    if (str[0] != 0 && str[1] != 0 && str[2] != 0)
        return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!('0' <= str[i] && str[i] <= '9'))
            return 0;
        nb = nb * 10 + str[i] - '0';
    }
    if (nb > 16 || nb == 0)
        return 0;
    return 1;
}

static int direct_add(int inst)
{
    int i = inst;

    if (i == 9 || i == 10 || i == 11 || i == 12 || i == 14 || i == 15)
        return 2;
    return 4;
}

static int get_type(char *param)
{
    if (param[0] == 'r') {
        if (!isreg(param + 1))
            return -1;
        return T_REG;
    }
    if (param[0] == ':')
        return T_ILAB;
    if (param[0] == '%') {
        if (param[1] == ':')
            return T_LAB;
        if (!isnum(param + 1))
            return -1;
        return T_DIR;
    }
    if (!isnum(param)) {
        return -1;
    }
    return T_IND;
}

static int check_arg(char *param, int i, int inst, int *type)
{
    *type = get_type(param);
    if (*type < 0 || !is_type_good((*type == T_LAB) ?
    T_DIR : *type % 16, i, inst))
        return 1;
    return 0;
}

void fill_cbyte(int (*cbyte)[8], int index, int type, int add)
{
    switch (type) {
    case T_REG:
        (*cbyte)[index * 2] = 0;
        (*cbyte)[index * 2 + 1] = 1;
        break;
    case T_IND:
    case T_ILAB:
        (*cbyte)[index * 2] = 1;
        (*cbyte)[index * 2 + 1] = 1;
        break;
    case T_DIR:
    case T_LAB:
        (*cbyte)[index * 2] = 1;
        (*cbyte)[index * 2 + 1] = 0;
        break;
    }
}

static int *return_param(body_t *body, int type, wait_label_t **wait, int pos)
{
    int to_add = type % 16;

    body->tmp_byte += type % 16;
    body->param_size[body->actual_param] = to_add;
    if (type == T_ILAB)
        return add_to_wait(wait, 2, pos, body->tested_param + 1);
    return (type == T_REG) ? set_int(my_getnbr(body->tested_param + 1)) :
    set_int(swapint16(my_getnbr(body->tested_param)));
}

static int *return_dir(body_t *body, int add)
{
    return (add == 2) ?
    set_int(swapint16(my_getnbr(body->tested_param + 1))) :
    set_int(swapint32(my_getnbr(body->tested_param + 1)));
}

int *add_param(wait_label_t **wait, int pos, body_t *body, int (*cbyte)[8])
{
    int type = 0;
    int to_add;
    int add = direct_add(body->inst);

    if (check_arg(body->tested_param, body->actual_param, body->inst, &type)) {
        body->param_size[body->actual_param] = 0;
        return 0;
    }
    fill_cbyte(cbyte, body->actual_param, type, add);
    if (type == T_LAB || type == T_DIR) {
        body->tmp_byte += add;
        to_add = add;
        body->param_size[body->actual_param] = to_add;
        if (type == T_LAB) {
            return add_to_wait(wait, add, pos, body->tested_param + 2);
        } else
            return_dir(body, add);
    } else
        return return_param(body, type, wait, pos);
}
