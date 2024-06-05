/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** live.c
*/

#include "my.h"

void i_live(champion_t *champion, corewar_t *corewar)
{
    int number = swap_32bits(corewar->map, champion->PC + 1);

    for (ll_t *tmp = *corewar->list_champion; tmp != NULL; tmp = tmp->next)
        if (CHAMPION->number == number) {
            CHAMPION->live = 1;
            number = -1;
            break;
        }
    (champion->PC)++;
    if (number == -1) {
        champion->PC += 4;
        champion->cooldown = 10;
    }
}
