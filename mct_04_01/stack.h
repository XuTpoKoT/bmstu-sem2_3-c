#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef int data_t;

typedef struct node_t
{
    data_t data;
    struct node_t *next;
} node_t;

int stack_push(node_t **head, data_t data);
int stack_pop(node_t **head, data_t *data);
void stack_free(node_t **head);

#endif