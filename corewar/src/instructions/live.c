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
            my_miniprintf((champion != CHAMPION) ? "%d(%s%s) say " : "",
            champion->number, champion->header.prog_name, FORK(champion));
            my_miniprintf("%d(%s%s) is alive\n", CHAMPION->number,
            CHAMPION->header.prog_name, FORK(CHAMPION));
            break;
        }
    (champion->PC)++;
    if (number == -1) {
        champion->PC += 4;
        champion->cooldown = 10;
    } else
        my_miniprintf("%d(%s%s) failed live instruction\n",
        champion->number, champion->header.prog_name, FORK(champion));
}
