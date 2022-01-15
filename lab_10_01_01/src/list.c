#include <assert.h>
#include <stdio.h>

#include "list.h"

node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void*))
{
    if (!head || !data)
        return NULL;

    while (head && comparator(head->data, data))
        head = head->next;

    return head;
}

void *pop_front(node_t **head)
{
    if (!head || !(*head))
        return NULL;

    node_t *prev = (*head);
    void *data = prev->data;
    (*head) = (*head)->next;
    free(prev);

    return data;
}

void *pop_back(node_t **head)
{
    if (!head || !(*head))
        return NULL;

    void *data;
    node_t *lastbn = list_get_last_but_one(*head);
    
    //Если в списке один элемент
    if (lastbn == NULL) 
    {
        data = (*head)->data;
        free(*head);
        *head = NULL;
    } 
    else 
    {
        data = lastbn->next->data;
        free(lastbn->next);
        lastbn->next = NULL;
    }

    return data;
}

int copy(node_t *head, node_t **new_head)
{
    if (!head)
        return EXIT_FAILURE;

    node_t *head_buf = list_create_node(head->data);
    if (!head_buf)
        return EXIT_FAILURE;

    head = head->next;

    for (; head; head = head->next)
    {
        node_t *node = list_create_node(head->data);
        if (!node)
        {
            list_free_all(&head_buf);
            return EXIT_FAILURE;
        }
        if (!list_push(&head_buf, node))
        {
            list_free_all(&head_buf);
            return EXIT_FAILURE;
        }
    }

    *new_head = list_create_node(head_buf->data); 
    node_t *cur_head = head_buf->next;

    for (; cur_head; cur_head = cur_head->next)
    {
        node_t *node = list_create_node(cur_head->data);
        if (!node)
        {
            list_free_all(&head_buf);
            list_free_all(new_head);
            return EXIT_FAILURE;
        }
        if (!list_push(new_head, node))
        {
            list_free_all(&head_buf);
            list_free_all(new_head);
            return EXIT_FAILURE;
        }
    }
    list_free_all(&head_buf); 

    return EXIT_SUCCESS;
}

node_t *reverse(node_t *head)
{
    node_t *cur_from_front = head;
    size_t nmemb = list_nmemb(head);

    if (nmemb <= 1)
        return head;

    for (size_t i = 0; i < nmemb / 2; i++)
    {
        list_swap_nodes(cur_from_front, list_get_by_pos(head, nmemb - 1 - i));
        cur_from_front = cur_from_front->next;
    }

    return head;
}

node_t *sort(node_t *head, int (*copmarator)(const void*, const void*))
{
    if (!head)
        return NULL;

    node_t *new_head = NULL;

    for (; head; head = head->next)
    {
        node_t *elem = list_create_node(head->data);
        if (!elem)
        {
            list_free_all(&new_head);
            return NULL;
        }        

        sorted_insert(&new_head, elem, copmarator);
    }

    return new_head;
}

void sorted_insert(node_t **head, node_t *elem, int (*copmarator)(const void*, const void*))
{
    if (!head || !elem)
        return;

    if (!(*head))
    {
        *head = elem;
        return;
    }
        
    node_t *cur_node = *head;

    for (; cur_node->next && copmarator(elem->data, cur_node->next->data) > 0; cur_node = cur_node->next);

    if (cur_node == *head && copmarator(elem->data, cur_node->data) < 0)
    {
        elem->next = cur_node;
        *head = elem;
    }
    else
    {
        elem->next = cur_node->next;
        cur_node->next = elem;
    }
}

// -------------------------------------------------------------------------------------
node_t *list_create_node(void *data)
{
    node_t *p = malloc(sizeof(node_t));
    if (!p)
        return NULL;

    p->data = data;
    p->next = NULL;
    
    return p;
} 

void list_free_all(node_t **head)
{
    while ((*head)->next)
        pop_front(head);

    free(*head);
}

node_t *list_push(node_t **head, node_t *node)
{
    node->next = (*head);
    (*head) = node;

    return *head;
}

void list_fprint(FILE *f, const node_t *head, void (*printer)(FILE *, const void *))
{
    while (head)
    {
        printer(f, head->data);
        head = head->next;
    }
}

size_t list_nmemb(node_t *head)
{
    size_t nmemb = 0;
    while (head)
    {
        head = head->next;
        nmemb++;
    }
    return nmemb;
}

node_t *list_get_by_pos(node_t *head, size_t pos)
{
    size_t counter = 0;
    while (counter < pos && head)
    {
        head = head->next;
        counter++;
    }
    return head;
}

node_t *list_get_last(node_t *head)
{
    if (head == NULL)
        return NULL;

    while (head->next)
        head = head->next;

    return head;
}

node_t *list_get_last_but_one(node_t *head)
{
    if (head == NULL || head->next == NULL)
        return NULL;
    
    while (head->next->next)
        head = head->next;
    
    return head;
}

void *list_del(node_t **head, size_t pos)
{
    if (pos == 0)
        return pop_front(head);

    node_t *prev = list_get_by_pos(*head, pos - 1);
    node_t *elem = prev->next;
    void *data = elem->data;

    prev->next = elem->next;
    free(elem);

    return data;
}

void list_swap_nodes(node_t *a, node_t *b)
{
    assert(a && b);

    void *tmp = a->data;  
    a->data = b->data;
    b->data = tmp;
}

