/*
** EPITECH PROJECT, 2023
** my_put_in_list.c
** File description:
** my_put_in_list.c
*/

#include "../../include/linked_list.h"
#include <stdlib.h>

void list_add_prev(ll_t **list, void *data)
{
    ll_t *param;

    param = malloc(sizeof(*param));
    param->data = data;
    param->next = *list;
    param->prev = NULL;
    *list = param;
}
