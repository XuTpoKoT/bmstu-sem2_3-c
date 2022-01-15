#include "sparse_matr.h"

sparse_matr_t *sparse_matr_create_node(size_t row, size_t col, data_t data)
{
    sparse_matr_t *p = malloc(sizeof(sparse_matr_t));
    if (!p)
        return NULL;

    p->row = row;
    p->col = col;
    p->data = data;
    p->next = NULL;
    
    return p;
} 

static void sparse_matr_push(sparse_matr_t **head, sparse_matr_t *node)
{
    node->next = (*head);
    (*head) = node;
}

static sparse_matr_t *sparse_matr_get_last(sparse_matr_t *head)
{
    if (head == NULL)
        return NULL;

    while (head->next)
        head = head->next;

    return head;
}

static void sparse_matr_push_back(sparse_matr_t **head, sparse_matr_t *node)
{
    sparse_matr_t *last = sparse_matr_get_last(*head);
    if (!last)
        *head = node;
    else
        last->next = node;
}

static void sparse_matr_pop(sparse_matr_t **head)
{
    if (!head || !(*head))
        return;

    sparse_matr_t *prev = (*head);
    (*head) = (*head)->next;
    free(prev);
}

sparse_matr_t *matr_to_sparse_matr(const matr_t *matr)
{
    sparse_matr_t *head = NULL;

    // for (size_t i = matr->rows - 1; i != __SIZE_MAX__; i--) // style checker(((
    //     for (size_t j = matr->cols - 1; j != __SIZE_MAX__; j--)
    //         if (matr->data[i][j] != 0)
    //         {
    //             sparse_matr_t *node = sparse_matr_create_node(i, j, matr->data[i][j]);
    //             if (!node)
    //             {
    //                 sparse_matr_free(&head);
    //                 return NULL;
    //             }
                    
    //             sparse_matr_push(&head, node);
    //         }

    for (size_t i = matr->rows - 1; i != 0; i--)
    {
        for (size_t j = matr->cols - 1; j != 0; j--)
            if (matr->data[i][j] != 0)
            {
                sparse_matr_t *node = sparse_matr_create_node(i, j, matr->data[i][j]);
                if (!node)
                {
                    sparse_matr_free(&head);
                    return NULL;
                }
                    
                sparse_matr_push(&head, node);
            }
        if (matr->data[i][0] != 0)
        {
            sparse_matr_t *node = sparse_matr_create_node(i, 0, matr->data[i][0]);
            if (!node)
            {
                sparse_matr_free(&head);
                return NULL;
            }
                
            sparse_matr_push(&head, node);
        } 
    }

    for (size_t j = matr->cols - 1; j != 0; j--)
        if (matr->data[0][j] != 0)
        {
            sparse_matr_t *node = sparse_matr_create_node(0, j, matr->data[0][j]);
            if (!node)
            {
                sparse_matr_free(&head);
                return NULL;
            }
                
            sparse_matr_push(&head, node);
        }

    if (matr->data[0][0] != 0)
    {
        sparse_matr_t *node = sparse_matr_create_node(0, 0, matr->data[0][0]);
        if (!node)
        {
            sparse_matr_free(&head);
            return NULL;
        }
            
        sparse_matr_push(&head, node);
    }         

    return head;
}

void sparse_matr_free(sparse_matr_t **head)
{
    if (!head || !(*head))
        return;

    while ((*head)->next)
        sparse_matr_pop(head);

    free(*head);
}

void sparse_matr_free_two(sparse_matr_t **a, sparse_matr_t **b)
{
    sparse_matr_free(a);
    sparse_matr_free(b);
}

void sparse_matr_fprint(FILE *f, const sparse_matr_t *head, const char *format)
{
    while (head)
    {
        fprintf(f, format, head->row, head->col, head->data);
        head = head->next;
    }
}


static void sparse_matr_del_zeros(sparse_matr_t **head)
{
    if (!head || !(*head))
        return;

    sparse_matr_t *cur_node = *head;

    while (cur_node->next)
        if (!cur_node->next->data)
        {
            sparse_matr_t *prev = cur_node->next;
            cur_node->next = cur_node->next->next;
            free(prev);
        }
        else
            cur_node = cur_node->next;

    if (!(*head)->data)
        sparse_matr_pop(head);
}

static int sparse_matr_cmp_indexes(const sparse_matr_t *matr1, const sparse_matr_t *matr2)
{
    if (matr1->row > matr2->row)
        return 1;
    else if (matr1->row < matr2->row)
        return -1;
    else if (matr1->col > matr2->col)
        return 1;
    else if (matr1->col < matr2->col)
        return -1;
    else
        return 0;
}

// ptrs should not be NULL
static void sparse_matr_move_ptrs(const sparse_matr_t **matr1, const sparse_matr_t **matr2)
{
    if ((*matr1)->row > (*matr2)->row)
        *matr2 = (*matr2)->next;
    else if ((*matr1)->row < (*matr2)->row)
        *matr1 = (*matr1)->next;
    else if ((*matr1)->col > (*matr2)->col)
        *matr2 = (*matr2)->next;
    else if ((*matr1)->col < (*matr2)->col)
        *matr1 = (*matr1)->next;
    else
    {
        *matr1 = (*matr1)->next;
        *matr2 = (*matr2)->next;
    }
}

sparse_matr_t *sparse_matr_sum(const sparse_matr_t *matr1, const sparse_matr_t *matr2)
{
    sparse_matr_t *res = NULL;   

    while (matr1 && matr2)
    {
        bool zero_res = false;
        sparse_matr_t *node = NULL;
        if (!sparse_matr_cmp_indexes(matr1, matr2))
        {
            if (matr1->data == -matr2->data)
                zero_res = true;
            else
                node = sparse_matr_create_node(matr1->row, matr1->col, matr1->data + matr2->data);            
        }
        else if (sparse_matr_cmp_indexes(matr1, matr2) < 0)
            node = sparse_matr_create_node(matr1->row, matr1->col, matr1->data);
        else
            node = sparse_matr_create_node(matr2->row, matr2->col, matr2->data);

        if (!node && !zero_res)
        {
            sparse_matr_free(&res);
            return NULL;
        }
        sparse_matr_push_back(&res, node);
        sparse_matr_move_ptrs(&matr1, &matr2);
    }  

    const sparse_matr_t *remained = matr1;
    if (!remained)
        remained = matr2;

    while (remained)
    {
        sparse_matr_t *node = sparse_matr_create_node(remained->row, remained->col, remained->data);
        if (!node)
        {
            sparse_matr_free(&res);
            return NULL;
        }
        sparse_matr_push_back(&res, node);
        remained = remained->next;
    }

    return res;
}


static void sparse_matr_sorted_insert(sparse_matr_t **head, sparse_matr_t *elem)
{
    if (!head || !elem)
        return;

    if (!(*head))
    {
        *head = elem;
        return;
    }
        
    sparse_matr_t *cur_node = *head;

    for (; cur_node->next && sparse_matr_cmp_indexes(elem, cur_node->next) > 0; cur_node = cur_node->next);

    if (cur_node == *head && sparse_matr_cmp_indexes(elem, cur_node) < 0)
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

sparse_matr_t *sparse_matr_transpose(const sparse_matr_t *head)
{
    if (!head)
        return NULL;

    sparse_matr_t *new_head = NULL;

    for (; head; head = head->next)
    {
        sparse_matr_t *elem = sparse_matr_create_node(head->col, head->row, head->data);
        if (!elem)
        {
            sparse_matr_free(&new_head);
            return NULL;
        }        

        sparse_matr_sorted_insert(&new_head, elem);
    }

    return new_head;
}

static void sparse_matr_change_row(const sparse_matr_t **head)
{
    size_t old_row = (*head)->row;
    for (; *head && (*head)->row == old_row; *head = (*head)->next);
}

sparse_matr_t *sparse_matr_find(sparse_matr_t *head, size_t row, size_t col)
{
    for (; head; head = head->next)
        if (head->row == row && head->col == col)
            return head;
    return NULL;
}

static void sparse_matr_append(sparse_matr_t **head, sparse_matr_t *row)
{
    if (!(*head))
    {
        *head = row;
        return;
    }

    sparse_matr_t *cur = *head;
    for (; cur->next; cur = cur->next);

    cur->next = row;
}

sparse_matr_t *sparse_matr_mul(const sparse_matr_t *matr1, const sparse_matr_t *matr2)
{
    sparse_matr_t *res = NULL;
    for (; matr1; sparse_matr_change_row(&matr1))
    {
        size_t cur_row_i = matr1->row; 
        const sparse_matr_t *cur_row = matr1; // строка 1-й матрицы
        sparse_matr_t *res_row = NULL;
        const sparse_matr_t *cur_node = matr2; 

        for (; cur_row && cur_row->row == cur_row_i; cur_row = cur_row->next)
        {            
            size_t cur_col_i = cur_row->col; // индекс столбца 1-й матрицы
            for (; cur_node && cur_node->row != cur_col_i; cur_node = cur_node->next);

            // ищем, что прибавить к элементу текущего столбца строки
            for (; cur_node && cur_node->row == cur_col_i; cur_node = cur_node->next)
            {
                sparse_matr_t *inc_node = sparse_matr_find(res_row, cur_row_i, cur_node->col);
                if (!inc_node)
                {
                    sparse_matr_t *res_node = sparse_matr_create_node(cur_row_i, cur_node->col, cur_node->data * cur_row->data); // check mem
                    sparse_matr_sorted_insert(&res_row, res_node);
                }
                else
                    inc_node->data += cur_node->data * cur_row->data;
            }
            // sparse_matr_fprint(stdout, res_row, INT_FORMAT);
        }
        sparse_matr_append(&res, res_row);
    }

    sparse_matr_del_zeros(&res);

    return res;
}


// head should not be NULL
size_t sparse_matr_find_row_with_max(const sparse_matr_t *head)
{
    size_t row = head->row;
    data_t max = head->data;
    
    for (head = head->next; head; head = head->next)
        if (head->data > max)
        {
            row = head->row;
            max = head->data;
        }
        
    return row;
}

void sparse_matr_del_row(sparse_matr_t **head, size_t row)
{
    sparse_matr_t *cur_node = *head;
    while (cur_node->next)
        if (cur_node->next->row == row)
        {
            sparse_matr_t *prev = cur_node->next;
            cur_node->next = cur_node->next->next;
            free(prev);
        }
        else
        {
            if (cur_node->next->row > row)
                cur_node->next->row--;
            cur_node = cur_node->next;
        }
               
    if ((*head)->row == row)
    {
        sparse_matr_t *prev = *head;
        *head = (*head)->next;
        free(prev);
    }
    else if ((*head)->row > row)
        (*head)->row--;
}


bool sparse_matr_equal(const sparse_matr_t *a, const sparse_matr_t *b)
{
    if (!a && !b)
        return true;

    for (; a && b; a = a->next, b = b->next)
        if (sparse_matr_cmp_indexes(a, b) || a->data != b->data)
            return false;

    return !a && !b;
}



