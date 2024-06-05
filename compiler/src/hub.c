/*
** EPITECH PROJECT, 2023
** robot-factory
** File description:
** hub.c
*/

#include "my.h"

int usage(char *args)
{
    if (my_strcmp(args, "-h"))
        return 0;
    my_putstr("USAGE\n./asm file_name[.s]\nDESCRIPTION\nfile_name file in as");
    my_putstr("sembly language to be converted into file_name.cor, an execut");
    my_putstr("able in the Virtual Machine.\n");
    return 1;
}

int is_sfile(char *av)
{
    struct stat tested;
    int i = my_strlen(av);

    if (i < 2)
        return 1;
    if (av[i - 2] != '.' || av[i - 1] != 's')
        return 1;
    if (stat(av, &tested))
        return 1;
    return 0;
}

int error_handling(int ac, char **av)
{
    if (ac != 2)
        return 84;
    if (usage(av[1]))
        return 0;
    if (is_sfile(av[1]))
        return 84;
    return 1;
}

int hub(int ac, char **av)
{
    int handling = error_handling(ac, av);

    if (handling != 1)
        return handling;
    return assembly(ac, av);
}
