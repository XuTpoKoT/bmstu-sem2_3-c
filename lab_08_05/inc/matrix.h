#ifndef MARTIX_H
#define MARTIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct 
{
    int **data;
    size_t rows;
    size_t cols;
} matrix_t;

#define ERR_WRONG_ARG_COUNT 101
#define ERR_WRONG_KEY       102
#define ERR_OPEN_FILE       103
#define ERR_READ            104
#define ERR_MALLOC          105

#define ERR_RESIZE 201
#define ERR_MUL 202

int matrix_create(const size_t rows, const size_t cols, matrix_t *matr);
void matrix_free(matrix_t *a);
void matrix_free_all(matrix_t *a, matrix_t *b);
int matrix_resize(matrix_t *a, const size_t rows, const size_t cols);

int matrix_fread(FILE *f, matrix_t *a);
int matrix_read(matrix_t *a);
int matrix_read_with_indexes(matrix_t *a, const size_t nonzero_memb);
int matrix_fill_random(matrix_t *a, const int percents);

void matrix_fwrite(FILE *f, const matrix_t *a);
void matrix_write(const matrix_t *a);

int matrix_copy(matrix_t *dst, const matrix_t *src);
void matrix_del_row(matrix_t *a, const size_t row);
void matrix_del_col(matrix_t *a, const size_t col);
void matrix_trunc_to_square(matrix_t *a);
int matrix_make_sym_size(matrix_t *a, matrix_t *b);

void matrix_find_min(const matrix_t *a, size_t *row, size_t *col);
int matrix_sum(const matrix_t *a, const matrix_t *b, matrix_t *sum);
int matrix_mul(const matrix_t *a, const matrix_t *b, matrix_t *mul);
int matrix_pow(matrix_t *a, unsigned int pow);

bool matrix_equal(const matrix_t *a, const matrix_t *b);

#endif
