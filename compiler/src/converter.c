/*
** EPITECH PROJECT, 2023
** robot-factory
** File description:
** swapint32.c
*/

#include "my.h"

int swapint32(int x)
{
    return ((x >> 24) & 0xff) | ((x << 8) & 0xff0000)
    | ((x >> 8) & 0xff00) | ((x << 24) & 0xff000000);
}

int swapint16(int x)
{
    return (((x >> 8) & 0x000000ff) | ((x << 8) & 0x0000ff00));
}

int *set_int(int nb)
{
    int *res = malloc(sizeof(int));

    *res = nb;
    return res;
}

void free_str_to_word_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

int is_not_empty(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] != ' ' && str[i] != '\t')
            return 1;
    return 0;
}
