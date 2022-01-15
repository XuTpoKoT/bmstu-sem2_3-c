#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node_t
{
    void *data;
    struct node_t *next;
} node_t;

node_t *list_create_node(void *data);
void list_free_all(node_t **head);

node_t *list_push(node_t **head, node_t *node);
void list_fprint(FILE *f, const node_t *head, void (*printer)(FILE *, const void *));

size_t list_nmemb(node_t *head);

node_t *list_get_by_pos(node_t *head, size_t pos);
node_t *list_get_last(node_t *head);
node_t *list_get_last_but_one(node_t *head);

void *list_del(node_t **head, size_t pos);
void list_swap_nodes(node_t *a, node_t *b);

// task
node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void*));
void *pop_front(node_t **head);
void *pop_back(node_t **head);

int copy(node_t *head, node_t **new_head);
node_t *reverse(node_t *head);

node_t *sort(node_t *head, int (*copmarator)(const void*, const void*));
void sorted_insert(node_t **head, node_t *elem, int (*copmarator)(const void*, const void*));

#endif