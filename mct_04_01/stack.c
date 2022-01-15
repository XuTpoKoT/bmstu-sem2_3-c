#include "stack.h"

static node_t *stack_create_node(data_t data)
{
    node_t *node = malloc(sizeof(node_t));

    if (!node)
        return NULL;

    node->data = data;
    node->next = NULL;
    
    return node;
}

int stack_push(node_t **head, data_t data)
{
    node_t *node = stack_create_node(data);
    if (!node)
        return EXIT_FAILURE;

    node->next = *head;
    *head = node;

    return EXIT_SUCCESS;
}

int stack_pop(node_t **head, data_t *data)
{
    if (!(*head))
        return EXIT_FAILURE;

    node_t *prev = (*head);
    *data = prev->data;
    (*head) = (*head)->next;
    free(prev);

    return EXIT_SUCCESS;
}

void stack_free(node_t **head)
{
    data_t *data;
    while (*head)
        stack_pop(head, data);
}