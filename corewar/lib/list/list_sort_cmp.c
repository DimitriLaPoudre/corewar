/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** list_sort_cmp.c
*/

#include "../../include/my.h"

int cmp_alpha(ll_t *pivot, ll_t *opp)
{
    return my_strcmp(pivot->data, opp->data);
}

int cmp_champion_number(ll_t *pivot, ll_t *opp)
{
    return (((champion_t *)pivot->data)->number \
    - ((champion_t *)opp->data)->number);
}
