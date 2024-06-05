/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** read_instruction.c
*/

#include "my.h"

static void read_instruction(champion_t *champion, corewar_t *corewar)
{
    void (*function[])(champion_t *, corewar_t *)
    = {&i_live, &i_ld, &i_st, &i_add, &i_sub, &i_and, &i_or, &i_xor,
    &i_zjmp, &i_ldi, &i_sti, &i_fork, &i_lld, &i_lldi, &i_lfork, &i_aff};

    if ((unsigned char)(corewar->map[champion->PC]) > 16
    || (unsigned char)(corewar->map[champion->PC]) == 0) {
        (champion->PC)++;
        (champion->cooldown) = 0;
    } else
        function[(unsigned char)(corewar->map[champion->PC]) - 1](champion,
        corewar);
    champion->PC %= MEM_SIZE;
}

void champion_read(corewar_t *corewar)
{
    for (ll_t *tmp = *corewar->list_champion; tmp != NULL; tmp = tmp->next)
        if (CHAMPION->cooldown == 0)
            read_instruction(CHAMPION, corewar);
        else
            (CHAMPION->cooldown)--;
}
