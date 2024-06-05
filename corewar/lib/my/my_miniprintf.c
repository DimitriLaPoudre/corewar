/*
** EPITECH PROJECT, 2023
** mini_printf
** File description:
** recreate a part of the printf function
*/

#include "../../include/my.h"
#include <stdarg.h>

static void print_n(va_list *list, int *len)
{
    long long nb;

    nb = va_arg(*list, int);
    my_putnbr(nb);
    for (; nb > 0; (*len)++)
        nb = nb / 10;
}

static void print_f(va_list *list, int *len)
{
    double nb;

    nb = va_arg(*list, double);
    my_putfloat(nb);
    for (long long i = nb; i > 0; (*len)++)
        i = i / 10;
    *len += 7;
}

static void print_c(va_list *list, int *len)
{
    my_putchar(va_arg(*list, int));
    *len += 1;
}

static void print_s(va_list *list, int *len)
{
    char *s;

    s = va_arg(*list, char *);
    my_putstr(s);
    *len += my_strlen(s);
}

static void print_t(va_list *list, int *len)
{
    char **tab;

    tab = va_arg(*list, char **);
    for (int i = 0; tab[i] != NULL; i++) {
        my_putstr(tab[i]);
        if (tab[i + 1] != NULL) {
            my_putchar('\n');
            (*len)++;
        }
        *len += my_strlen(tab[i]);
    }
}

static void print_p(va_list *list, int *len)
{
    my_putchar('%');
    *len += 1;
}

static int choose_print(va_list *list, int *len, char l, int j)
{
    void (*tab_f[7])(va_list *, int *) = {&print_n, &print_n,
    &print_f, &print_c, &print_s, &print_t, &print_p};
    char *tab_ff[7] = {"d", "i", "f", "c", "s", "t", "%"};

    if (j == 7)
        print_p(list, len);
    else
        if (l == tab_ff[j][0]) {
            tab_f[j](list, len);
            return 1;
        }
    return 2;
}

void print_plus(int *len, char c)
{
    *len += 1;
    my_putchar(c);
}

int my_miniprintf(const char *format, ...)
{
    va_list list;
    int c_var = 0;
    int len = 0;

    va_start(list, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && c_var == 0) {
            c_var = 2;
            continue;
        }
        for (int j = 0; j < 8 && c_var == 2; j++)
            c_var = choose_print(&list, &len, format[i], j);
        if (c_var != 1)
            print_plus(&len, format[i]);
        c_var = 0;
    }
    if (c_var == 2)
        print_plus(&len, '%');
    return len;
}
