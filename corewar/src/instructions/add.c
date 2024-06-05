/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** live.c
*/

#include "my.h"

static int error_calcul2(char param[4], champion_t *champion,
    corewar_t *corewar)
{
    if ((param[0] != 1)
    || ((corewar->map)[(champion->PC + 2) % MEM_SIZE] - 1) >= REG_NUMBER
    || (param[1] != 1)
    || ((corewar->map)[(champion->PC + 3) % MEM_SIZE] - 1) >= REG_NUMBER
    || (param[2] != 1)
    || ((corewar->map)[(champion->PC + 4) % MEM_SIZE] - 1) >= REG_NUMBER) {
        (champion->PC)++;
        champion->carry = 0;
        my_miniprintf("%d(%s%s) failed add instruction\n",
        champion->number, champion->header.prog_name, FORK(champion));
        return 1;
    }
    return 0;
}

void i_add(champion_t *champion, corewar_t *corewar)
{
    char param[4] = {(corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 6
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 4
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 2
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] & 0b11};
    reg_type_t value = 0;

    if (error_calcul2(param, champion, corewar))
        return;
    value = champion->reg[corewar->map[(champion->PC + 2) % MEM_SIZE] - 1];
    value += champion->reg[corewar->map[(champion->PC + 3) % MEM_SIZE] - 1];
    champion->reg[(corewar->map)[(champion->PC + 4) % MEM_SIZE] - 1] = value;
    champion->PC += 2 + 1 + 1 + 1;
    champion->carry = (value == 0) ? 1 : 0;
    champion->cooldown = 10;
    my_miniprintf("%d(%s%s) add\n",
    champion->number, champion->header.prog_name, FORK(champion));
}
