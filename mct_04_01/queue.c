#include <stdarg.h>

#include "queue.h"

static void stack_move(node_t **stack_src, node_t **stack_dst)
{
    data_t data;
    while (!stack_pop(stack_src, &data))
        stack_push(stack_dst, data);
}

int queue_push(queue_t *queue, data_t data)
{
    if (!queue->stack_push)
        stack_move(&queue->stack_pop, &queue->stack_push);

    return stack_push(&queue->stack_push, data);
}

int queue_push_many(queue_t *queue, size_t nmemb, ...)
{
    va_list args;
    va_start(args, nmemb);

    for (size_t i = 0; i < nmemb; i++)
    {
        data_t data = va_arg(args, data_t);
        if (queue_push(queue, data))
            return EXIT_FAILURE;
    }

    va_end(args);

    return EXIT_SUCCESS;
}

int queue_pop(queue_t *queue, data_t *data)
{
    if (!queue->stack_pop)
        stack_move(&queue->stack_push, &queue->stack_pop);

    return stack_pop(&queue->stack_pop, data);
}

void queue_free(queue_t *queue)
{
    stack_free(&queue->stack_pop);
    stack_free(&queue->stack_push);
}


