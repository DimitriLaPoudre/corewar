/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** live.c
*/

#include "my.h"

static void write_value(reg_type_t value, long dest, char map[MEM_SIZE])
{
    map[(dest + REG_SIZE - 1) % MEM_SIZE] = (char)value & 0xFF;
    if (REG_SIZE > 1)
        map[(dest + REG_SIZE - 2) % MEM_SIZE] = (short)value >> 8 & 0xFF;
    if (REG_SIZE > 2) {
        map[(dest + REG_SIZE - 3) % MEM_SIZE] = (int)value >> 16 & 0xFF;
        map[(dest + REG_SIZE - 4) % MEM_SIZE] = (int)value >> 24 & 0xFF;
    }
    if (REG_SIZE > 4) {
        map[(dest + REG_SIZE - 5) % MEM_SIZE] = (long)value >> 32 & 0xFF;
        map[(dest + REG_SIZE - 6) % MEM_SIZE] = (long)value >> 40 & 0xFF;
        map[(dest + REG_SIZE - 7) % MEM_SIZE] = (long)value >> 48 & 0xFF;
        map[(dest + REG_SIZE - 8) % MEM_SIZE] = (long)value >> 56 & 0xFF;
    }
}

static int error_calcul2(char param[4], champion_t *champion,
    corewar_t *corewar)
{
    if (param[0] != 1 || (param[1] != 1 && param[1] != 3) || (param[1] == 1
    && ((corewar->map)[(champion->PC + 3) % MEM_SIZE] - 1) >= REG_NUMBER)
    || param[2] || param[3]
    || ((corewar->map)[(champion->PC + 2) % MEM_SIZE] - 1) >= REG_NUMBER) {
        (champion->PC)++;
        my_miniprintf("%d(%s%s) failed st instruction\n",
        champion->number, champion->header.prog_name, FORK(champion));
        return 1;
    }
    return 0;
}

void i_st(champion_t *champion, corewar_t *corewar)
{
    char param[4] = {(corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 6
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 4
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 2
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] & 0b11};
    reg_type_t value = 0;

    if (error_calcul2(param, champion, corewar))
        return;
    value = champion->reg[(corewar->map)[(champion->PC + 2) % MEM_SIZE] - 1];
    if (param[1] == 1)
        champion->reg[(corewar->map)[(champion->PC + 3) % MEM_SIZE] - 1]
        = value;
    if (param[1] == 3)
        write_value(value, champion->PC + swap_16bits(corewar->map,
        (champion->PC + 3)) % IDX_MOD, corewar->map);
    champion->PC += 2 + 1 + param[1] - param[1] / 3 + (param[1] == 2) * 2;
    champion->cooldown = 5;
    my_miniprintf("%d(%s%s) store\n", champion->number,
    champion->header.prog_name, FORK(champion));
}
