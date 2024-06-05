/*
** EPITECH PROJECT, 2023
** my_putnbr
** File description:
** my_putnbr
*/

#include "../../include/my.h"

void my_putfloat(double nb)
{
    long first = 0;
    long second = 0;

    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    first = nb;
    nb = nb - first;
    nb *= 1000000;
    second = nb;
    if (nb - second >= 0.5)
        second += 1;
    my_putnbr(first);
    my_putchar('.');
    my_putnbr(second);
}
