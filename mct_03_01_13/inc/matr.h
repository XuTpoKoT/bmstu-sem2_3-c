#ifndef MATR_H
#define MATR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    size_t rows;
    size_t cols;
    int **data;
} matr_t;

int matr_init(size_t rows, size_t cols, matr_t *matr);
void matr_free(matr_t *a);
int matr_scan(matr_t *a);
void matr_print(matr_t *a);

int matr_copy(matr_t *dst, const matr_t *src);
int matr_swap_cols(matr_t *a, size_t c1, size_t c2);
int matr_col_with_min(matr_t *a);
int matr_col_with_max(matr_t *a);

#endif