/*
** EPITECH PROJECT, 2023
** my_str_isalpha
** File description:
** for know if a str is num
*/

#include "../../include/my.h"

int my_str_isnum(char const *str)
{
    char comma = 0;

    if (str == NULL)
        return 0;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return 0;
    return 1;
}
