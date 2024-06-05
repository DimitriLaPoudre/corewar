/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** game_loop.c
*/

#include "my.h"

static char get_parent(champion_t *champion)
{
    for (; champion->parent; champion = champion->parent);
    if (champion->live)
        return 0;
    return 1;
}

static champion_t *last_one_standing(corewar_t *corewar)
{
    int alive = 0;
    champion_t *last = NULL;

    for (ll_t *tmp = *(corewar->list_champion); tmp != NULL; tmp = tmp->next)
        if (CHAMPION->live && (!(CHAMPION->parent) || get_parent(CHAMPION))) {
            alive++;
            last = CHAMPION;
        }
    if (alive == 0)
        return ((champion_t *)((*corewar->list_champion)->data));
    if (alive == 1)
        return last;
    for (ll_t *tmp = *(corewar->list_champion); tmp != NULL; tmp = tmp->next) {
        if (!CHAMPION->live)
            list_del_node(corewar->list_champion, CHAMPION);
        else
            CHAMPION->live = 0;
    }
    return NULL;
}

void game_loop(corewar_t *corewar)
{
    champion_t *last = NULL;

    while (!last) {
        champion_read(corewar);
        if (corewar->nbr_cycle_act == corewar->nbr_cycle_dump)
            show_map(corewar);
        else
            (corewar->nbr_cycle_act)++;
        (corewar->nbr_cycle_die)--;
        if (corewar->nbr_cycle_die == 0) {
            corewar->act_die -= CYCLE_DELTA;
            corewar->nbr_cycle_die = corewar->act_die;
            last = last_one_standing(corewar);
        }
    }
    for (; last->parent; last = last->parent);
    my_miniprintf("The player %d(%s)has won.\n",
    last->number, last->header.prog_name);
}
