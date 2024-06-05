/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** live.c
*/

#include "my.h"

static reg_type_t get_data2(long index, char map[MEM_SIZE],
    char param, champion_t *champion)
{
    if (param == 1)
        return champion->reg[map[(champion->PC + index)] - 1];
    if (param == 2)
        return (reg_type_t) swap_16bits(map, (champion->PC + index));
    if (param == 3)
        return (reg_type_t) swap_16bits(map, champion->PC
        + swap_16bits(map, (champion->PC + index)));
}

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
    if (((unsigned char)(param[0] - 1) > 2) || (param[0] == 1
    && ((corewar->map)[(champion->PC + 2) % MEM_SIZE] - 1) >= REG_NUMBER)
    || ((unsigned char)(param[1] - 1) > 1) || (param[1] == 1
    && ((corewar->map)[(champion->PC + 2 + param[0]- param[0] / 3
    + (param[0] == 2) * 2) % MEM_SIZE] - 1) >= REG_NUMBER)
    || param[2] != 1 || param[3]
    || (corewar->map)[(champion->PC + 2
    + param[0] - param[0] / 3 + (param[0] == 2) * 2
    + param[1] - param[1] / 3 + (param[1] == 2) * 2) % MEM_SIZE] - 1 >= 16) {
        (champion->PC)++;
        champion->carry = 0;
        my_miniprintf("%d(%s%s) failed ldi instruction\n",
        champion->number, champion->header.prog_name, FORK(champion));
        return 1;
    }
    return 0;
}

void i_lldi(champion_t *champion, corewar_t *corewar)
{
    char param[4] = {(corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 6
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 4
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 2
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] & 0b11};
    reg_type_t value = 0;

    if (error_calcul2(param, champion, corewar))
        return;
    value = get_data2(2, corewar->map, param[0], champion);
    value += get_data2(2 + param[0] - param[0] / 3, corewar->map, param[1],
    champion);
    load_value(&(champion->reg[(corewar->map)[(champion->PC + 2 + param[0]
    - param[0] / 3 + param[1] - param[1] / 3) % MEM_SIZE] - 1]),
    champion->PC + value, corewar->map);
    champion->PC += 2 + param[0] - param[0] / 3 + param[1] - param[1] / 3 + 1;
    champion->carry = (value == 0) ? 1 : 0;
    champion->cooldown = 25;
    my_miniprintf("%d(%s%s) load index\n",
    champion->number, champion->header.prog_name, FORK(champion));
}
