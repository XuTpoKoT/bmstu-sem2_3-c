#ifndef MATR_H
#define MATR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int data_t;

typedef struct
{
    size_t rows;
    size_t cols;
    data_t **data;
} matr_t;

int matr_malloc(size_t rows, size_t cols, matr_t *matr);
void matr_free(matr_t *a);
void matr_free_two(matr_t *a, matr_t *b);
int matr_resize(matr_t *a, size_t rows, size_t cols);
int matr_fscan(FILE *f, matr_t *a);
int matr_scan(matr_t *a);
void matr_fprint(FILE *f, matr_t *a);
void matr_print(matr_t *a);

int matr_copy(matr_t *dst, const matr_t *src);
int matr_swap_cols(matr_t *a, size_t c1, size_t c2);

int matr_sum(const matr_t *a, const matr_t *b, matr_t *sum);
int matr_mul(const matr_t *a, const matr_t *b, matr_t *mul);
int matr_make_identity(matr_t *a);
int matr_pow(matr_t *a, unsigned int pow);
int matr_minor(const matr_t *src, matr_t *dst, size_t del_row, size_t del_col);
int matr_det(const matr_t *a, data_t *det_matr);

size_t matr_cnt_nonzero(const matr_t *a, int (*comparator)(const void*, const void*));
bool matr_equal(const matr_t *a, const matr_t *b, int (*comparator)(const void*, const void*));

#endif