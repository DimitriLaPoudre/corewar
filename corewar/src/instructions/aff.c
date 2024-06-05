/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** live.c
*/

#include "my.h"

void i_aff(champion_t *champion, corewar_t *corewar)
{
    char param[4] = {(corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 6
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 4
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 2
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] & 0b11};

    if (param[0] != 1 || (corewar->map)[(champion->PC + 2)
    % MEM_SIZE] - 1 >= 16 || param[1] || param[2] || param[3]) {
        (champion->PC)++;
        my_miniprintf("%d(%s%s) failed aff instruction\n",
        champion->number, champion->header.prog_name, FORK(champion));
        return;
    }
    my_miniprintf("%d(%s%s) r%d contain %c\n",
    champion->number, champion->header.prog_name, FORK(champion),
    (corewar->map)[(champion->PC + 2) % MEM_SIZE],
    champion->reg[(corewar->map)[(champion->PC + 2) % MEM_SIZE] - 1] % 256);
    champion->PC += 3;
    champion->cooldown = 2;
}
