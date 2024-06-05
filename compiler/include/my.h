/*
** EPITECH PROJECT, 2023
** my.h
** File description:
** for my files
*/

#ifndef MY_H_
    #define MY_H_

    #include "garbage.h"
    #include "op.h"
    #include <sys/stat.h>
    #include <unistd.h>
    #include <fcntl.h>

void my_putchar(char c);

void my_putstr(char const *str);

void my_puterror(char const *str);

int my_miniprintf(char const *format, ...);

int my_strlen(char const *str);

int my_getnbr(char *str);

long long my_power(long long nb, long long p);

long double my_power_float(long double nb, int p);

void my_putnbr(long long nb);

void my_putnbr_base(unsigned long long nb, char const *base);

char *my_stradd(char **src, char c);

char *my_strdup(char const *src);

char *my_strcat(char *dest, char const *src);

char *my_strcpy(char *dest, char const *src);

int my_strcmp(char const *s1, char const *s2);

int my_strncmp(char const *s1, char const *s2, int n);

char **my_str_to_word_array(char *str, char *ban);

char *my_strstr(char *str, char const *to_find);

int hub(int ac, char **av);

int swapint32(int x);

int swapint16(int x);

int *set_int(int nb);

int assembly(int ac, char **av);

int check_header(char **file_content, header_t *header);

void write_header(header_t *header, int fd);

int check_body(main_t *main, char **content, header_t *header,
    int *has_label);

void write_body(body_t *body, int fd);

int is_label(char *word, label_t **label, int pos);

int *add_to_wait(wait_label_t **node, int size, int pos, char *name);

int *add_param(wait_label_t **wait, int pos, body_t *body, int (*cbyte)[8]);

int is_not_empty(char *str);

int magic_label(wait_label_t *wait, label_t *label);

void free_str_to_word_array(char **array);

#endif /* MY_H_ */
