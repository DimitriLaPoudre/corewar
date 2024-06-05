/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** game_loop.c
*/

#include "my.h"
#include <ncurses.h>

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

static WINDOW *init_screen(ll_t **list)
{
    WINDOW *new = initscr();

    start_color();
    curs_set(0);
    for (char color = 1; color < 5; color++) {
        init_pair(color, color, COLOR_BLACK);
        init_pair(color + 4, COLOR_BLACK, color);
    }
    noecho();
    return new;
}

static void show_map2_help(int line, corewar_t *corewar)
{
    for (ll_t *tmp = *(corewar->list_champion); tmp != NULL; tmp = tmp->next) {
        attron(COLOR_PAIR(CHAMPION->color + 4));
        mvprintw(CHAMPION->PC / line + 5, (CHAMPION->PC % line) * 3, "%02x",
        corewar->map[CHAMPION->PC] & 0xFF);
        attroff(COLOR_PAIR(CHAMPION->color + 4));
    }
}

static void show_map2(corewar_t *corewar)
{
    int xmax = 0;
    int ymax = 0;
    int x = 0;
    int y = 4;
    int line;

    getmaxyx(stdscr, ymax, xmax);
    line = xmax / 3;
    mvprintw(0, 0, "current cycle: %d", corewar->nbr_cycle_act);
    mvprintw(1, 0, "death cycle: %d/%d",
    corewar->act_die - corewar->nbr_cycle_die, corewar->act_die);
    for (int i = 0; i < MEM_SIZE; i++) {
        if (i % line == 0) {
            x = 0;
            y++;
        }
        attron(COLOR_PAIR(corewar->color[i]));
        mvprintw(y, x, "%02x", corewar->map[i] & 0xFF);
        attroff(COLOR_PAIR(corewar->color[i]));
        x += 3;
    }
    show_map2_help(line, corewar);
    refresh();
}

static void stop_win(WINDOW *window)
{
    while (getch() == 0);
    wclear(window);
    endwin();
}

void game_loop(corewar_t *corewar)
{
    champion_t *last = NULL;
    WINDOW *window = init_screen(corewar->list_champion);

    wclear(window);
    while (!last) {
        champion_read(corewar);
        wclear(window);
        show_map2(corewar);
        corewar->nbr_cycle_act++;
        (corewar->nbr_cycle_die)--;
        if (corewar->nbr_cycle_die == 0) {
            corewar->act_die -= CYCLE_DELTA;
            corewar->nbr_cycle_die = corewar->act_die;
            last = last_one_standing(corewar);
        }
        usleep(8000);
    }
    stop_win(window);
    for (; last->parent; last = last->parent);
    my_miniprintf("\nThe player %d(%s)has won.\n",
    last->number, last->header.prog_name);
}
