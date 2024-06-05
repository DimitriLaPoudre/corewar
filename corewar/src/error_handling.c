/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** error_handling.c
*/

#include "my.h"

static char valid_prog(char *path, champion_t *champion)
{
    int fd = open(path, O_RDONLY);
    struct stat info;

    if (fd == -1 || my_strlen(path) < 4
    || my_strcmp(path + my_strlen(path) - 4, ".cor"))
        return 0;
    stat(path, &info);
    if (info.st_size < sizeof(header_t))
        return 0;
    read(fd, &(champion->header), sizeof(header_t));
    champion->header.magic = swap_32bits_nb(champion->header.magic);
    champion->header.prog_size = swap_32bits_nb(champion->header.prog_size);
    if (champion->header.magic != COREWAR_EXEC_MAGIC
    || champion->header.prog_size != info.st_size - sizeof(header_t))
        return 0;
    champion->prog = ALLOC(sizeof(char) * champion->header.prog_size);
    read(fd, champion->prog, champion->header.prog_size);
    close(fd);
    return 1;
}

void set_default_number(champion_t *champion, ll_t **champions)
{
    champion->number = 1;
    for (ll_t *tmp = *champions; tmp != NULL; tmp = tmp->next)
        if (champion->number == ((champion_t *)tmp->data)->number)
            (champion->number)++;
}

static char valid_param_help(char *flag, char *content, int *index,
    corewar_t *corewar)
{
    if (flag[0] != '-' && valid_prog(flag, corewar->champion_act)) {
        if (corewar->champion_act->number == -1)
            set_default_number(corewar->champion_act, corewar->list_champion);
        corewar->champion_act->reg[0] = corewar->champion_act->number;
        list_add_next(corewar->list_champion, corewar->champion_act);
        bubble_sort(corewar->list_champion);
        corewar->champion_act = CALLOC(sizeof(champion_t));
        corewar->champion_act->pointer = -1;
        corewar->champion_act->number = -1;
        (*index)--;
        return 1;
    }
    return 0;
}

static char nb_is_not_taken(int nb, ll_t **champions)
{
    for (ll_t *tmp = *champions; tmp != NULL; tmp = tmp->next) {
        if (nb == ((champion_t *)tmp->data)->number)
            return 0;
    }
    return 1;
}

char valid_param(char *flag, char *content, int *index,
    corewar_t *corewar)
{
    (*index)++;
    if (!my_strcmp(flag, "-dump") && my_str_isnum(content)
    && corewar->nbr_cycle_dump == -1 && corewar->champion_act->number == -1
    && corewar->champion_act->pointer == -1) {
        corewar->nbr_cycle_dump = my_getnbr(content);
        return 1;
    }
    if (!my_strcmp(flag, "-n") && my_str_isnum(content)
    && corewar->champion_act->number == -1 && my_getnbr(content) != 0
    && nb_is_not_taken(my_getnbr(content), corewar->list_champion)) {
        corewar->champion_act->number = my_getnbr(content);
        return 1;
    }
    if (!my_strcmp(flag, "-a") && my_str_isnum(content)
    && corewar->champion_act->pointer == -1) {
        corewar->champion_act->pointer = my_getnbr(content) % MEM_SIZE;
        corewar->champion_act->PC = corewar->champion_act->pointer;
        return 1;
    }
    return valid_param_help(flag, content, index, corewar);
}
