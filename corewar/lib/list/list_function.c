/*
** EPITECH PROJECT, 2023
** my apply on nodes
** File description:
** apply a function on each node
*/

#include "../../include/my.h"
#include <stdlib.h>
#include <stdio.h>

int list_function(ll_t **begin, void (*f)(void *))
{
    for (ll_t *tmp = *begin; tmp != NULL; tmp = tmp->next)
        f(tmp->data);
}
