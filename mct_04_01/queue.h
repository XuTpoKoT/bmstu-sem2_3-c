#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#include "stack.h"

#define QUEUE_INIT { .stack_push = NULL, .stack_pop = NULL }

typedef struct {
    node_t *stack_push;
    node_t *stack_pop;
} queue_t;

int queue_push(queue_t *queue, data_t data);
int queue_pop(queue_t *queue, data_t *data);
int queue_push_many(queue_t *queue, size_t nmemb, ...);
void queue_free(queue_t *queue);

#endif