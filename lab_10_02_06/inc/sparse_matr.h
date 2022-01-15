#ifndef SPARSE_MATR_H
#define SPARSE_MATR_H

#include <stdlib.h>
#include <stdbool.h>

#include "matr.h"

#define INT_FORMAT "%zu %zu %d "

typedef struct sparse_matr_t
{
    size_t row;
    size_t col;
    data_t data;
    struct sparse_matr_t *next;
} sparse_matr_t;

sparse_matr_t *sparse_matr_create_node(size_t row, size_t col, data_t data);
void sparse_matr_free(sparse_matr_t **head);
void sparse_matr_free_two(sparse_matr_t **a, sparse_matr_t **b);

sparse_matr_t *matr_to_sparse_matr(const matr_t *matr);
void sparse_matr_fprint(FILE *f, const sparse_matr_t *head, const char *format);

sparse_matr_t *sparse_matr_sum(const sparse_matr_t *matr1, const sparse_matr_t *matr2);
sparse_matr_t *sparse_matr_transpose(const sparse_matr_t *head);
sparse_matr_t *sparse_matr_mul(const sparse_matr_t *matr1, const sparse_matr_t *matr2);

size_t sparse_matr_find_row_with_max(const sparse_matr_t *head);
void sparse_matr_del_row(sparse_matr_t **head, size_t row);
bool sparse_matr_equal(const sparse_matr_t *a, const sparse_matr_t *b);

#endif