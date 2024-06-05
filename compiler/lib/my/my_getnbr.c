/*
** EPITECH PROJECT, 2023
** my_getnbr
** File description:
** my_getbr
*/

#include "../../include/my.h"

int my_getnbr(char *str)
{
    int nb = 0;
    int neg = 1;
    int i = 0;

    if (str[0] == '-' || str[0] == '+') {
        i++;
        neg = (str[0] == '-') ? -1 : 1;
    }
    for (; str[i] >= 48 && str[i] <= 57; i++)
        nb = nb * 10 + str[i] - 48;
    return nb * neg;
}
