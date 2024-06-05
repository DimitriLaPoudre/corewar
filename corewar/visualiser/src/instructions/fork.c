/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** live.c
*/

#include "my.h"

static void bubble_sort_help(ll_t *act, ll_t *temp)
{
    if (((champion_t *)(act->data))->number
    > ((champion_t *)(act->next->data))->number) {
        temp = act->data;
        act->data = act->next->data;
        act->next->data = temp;
    }
}

void bubble_sort(ll_t **begin)
{
    ll_t *act = *begin;
    ll_t *end = NULL;
    ll_t *temp = NULL;

    if (begin == NULL || *begin == NULL)
        return;
    do {
        temp = NULL;
        act = *begin;
        while (act->next != end) {
            bubble_sort_help(act, temp);
            act = act->next;
        }
        end = act;
    } while (temp);
}

static void create_fork(long index, champion_t *champion, corewar_t *corewar)
{
    champion_t *fork = CALLOC(sizeof(champion_t));

    set_default_number(fork, corewar->all_champion);
    for (int i = 0; i < PROG_NAME_LENGTH; i++)
        fork->header.prog_name[i] = champion->header.prog_name[i];
    fork->parent = champion;
    fork->PC = index;
    if (REG_NUMBER > 0)
        fork->reg[0] = fork->number;
    for (int i = 1; i < REG_NUMBER; i++)
        fork->reg[i] = champion->reg[i];
    fork->carry = champion->carry;
    fork->color = champion->color;
    fork->cooldown = 800;
    list_add_next(corewar->list_champion, fork);
    bubble_sort(corewar->list_champion);
    list_add_next(corewar->all_champion, fork);
    bubble_sort(corewar->all_champion);
}

void i_fork(champion_t *champion, corewar_t *corewar)
{
    long index = (champion->PC
    + swap_16bits(corewar->map, (champion->PC + 1)) % IDX_MOD) % MEM_SIZE;

    create_fork(index, champion, corewar);
    champion->PC += 1 + 2;
    champion->cooldown = 800;
}
