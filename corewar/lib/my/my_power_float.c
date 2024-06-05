/*
** EPITECH PROJECT, 2023
** my_power_float
** File description:
** my_power_float
*/

#include "../../include/my.h"

double my_power_float(double nb, long p)
{
    double result = nb;

    if (p == 0)
        return (1);
    else if (p < 0)
        return (0);
    result = nb * my_power_float(nb, p - 1);
    return (result);
}
