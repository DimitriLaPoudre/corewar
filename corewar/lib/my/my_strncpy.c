/*
** EPITECH PROJECT, 2023
** my_strcpy
** File description:
** copy a string into another string
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    for (; i < n; i++)
        dest[i] = src[i];
    return dest;
}
