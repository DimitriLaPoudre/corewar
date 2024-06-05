/*
** EPITECH PROJECT, 2023
** robot-factory
** File description:
** header.c
*/

#include "my.h"

static int check_string(char *string, int index, char *dest, int size)
{
    char is_string = 0;
    int len = 0;

    for (int i = index; string[i] != '\0' && len <= size; i++) {
        if (is_string < 2 && string[i] == '\"') {
            is_string++;
            continue;
        }
        if (is_string % 2 == 0 && (string[i] == ' ' || string[i] == '\t'))
            continue;
        if (is_string == 1) {
            dest[len] = string[i];
            len++;
            continue;
        }
        return 1;
    }
    if (is_string < 2 || len > size)
        return 1;
    return 0;
}

int check_header(char **file_content, header_t *header)
{
    char *tmp = NULL;
    int i = 0;

    if (file_content[0] == NULL)
        return 0;
    for (i = 0; file_content[0][i] != '.' && file_content[0][i] != '\0'; i++);
    if (my_strncmp(file_content[0] + i, NAME_CMD_STRING, 5) ||
    check_string(file_content[0] + i, 5, header->prog_name, PROG_NAME_LENGTH))
        return 0;
    if (file_content[1] == NULL)
        return 0;
    for (i = 0; file_content[1][i] != '.' && file_content[1][i] != '\0'; i++);
    if (my_strncmp(file_content[1] + i, COMMENT_CMD_STRING, 8)
    || check_string(file_content[1] + i, 8, header->comment, COMMENT_LENGTH))
        return 0;
    return 1;
}

void write_header(header_t *header, int fd)
{
    write(fd, header, sizeof(header_t));
    return;
}
