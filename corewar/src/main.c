/*
** EPITECH PROJECT, 2023
** Standard File
** File description:
** main.c
*/

#include "my.h"

static int print_h(void)
{
    int fd = open("tools/help.txt", O_RDONLY);
    struct stat st;
    char *buffer = NULL;

    stat("tools/help.txt", &st);
    buffer = malloc(sizeof(char) * (st.st_size + 1));
    buffer[st.st_size] = 0;
    read(fd, buffer, st.st_size);
    my_miniprintf("%s", buffer);
    free(buffer);
    close(fd);
    return 0;
}

int main(int ac, char **av)
{
    if (ac == 2 && !my_strcmp(av[1], "-h"))
        return print_h();
    return corewar(ac, av);
}
