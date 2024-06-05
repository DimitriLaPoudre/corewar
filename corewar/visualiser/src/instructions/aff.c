/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** live.c
*/

#include "my.h"
#include <ncurses.h>

void i_aff(champion_t *champion, corewar_t *corewar)
{
    char param[4] = {(corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 6
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 4
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 2
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] & 0b11};

    if (param[0] != 1 || (corewar->map)[(champion->PC + 2)
    % MEM_SIZE] - 1 >= 16 || param[1] || param[2] || param[3]) {
        (champion->PC)++;
        return;
    }
    mvprintw(3, 0,"%d(%s%s) show [%c]\n",
    champion->number, champion->header.prog_name, FORK(champion),
    (corewar->map)[(champion->PC + 2) % MEM_SIZE],
    champion->reg[(corewar->map)[(champion->PC + 2) % MEM_SIZE] - 1] % 256);
    champion->PC += 3;
    champion->cooldown = 2;
}
