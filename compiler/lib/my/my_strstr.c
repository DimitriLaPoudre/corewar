/*
** EPITECH PROJECT, 2023
** my strstr
** File description:
** task 5
*/

#include "../../include/my.h"

char *my_strstr(char *str, char const *to_find)
{
    int y = 0;

    if (my_strlen(to_find) == 0)
        return str;
    if (my_strlen(str) < my_strlen(to_find))
        return (0);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != to_find[y])
            y = 0;
        if (to_find[y + 1] == '\0' && str[i] == to_find[y])
            return str + (i - y);
        if (str[i] == to_find[y]) {
            y++;
        }
    }
    return (0);
}
