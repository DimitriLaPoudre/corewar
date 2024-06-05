/*
** EPITECH PROJECT, 2023
** my.h
** File description:
** for my files
*/

#ifndef MY_H_
    #define MY_H_

    #include "linked_list.h"
    #include "garbage.h"
    #include "corewar.h"
    #include <stdio.h>

    #define DEBUG my_miniprintf("gay\n")

void my_putchar(char c);

void my_putstr(char const *str);

void my_puterror(char const *str);

int my_miniprintf(char const *format, ...);

int my_strlen(char const *str);

long my_getnbr(char *str);

char *my_nbr_to_str(int nb);

long my_power(long nb, long p);

double my_power_float(double nb, long p);

void my_putnbr(long nb);

void my_putfloat(double nb);

void my_putnbr_base(unsigned long nb, char const *base);

char *my_stradd(char **src, char c);

char *my_strdup(char const *src);

char *my_strcat(char *dest, char const *src);

char *my_strcat_na(char *dest, char const *src);

char *my_strcpy(char *dest, char const *src);

char *my_strncpy(char *dest, char const *src, int n);

int my_strcmp(char const *s1, char const *s2);

int my_strncmp(char const *s1, char const *s2, int n);

int my_str_isnum(char const *str);

char **my_str_to_word_array(char *str, char *ban);

#endif /* MY_H_ */
