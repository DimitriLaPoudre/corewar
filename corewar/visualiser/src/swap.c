/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** swap.c
*/

#include "my.h"

long swap_64bits(char map[MEM_SIZE], long index)
{
    return ((long)(map[(index) % MEM_SIZE]) << 56 & 0xFF00000000000000)
    | ((long)(map[(index + 1) % MEM_SIZE]) << 48 & 0xFF000000000000)
    | ((long)(map[(index + 2) % MEM_SIZE]) << 40 & 0xFF0000000000)
    | ((long)(map[(index + 3) % MEM_SIZE]) << 32 & 0xFF00000000)
    | ((long)(map[(index + 4) % MEM_SIZE]) << 24 & 0xFF000000)
    | ((long)(map[(index + 5) % MEM_SIZE]) << 16 & 0xFF0000)
    | ((long)(map[(index + 6) % MEM_SIZE]) << 8 & 0xFF00)
    | ((long)(map[(index + 7) % MEM_SIZE]) & 0xFF);
}

int swap_32bits(char map[MEM_SIZE], long index)
{
    return ((int)(map[(index) % MEM_SIZE]) << 24 & 0xFF000000)
    | ((int)(map[(index + 1) % MEM_SIZE]) << 16 & 0xFF0000)
    | ((int)(map[(index + 2) % MEM_SIZE]) << 8 & 0xFF00)
    | ((int)(map[(index + 3) % MEM_SIZE]) & 0xFF);
}

short swap_16bits(char map[MEM_SIZE], long index)
{
    return ((short)(map[(index) % MEM_SIZE]) << 8 & 0xFF00)
    | ((short)(map[(index + 1) % MEM_SIZE]) & 0xFF);
}

int swap_32bits_nb(int value)
{
    return (value >> 24 & 0xFF) | (value >> 8 & 0xFF00)
    | (value << 8 & 0xFF0000) | (value << 24 & 0xFF000000);
}
