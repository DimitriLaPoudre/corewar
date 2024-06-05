/*
** EPITECH PROJECT, 2023
** my_listlen.c
** File description:
** my_listlen.c
*/

#include "../../include/linked_list.h"
#include <stdlib.h>

int list_len(ll_t **begin)
{
    int i = 0;

    for (ll_t *tmp = *begin; tmp != NULL; i++)
        tmp = tmp->next;
    return i;
}
