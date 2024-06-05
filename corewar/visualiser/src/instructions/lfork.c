/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** live.c
*/

#include "my.h"

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
    fork->cooldown = 1000;
    list_add_next(corewar->list_champion, fork);
    bubble_sort(corewar->list_champion);
    list_add_next(corewar->all_champion, fork);
    bubble_sort(corewar->all_champion);
}

void i_lfork(champion_t *champion, corewar_t *corewar)
{
    long index = (champion->PC
    + swap_16bits(corewar->map, (champion->PC + 1))) % MEM_SIZE;

    create_fork(index, champion, corewar);
    champion->PC += 1 + 2;
    champion->cooldown = 1000;
}
