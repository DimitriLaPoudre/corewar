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
        champion->PC += swap_16bits(corewar->map, (champion->PC + 1));
    } else {
        champion->PC += 3;
    }
    champion->cooldown = 20;
}
