#include "matrix.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <assert.h>

int matrix_create(const size_t rows, const size_t cols, matrix_t *matr)
{
    if (rows == 0 || cols == 0)
        return EXIT_FAILURE;

    matr->data = calloc(rows, sizeof(int*));
    if (!matr->data)
        return EXIT_FAILURE;

    matr->rows = rows;
    matr->cols = cols;
        
    for (size_t i = 0; i < rows; i++)
    {
        matr->data[i] = malloc(cols * sizeof(int));
        if (!matr->data[i])
        {
            matrix_free(matr);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

void matrix_free(matrix_t *a)
{
    if (!a || !a->data)
        return;

    for (size_t i = 0; i < a->rows; i++)
        free(a->data[i]);
    free(a->data);

    a->rows = 0;
    a->cols = 0;
}

void matrix_free_all(matrix_t *a, matrix_t *b)
{
    matrix_free(a);
    matrix_free(b);
}

int matrix_resize(matrix_t *a, const size_t rows, const size_t cols)
{
    if (rows == 0 || cols == 0)
        return EXIT_FAILURE;

    int **matr_buf = calloc(rows, sizeof(int*));
    if (!matr_buf)
        return EXIT_FAILURE;

    size_t rows_min, cols_min;
    if (rows < a->rows)
        rows_min = rows;
    else
        rows_min = a->rows;

    if (cols < a->cols)
        cols_min = cols;
    else 
        cols_min = a->cols;

    // копируем в буфер
    int *row_buf;
    for (size_t i = 0; i < rows_min; i++)
    {
        row_buf = malloc(cols * sizeof(int));
        if (!row_buf)
        {
            for (size_t i = 0; i < rows; i++)
                free(matr_buf[i]);
            free(matr_buf);
            return EXIT_FAILURE;
        }
        memmove(row_buf, a->data[i], cols_min * sizeof(int));
        matr_buf[i] = row_buf;
    }

    // если нужно добавить строки
    if (rows_min < rows)
        for (size_t i = a->rows; i < rows; i++)
        {
            matr_buf[i] = malloc(cols * sizeof(int));
            if (!matr_buf[i])
            {
                for (size_t i = 0; i < rows; i++)
                    free(matr_buf[i]);
                free(matr_buf);
                return EXIT_FAILURE;
            }
        }     
    
    matrix_free(a);
    a->data = matr_buf;
    a->rows = rows;
    a->cols = cols;

    return EXIT_SUCCESS;
}


int matrix_fread(FILE *f, matrix_t *a)
{
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (fscanf(f, "%d", &a->data[i][j]) != 1)
                return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int matrix_read(matrix_t *a)
{
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (scanf("%d", &a->data[i][j]) != 1)
                return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int matrix_read_with_indexes(matrix_t *a, const size_t nonzero_memb)
{
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            a->data[i][j] = 0;

    size_t i, j;
    for (size_t k = 0; k < nonzero_memb; k++)
    {
        printf("Enter indexes of elem %zu: ", k);
        if (scanf("%zu%zu", &i, &j) != 2 || a->data[i][j] != 0)
            return EXIT_FAILURE;
        printf("Enter elem %zu: ", k);
        if (scanf("%d", &a->data[i][j]) != 1)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void shuffle(int *arr, size_t nmemb)
{
    srand(time(NULL));

    for (size_t i = 0; i < nmemb; i++)
    {
        size_t j = rand() % (nmemb);

        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

int matrix_fill_random(matrix_t *a, const int percents)
{
    int *buf = malloc(a->rows * a->cols * sizeof(int));
    if (!buf)
        return EXIT_FAILURE;

    size_t nmemb = a->rows * a->cols * percents / 100;
    for (size_t i = 0; i < nmemb; i++)
        buf[i] = rand() % 100;
    shuffle(buf, nmemb);
    size_t i, j, k = 0;

    for (i = 0; i < a->rows; i++)
        for (j = 0; j < a->cols; j++)
            if (k < nmemb)
                a->data[i][j] = buf[k++];
            else
                a->data[i][j] = 0;
    free(buf);
    return EXIT_SUCCESS;
}


void matrix_fwrite(FILE *f, const matrix_t *a)
{
    fprintf(f, "%zu %zu\n", a->rows, a->cols);
    for (size_t i = 0; i < a->rows; i++)
    {
        for (size_t j = 0; j < a->cols; j++)
            fprintf(f, "%d ", a->data[i][j]);
        printf("\n");
    }
}

void matrix_write(const matrix_t *a)
{
    for (size_t i = 0; i < a->rows; i++)
    {
        for (size_t j = 0; j < a->cols; j++)
            printf("%d ", a->data[i][j]);
        printf("\n");
    }
}


int matrix_copy(matrix_t *dst, const matrix_t *src)
{
    if (src->rows != dst->rows || src->cols != dst->cols)
        return EXIT_FAILURE;

    for (size_t i = 0; i < src->rows; i++)
        for (size_t j = 0; j < src->cols; j++)
            dst->data[i][j] = src->data[i][j];
    
    return EXIT_SUCCESS;
}


void matrix_find_min(const matrix_t *a, size_t *row, size_t *col)
{
    int min = a->data[0][0];
    *row = 0;
    *col = 0;
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (a->data[i][j] < min)
            {
                min = a->data[i][j];
                *row = i;
                *col = j;
            }             
}

int matrix_geom_avg_col(const matrix_t *a, const size_t rows, const size_t col)
{
    double avg = 1;
    for (size_t i = 0; i < rows; i++)
        avg *= abs(a->data[i][col]);
    avg = pow(avg + 1e-8, 1.0 / rows);
    return (int)floor(avg);
}

void matrix_del_row(matrix_t *a, const size_t row)
{
    if (row >= a->rows)
        return;

    free(a->data[row]);
    if (a->rows == 1)
        return;

    for (size_t i = row; i < a->rows - 1; i++)
        a->data[i] = a->data[i + 1];
    
    a->data[--a->rows] = NULL;
}

void matrix_del_col(matrix_t *a, const size_t col)
{
    if (col >= a->cols || a->cols == 0)
        return;

    for (size_t i = 0; i < a->rows; i++)
    {
        if (a->cols != 1)
            for (size_t j = col; j < a->cols - 1; j++)
                a->data[i][j] = a->data[i][j + 1];

        int *p = realloc(a->data[i], sizeof(int) * (a->cols - 1));
        if (!p)
            return;
        a->data[i] = p;
    }
    a->cols--;
}

void matrix_trunc_to_square(matrix_t *a)
{
    size_t row_min, col_min;

    while (a->rows != a->cols)
    {
        matrix_find_min(a, &row_min, &col_min);
        if (a->rows > a->cols)           
            matrix_del_row(a, row_min);
        else
            matrix_del_col(a, col_min);
    }
}

void matrix_fill_row(matrix_t *a, const size_t cols, const size_t row)
{
    if (row >= a->rows)
        return;

    for (size_t i = 0; i < cols; i++)
        a->data[row][i] = matrix_geom_avg_col(a, row, i);
}

int arr_max(const int *arr, const size_t nmemb)
{
    int max = arr[0];
    for (size_t i = 0; i < nmemb; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void matrix_fill_col(matrix_t *a, const size_t col)
{
    if (col >= a->cols)
        return;

    for (size_t i = 0; i < a->rows; i++)
        a->data[i][col] = arr_max(a->data[i], col);
}

int matrix_make_sym_size(matrix_t *a, matrix_t *b)
{
    if (a->rows != a->cols || b->rows != b->cols)
        return EXIT_FAILURE;
    
    if (a->rows == b->rows)
        return EXIT_SUCCESS;

    if (a->rows < b->rows)
    {
        size_t rows_old = a->rows, cols_old = a->cols;
        if (matrix_resize(a, b->rows, b->cols))
            return EXIT_FAILURE;
        for (size_t i = rows_old; i < a->rows; i++)
            matrix_fill_row(a, cols_old, i);
        for (size_t i = cols_old; i < a->cols; i++)
            matrix_fill_col(a, i);
    }
    else
    {
        size_t rows_old = b->rows, cols_old = b->cols;
        if (matrix_resize(b, a->rows, a->cols))
            return EXIT_FAILURE;
        for (size_t i = rows_old; i < b->rows; i++)
            matrix_fill_row(b, cols_old, i);
        for (size_t i = cols_old; i < b->cols; i++)
            matrix_fill_col(b, i);
    }    
    return EXIT_SUCCESS;
}



int matrix_sum(const matrix_t *a, const matrix_t *b, matrix_t *sum)
{
    if (a->rows != b->rows || a->cols != b->cols)
        return EXIT_FAILURE;

    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            sum->data[i][j] = a->data[i][j] + b->data[i][j];
    return EXIT_SUCCESS;
}

int matrix_mul_row_on_col(const matrix_t *a, const matrix_t *b, const size_t row, const size_t col)
{
    assert(row < a->rows || col < b->cols || a->cols == b->rows);

    int sum = 0;

    for (size_t i = 0; i < a->cols; i++)
        sum += a->data[row][i] * b->data[i][col];

    return sum;
}

int matrix_mul(const matrix_t *a, const matrix_t *b, matrix_t *mul)
{
    if (a->cols != b->rows || mul->rows != a->rows || mul->cols != b->cols)
        return EXIT_FAILURE;
    
    for (size_t i = 0; i < mul->rows; i++)
        for (size_t j = 0; j < mul->cols; j++)
            mul->data[i][j] = matrix_mul_row_on_col(a, b, i, j);

    return EXIT_SUCCESS;
}

void matrix_make_identity(matrix_t *a)
{
    assert(a->rows == a->cols);

    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            a->data[i][j] = 0;

    for (size_t i = 0; i < a->rows; i++)
        a->data[i][i] = 1;
}

int matrix_pow(matrix_t *a, unsigned int pow)
{
    if (a->rows != a->cols)
        return EXIT_FAILURE;

    if (pow == 0)
    {
        matrix_make_identity(a);
        return EXIT_SUCCESS;
    }
    
    matrix_t old_a, buf;
    if (matrix_create(a->rows, a->cols, &buf))
        return EXIT_FAILURE;

    if (matrix_create(a->rows, a->cols, &old_a))
    {
        matrix_free(&buf);
        return EXIT_FAILURE;
    }

    matrix_copy(&old_a, a);
    
    for (unsigned int i = 1; i < pow; i++)
    {
        if (matrix_mul(a, &old_a, &buf))
        {
            matrix_free_all(&buf, &old_a);
            return EXIT_FAILURE;
        }
        matrix_copy(a, &buf);
    }

    matrix_free_all(&buf, &old_a);

    return EXIT_SUCCESS;
}


bool matrix_equal(const matrix_t *a, const matrix_t *b)
{
    if (a->rows != b->rows || a->cols != b->cols)
        return false;

    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (a->data[i][j] != b->data[i][j])
                return false;
    return true;
}


size_t matrix_cnt_nonzero(const matrix_t *a)
{
    size_t cnt = 0;
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (a->data[i][j] != 0)
                cnt++;
    return cnt;
}


