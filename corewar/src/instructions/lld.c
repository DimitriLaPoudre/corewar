/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** live.c
*/

#include "my.h"

static void load_value(reg_type_t *reg, int index, char map[MEM_SIZE])
{
    *reg = map[(index + REG_SIZE - 1) % MEM_SIZE] & 0xFF;
    if (REG_SIZE > 1)
        *reg += (short)map[(index + REG_SIZE - 2) % MEM_SIZE] << 8 & 0xFF00;
    if (REG_SIZE > 2) {
        *reg += (int)map[(index + REG_SIZE - 3) % MEM_SIZE] << 16 & 0xFF0000;
        *reg += (int)map[(index + REG_SIZE - 4) % MEM_SIZE] << 24 & 0xFF000000;
    }
    if (REG_SIZE > 4) {
        *reg += (long)map[(index + REG_SIZE - 5) % MEM_SIZE] << 32
        & 0xFF00000000;
        *reg += (long)map[(index + REG_SIZE - 6) % MEM_SIZE] << 40
        & 0xFF0000000000;
        *reg += (long)map[(index + REG_SIZE - 7) % MEM_SIZE] << 48
        & 0xFF000000000000;
        *reg += (long)map[(index + REG_SIZE - 8) % MEM_SIZE] << 56
        & 0xFF00000000000000;
    }
}

static int error_calcul2(char param[4], champion_t *champion,
    corewar_t *corewar)
{
    if ((param[0] != 2 && param[0] != 3) || param[1] != 1
    || param[2] || param[3] || (unsigned char)(corewar->map[(champion->PC + 2
    + param[0] - param[0] / 3 + (param[0] == 2) * 2) % MEM_SIZE] - 1)
    >= REG_NUMBER) {
        (champion->PC)++;
        champion->carry = 0;
        my_miniprintf("%d(%s%s) failed ld instruction\n",
        champion->number, champion->header.prog_name, FORK(champion));
        return 1;
    }
    return 0;
}

static void i_lld_help(char param[4], champion_t *champion, corewar_t *corewar,
    long value)
{
    if (param[0] == 3)
        load_value(&(champion->reg[corewar->map[(champion->PC + 2 + param[0]
        - param[0] / 3 + (param[0] == 2) * 2) % MEM_SIZE] - 1]),
        champion->PC + value, corewar->map);
    else
        champion->reg[corewar->map[(champion->PC + 2 + param[0]
        - param[0] / 3 + (param[0] == 2) * 2) % MEM_SIZE] - 1] = value;
}

void i_lld(champion_t *champion, corewar_t *corewar)
{
    char param[4] = {(corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 6
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 4
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 2
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] & 0b11};
    long value = 0;

    if (error_calcul2(param, champion, corewar))
        return;
    if (param[0] == 2)
        value = swap_32bits(corewar->map, (champion->PC + 2));
    if (param[0] == 3)
        value = swap_16bits(corewar->map, (champion->PC + 2));
    i_lld_help(param, champion, corewar, value);
    my_miniprintf("%d(%s%s) load %d in r%d\n", champion->number,
    champion->header.prog_name, FORK(champion), value,
    corewar->map[(champion->PC + 2 + (param[0] == 2) ? 4 : 2) % MEM_SIZE]);
    champion->PC += 2 + param[0] - param[0] / 3 + (param[0] == 2) * 2 + 1;
    champion->carry = (value == 0) ? 1 : 0;
    champion->cooldown = 5;
}
