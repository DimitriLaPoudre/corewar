/*
** EPITECH PROJECT, 2023
** my_strcmp
** File description:
** pine ton oncle
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    for (; s1[i] == s2[i] && s1[i] != '\0' && i < n; i++);
    if (i == n)
        return 0;
    else
        return s1[i] - s2[i];
}
