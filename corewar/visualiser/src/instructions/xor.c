/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** live.c
*/

#include "my.h"

static reg_type_t get_data(long index, char map[MEM_SIZE],
    char param, champion_t *champion)
{
    if (param == 1)
        return champion->reg[map[(champion->PC + index)] - 1];
    if (param == 2)
        return (reg_type_t) swap_32bits(map, (champion->PC + index));
    if (param == 3)
        return (reg_type_t) swap_16bits(map, (champion->PC + index));
}

static int error_calcul(char param[4], champion_t *champion,
    corewar_t *corewar)
{
    if (((unsigned char)(param[0] - 1) > 2) || (param[0] == 1
    && ((corewar->map)[(champion->PC + 2) % MEM_SIZE] - 1) >= REG_NUMBER)
    || ((unsigned char)(param[1] - 1) > 2) || (param[1] == 1
    && ((corewar->map)[(champion->PC + 2 + param[0] - param[0] / 3
    + (param[0] == 2) * 2) % MEM_SIZE] - 1) >= REG_NUMBER)
    || param[2] != 1 || param[3] || (corewar->map)[(champion->PC + 2
    + param[0] - param[0] / 3 + (param[0] == 2) * 2
    + param[1] - param[1] / 3 + (param[1] == 2) * 2) % MEM_SIZE] - 1 >= 16) {
        (champion->PC)++;
        champion->carry = 0;
        return 1;
    }
    return 0;
}

void i_xor(champion_t *champion, corewar_t *corewar)
{
    char param[4] = {(corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 6
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 4
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] >> 2
    & 0b11, (corewar->map)[(champion->PC + 1) % MEM_SIZE] & 0b11};
    reg_type_t value = 0;

    if (error_calcul(param, champion, corewar))
        return;
    value = get_data(2, corewar->map, param[0], champion);
    value = value ^ get_data(2 + param[0] - param[0] / 3 + (param[0] == 2) * 2,
    corewar->map, param[1], champion);
    champion->reg[(corewar->map)[(champion->PC + 2
    + param[0] - param[0] / 3 + (param[0] == 2) * 2
    + param[1] - param[1] / 3 + (param[1] == 2) * 2) % MEM_SIZE] - 1] = value;
    champion->PC += 2 + param[0] - param[0] / 3 + (param[0] == 2) * 2
    + param[1] - param[1] / 3 + (param[1] == 2) * 2 + 1;
    champion->carry = (value == 0) ? 1 : 0;
    champion->cooldown = 6;
}
