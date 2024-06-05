/*
** EPITECH PROJECT, 2023
** my_power
** File description:
** my_power
*/

#include "../../include/my.h"

long my_power(long nb, long p)
{
    long result = nb;

    if (p == 0)
        return (1);
    else if (p < 0)
        return (0);
    result = nb * my_power(nb, p - 1);
    return (result);
}
