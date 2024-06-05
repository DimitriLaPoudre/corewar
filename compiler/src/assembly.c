/*
** EPITECH PROJECT, 2023
** robot-factory
** File description:
** assembly.c
*/

#include "my.h"

static int get_cleared_len(char *buffer)
{
    int count = 0;
    int in_comment = 0;

    for (int i = 0; buffer[i] != '\0'; i++) {
        if ((!in_comment) && buffer[i] == '#')
            in_comment = 1;
        if (in_comment && buffer[i] != '\n')
            continue;
        if (in_comment && buffer[i] == '\n') {
            in_comment = 0;
        }
        if (!in_comment)
            count++;
    }
    return count;
}

static int count_new(char **to_clear)
{
    int count = 0;

    for (int i = 0; to_clear[i] != NULL; i++) {
        if (!is_not_empty(to_clear[i]))
            continue;
        for (int j = 0; to_clear[i][j] != '\0'; j++)
            count++;
        count++;
    }
    return count - 1;
}

static char *clear_empty(char *buffer)
{
    char **to_clear = my_str_to_word_array(buffer, "\n");
    char *res = malloc(sizeof(char) * (count_new(to_clear) + 1));
    int index = 0;

    for (int i = 0; to_clear[i] != NULL; i++) {
        if (!is_not_empty(to_clear[i]))
            continue;
        for (int j = 0; to_clear[i][j] != '\0'; j++) {
            res[index] = to_clear[i][j];
            index++;
        }
        if (to_clear[i + 1] != NULL) {
            res[index] = '\n';
            index++;
        }
    }
    res[index] = '\0';
    free(buffer);
    free_str_to_word_array(to_clear);
    return res;
}

static char *clear_comment(char *buffer)
{
    int index = 0;
    int in_comment = 0;
    char *res = malloc(sizeof(char) * (get_cleared_len(buffer) + 1));

    for (int i = 0; buffer[i] != '\0'; i++) {
        if ((!in_comment) && buffer[i] == '#')
            in_comment = 1;
        if (in_comment && buffer[i] != '\n')
            continue;
        if (in_comment && buffer[i] == '\n') {
            in_comment = 0;
        }
        if (!in_comment)
            res[index] = buffer[i];
        index++;
    }
    res[index] = '\0';
    free(buffer);
    return res;
}

static main_t *init_main(char *file_name)
{
    main_t *main = malloc(sizeof(main_t));

    main->name_file = my_strdup(file_name);
    main->body = NULL;
    main->label = NULL;
    main->wait = NULL;
    main->line = NULL;
    main->inst = NULL;
    for (int j = 0; j < MAX_ARGS_NUMBER * 2; j++)
            main->cbyte[j] = 0;
}

static int assembly2(char **file_content, header_t *header, char *name_file)
{
    int fd;
    main_t *main = init_main(name_file);
    int has_label = 0;

    if (!check_header(file_content, header))
        return 84;
    has_label = check_body(main, file_content + 2, header, &has_label);
    if (has_label == -1)
        return 84;
    name_file[my_strlen(name_file) - 2] = '\0';
    name_file = my_strcat(name_file, ".cor");
    fd = open(name_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    write_header(header, fd);
    write_body(main->body, fd);
    return 0;
}

int assembly(int ac, char **av)
{
    struct stat file_s;
    char *buffer;
    int fd;
    header_t header = {swapint32(COREWAR_EXEC_MAGIC), 0, 0, 0};
    char **file_content = NULL;

    stat(av[1], &file_s);
    buffer = malloc(sizeof(char) * file_s.st_size + 1);
    fd = open(av[1], O_RDONLY);
    read(fd, buffer, file_s.st_size);
    close(fd);
    buffer[file_s.st_size] = '\0';
    buffer = clear_comment(buffer);
    buffer = clear_empty(buffer);
    file_content = my_str_to_word_array(buffer, "\n");
    free(buffer);
    return assembly2(file_content, &header, av[1]);
}
