/*
** EPITECH PROJECT, 2023
** my_list
** File description:
** struct of my list
*/

#ifndef MY_LIST_
    #define MY_LIST_

    #include <stddef.h>

typedef struct linked_list {
    void *data;
    struct linked_list *next;
    struct linked_list *prev;
} ll_t;

void list_add_prev(ll_t **list, void *data);

void list_add_next(ll_t **list, void *data);

void list_rev(ll_t **begin);

int list_len(ll_t **begin);

int list_del_node(ll_t **begin, void const *data_ref);

int list_del_nodes(ll_t **begin, void const *data_ref);

int list_function(ll_t **begin, void (*f)(void *));

void list_sort(ll_t **data, int (*cmp)(ll_t *, ll_t *));

void list_sort_help(ll_t *data, ll_t *end, int (*cmp)(ll_t *, ll_t *));

#endif /* MY_LIST_ */
