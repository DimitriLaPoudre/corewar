/*
** EPITECH PROJECT, 2023
** robot-factory
** File description:
** label_gestion.c
*/

#include "my.h"

int check_label(wait_label_t *wait, label_t *label)
{
    for (label_t *tmp = label; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(wait->name, tmp->name) == 0) {
            free(wait->name);
            *(wait->ptr) = (wait->size == 2) ?
            swapint16(tmp->position - wait->position) :
            swapint32(tmp->position - wait->position);
            return 1;
        }
    }
    return 0;
}

int magic_label(wait_label_t *wait, label_t *label)
{
    for (; wait != NULL; wait = wait->next) {
        if (!check_label(wait, label))
            return 0;
    }
    return 1;
}

int *add_to_wait(wait_label_t **node, int size, int pos, char *name)
{
    wait_label_t *new_head = malloc(sizeof(wait_label_t));

    new_head->name = my_strdup(name);
    new_head->size = size;
    new_head->position = pos;
    new_head->ptr = malloc(sizeof(int));
    new_head->next = *node;
    *node = new_head;
    return new_head->ptr;
}

static label_t *add_to_label(char *word, label_t *label, int pos)
{
    label_t *new_head = malloc(sizeof(label_t));

    new_head->name = my_strdup(word);
    new_head->position = pos;
    new_head->next = label;
    return new_head;
}

int is_label(char *word, label_t **label, int pos)
{
    int len = my_strlen(word);
    int checked = 1;

    if (word[len - 1] != ':')
        return 0;
    for (int i = 0; i < len - 1 && checked == 1; i++) {
        checked = 0;
        for (int j = 0; LABEL_CHARS[j] != '\0'; j++)
            checked += word[i] == LABEL_CHARS[j] ? 1 : 0;
    }
    if (checked == 1) {
        word[len - 1] = '\0';
        *label = add_to_label(word, *label, pos);
    }
    return checked;
}
