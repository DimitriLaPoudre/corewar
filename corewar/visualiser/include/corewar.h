/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** corewar.h
*/

#ifndef COREWAR
    #define COREWAR

    #include "op.h"
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <unistd.h>

    #define CHAMPION ((champion_t *)(tmp->data))
    #define FORK(champion) (champion->parent) ? " fork" : ""

#if REG_SIZE == 8
typedef long reg_type_t;
#elif REG_SIZE == 4
typedef int reg_type_t;
#elif REG_SIZE == 2
typedef short reg_type_t;
#else
typedef char reg_type_t;
#endif

typedef struct champion_s {
    int number;
    char live;
    long pointer;
    header_t header;
    char *prog;
    reg_type_t reg[REG_NUMBER];
    struct champion_s *parent;
    long PC;
    char carry;
    int cooldown;
    char color;
} champion_t;

typedef struct corewar_s {
    int nbr_cycle_act;
    int nbr_cycle_dump;
    int nbr_cycle_die;
    int act_die;
    ll_t **list_champion;
    ll_t **all_champion;
    char map[MEM_SIZE];
    char color[MEM_SIZE];
    champion_t *champion_act;
} corewar_t;

int corewar(int ac, char **av);

void bubble_sort(ll_t **begin);

int cmp_champion_number(ll_t *pivot, ll_t *opp);

char valid_param(char *flag, char *content, int *index,
    corewar_t *corewar);

void show_map(corewar_t *corewar);

void game_loop(corewar_t *corewar);

void champion_read(corewar_t *corewar);

void set_default_number(champion_t *champion, ll_t **champions);

long swap_64bits(char map[MEM_SIZE], long index);
int swap_32bits(char map[MEM_SIZE], long index);
short swap_16bits(char map[MEM_SIZE], long index);
int swap_32bits_nb(int value);

void i_live(champion_t *champion, corewar_t *corewar);
void i_ld(champion_t *champion, corewar_t *corewar);
void i_st(champion_t *champion, corewar_t *corewar);
void i_add(champion_t *champion, corewar_t *corewar);
void i_sub(champion_t *champion, corewar_t *corewar);
void i_and(champion_t *champion, corewar_t *corewar);
void i_or(champion_t *champion, corewar_t *corewar);
void i_xor(champion_t *champion, corewar_t *corewar);
void i_zjmp(champion_t *champion, corewar_t *corewar);
void i_ldi(champion_t *champion, corewar_t *corewar);
void i_sti(champion_t *champion, corewar_t *corewar);
void i_fork(champion_t *champion, corewar_t *corewar);
void i_lld(champion_t *champion, corewar_t *corewar);
void i_lldi(champion_t *champion, corewar_t *corewar);
void i_lfork(champion_t *champion, corewar_t *corewar);
void i_aff(champion_t *champion, corewar_t *corewar);

#endif
