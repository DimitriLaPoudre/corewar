/*
** EPITECH PROJECT, 2023
** robot-factory
** File description:
** body.c
*/

#include "my.h"

static int convert_codingbyte(int codingbyte[MAX_ARGS_NUMBER * 2])
{
    int tmp = 0;

    for (int i = 7; i >= 0; i--)
        tmp += codingbyte[7 - i] * my_power(2, i);
    return tmp;
}

static char **get_clear_line(char *content)
{
    char **line = my_str_to_word_array(content, ",");
    int len = 0;
    int index = 0;
    char **res = NULL;

    for (int i = 0; line[i] != NULL; i++) {
        if (is_not_empty(line[i]))
            len++;
    }
    res = malloc(sizeof(char *) * (len + 1));
    for (int i = 0; i < len; index++) {
        if (is_not_empty(line[index])) {
            res[i] = line[index];
            i++;
        } else
            free(line[index]);
    }
    res[len] = NULL;
    free(line);
    return res;
}

static body_t *add_new_body(body_t *body, char *inst)
{
    body_t *new_body = malloc(sizeof(body_t));

    for (int i = 0;; i++) {
        if (op_tab[i].code == 0)
            return NULL;
        if (my_strcmp(inst, op_tab[i].mnemonique) == 0) {
            new_body->inst = op_tab[i].code;
            new_body->param = malloc(sizeof(int *) * op_tab[i].nbr_args);
            new_body->param_size = malloc(sizeof(int) * op_tab[i].nbr_args);
            break;
        }
    }
    new_body->codingbyte = 0;
    new_body->actual_param = 0;
    new_body->next = body;
    new_body->tmp_byte = 0;
    return new_body;
}

static char *clear_space2(char *str, int first, int last, int i)
{
    for (i = first + 1; str[i] != '\0'; i++)
        if (str[i] == ' ' || str[i] == '\t') {
            last = i;
            break;
        }
    if (str[i] == '\0')
        return str + first;
    for (i = last; str[i] != '\0'; i++)
        if (str[i] != ' ' && str[i] != '\t')
            break;
    str[last] = '\0';
    return (str[i] == '\0') ? str + first : NULL;
}

static char *clear_space(char *str)
{
    int i = 0;
    int first;
    int last = -1;

    if (str == NULL)
        return NULL;
    for (first = 0; str[first] != '\0'; first++)
        if (str[first] != ' ' && str[first] != '\t')
            break;
    if (str[first] == '\0')
        return NULL;
    return clear_space2(str, first, last, i);
}

static int check_body2(main_t *main, header_t *header)
{
    for (int j = 0; j < op_tab[main->body->inst - 1].nbr_args;) {
        main->body->actual_param = j;
        main->body->param[j] = add_param(&(main->wait), header->prog_size,
        main->body, &(main->cbyte));
        if (main->body->param_size[j] == 0)
            return 1;
        j++;
        main->body->tested_param = clear_space(main->line[j]);
        if (main->body->tested_param == NULL
        && j < op_tab[main->body->inst - 1].nbr_args)
            return 1;
    }
    return 0;
}

static void fill_vars(main_t *main, header_t *header)
{
    main->body->codingbyte = convert_codingbyte(main->cbyte);
    header->prog_size += (main->body->inst == 1 || main->body->inst == 9
    || main->body->inst == 12 || main->body->inst == 15)
    ? main->body->tmp_byte + 1 : main->body->tmp_byte + 2;
    for (int j = 0; j < MAX_ARGS_NUMBER * 2; j++)
        main->cbyte[j] = 0;
}

static int label_modif(main_t *main, header_t *header, int *has_label)
{
    body_t *tmp_body = NULL;

    *has_label = (is_label(main->inst[0], &(main->label),
    header->prog_size)) ? 1 : 0;
    if (main->inst[*has_label] == NULL)
        return -1;
    tmp_body = add_new_body(main->body, main->inst[*has_label]);
    if (tmp_body == NULL) {
        if (*has_label != 1)
            *has_label = -1;
        return (*has_label == 1) ? -1 : 0;
    }
    main->body = tmp_body;
    return 0;
}

int check_body(main_t *main, char **content, header_t *header,
    int *has_label)
{
    for (main->l_nb = 0; content[main->l_nb] != NULL; (main->l_nb)++) {
        *has_label = 0;
        main->line = get_clear_line(content[main->l_nb]);
        main->inst = my_str_to_word_array(main->line[0], " \t");
        if (main->inst[0] == NULL || (main->inst[1] != NULL
        && main->inst[2] != NULL && main->inst[3] != NULL))
            return -1;
        if (label_modif(main, header, has_label) == -1)
            continue;
        if (*has_label == -1 || (*has_label == 0 && main->inst[2] != NULL))
            return -1;
        main->body->tested_param = main->inst[1 + *has_label];
        if (check_body2(main, header) || main->body->tested_param != NULL)
            return -1;
        fill_vars(main, header);
    }
    header->prog_size = swapint32(header->prog_size);
    return (magic_label(main->wait, main->label)) ? 0 : -1;
}

void write_body(body_t *body, int fd)
{
    body_t *rev_body = NULL;
    body_t *prev = NULL;

    if (body == NULL)
        return;
    for (; body != NULL;) {
        rev_body = body;
        body = body->next;
        rev_body->next = prev;
        prev = rev_body;
    }
    for (body = rev_body; body != NULL; body = body->next) {
        write(fd, &(body->inst), 1);
        if (body->inst != 1 && body->inst != 9
        && body->inst != 12 && body->inst != 15)
            write(fd, &(body->codingbyte), 1);
        for (int i = 0; i < op_tab[body->inst - 1].nbr_args; i++)
            write(fd, (body->param)[i], (body->param_size)[i]);
    }
    return;
}
