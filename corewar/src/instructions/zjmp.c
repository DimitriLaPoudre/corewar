/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** live.c
*/

#include "my.h"

void i_zjmp(champion_t *champion, corewar_t *corewar)
{
    if (champion->carry == 1) {
        my_miniprintf("%d(%s%s) jump to %d\n",
        champion->number, champion->header.prog_name, FORK(champion),
        (champion->PC + swap_16bits(corewar->map, (champion->PC + 1)))
        % MEM_SIZE);
        champion->PC += swap_16bits(corewar->map, (champion->PC + 1));
    } else {
        my_miniprintf("%d(%s%s) can't jump\n",
        champion->number, champion->header.prog_name, FORK(champion));
        champion->PC += 3;
    }
    champion->cooldown = 20;
}
