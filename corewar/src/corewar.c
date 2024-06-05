/*
** EPITECH PROJECT, 2023
** Standard File
** File description:
** main.c
*/

#include "my.h"

static corewar_t *init_corewar(void)
{
    corewar_t *new = CALLOC(sizeof(corewar_t));

    new->list_champion = CALLOC(sizeof(champion_t *));
    new->all_champion = CALLOC(sizeof(champion_t *));
    new->nbr_cycle_die = CYCLE_TO_DIE;
    new->act_die = CYCLE_TO_DIE;
    new->nbr_cycle_dump = -1;
    new->nbr_cycle_act = 0;
    new->champion_act = CALLOC(sizeof(champion_t));
    new->champion_act->pointer = -1;
    new->champion_act->number = -1;
    return new;
}

static void set_map_help(corewar_t *corewar, int champion_gap, int index)
{
    champion_gap /= index;
    index = 0;
    for (ll_t *tmp = *corewar->list_champion; tmp != NULL; tmp = tmp->next)
        if (CHAMPION->pointer == -1) {
            my_strncpy(corewar->map + index, CHAMPION->prog,
            CHAMPION->header.prog_size);
            CHAMPION->pointer = index;
            CHAMPION->PC = index;
            index += CHAMPION->header.prog_size + champion_gap;
        }
}

static void set_map(corewar_t *corewar)
{
    int champion_gap = MEM_SIZE;
    int index = 0;

    for (ll_t *tmp = *corewar->list_champion; tmp != NULL; tmp = tmp->next) {
        list_add_next(corewar->all_champion, tmp->data);
        CHAMPION->reg[0] = CHAMPION->number;
        if (CHAMPION->pointer == -1) {
            index++;
            champion_gap -= CHAMPION->header.prog_size;
        } else {
            my_strncpy(corewar->map + CHAMPION->pointer, CHAMPION->prog,
            CHAMPION->header.prog_size);
        }
    }
    if (index != 0)
        set_map_help(corewar, champion_gap, index);
}

void show_map(corewar_t *corewar)
{
    corewar->nbr_cycle_act = 0;
    for (int i = 0; i < MEM_SIZE; i++) {
        if (i % 8 == 0 && i != 0)
            my_putchar((i % 16 == 0) ? '\n' : ' ');
        if (i % 16 == 0)
            my_miniprintf("%d:\t", i);
        if ((corewar->map[i] & 0xFF) < 16)
            my_putchar('0');
        my_putnbr_base(corewar->map[i] & 0xFF, "0123456789abcdef");
        if ((i + 1) % 16 != 0)
            my_putchar(' ');
    }
    my_putchar('\n');
}

int corewar(int ac, char **av)
{
    corewar_t *corewar = init_corewar();

    for (int i = 1; av[i] != NULL; i++) {
        if (!valid_param(av[i], av[i + 1], &i, corewar)) {
            my_puterror("Syntax error in the command\n");
            DALLOC;
            return 84;
        }
    }
    if (corewar->champion_act->number != -1
    || corewar->champion_act->pointer != -1 || !(*corewar->list_champion)) {
        my_puterror("Syntax error in the command\n");
        DALLOC;
        return 84;
    }
    set_map(corewar);
    game_loop(corewar);
    DALLOC;
    return 0;
}
