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

    matr->data = calloc(rows, sizeof(double*));
    if (!matr->data)
        return EXIT_FAILURE;

    matr->rows = rows;
    matr->cols = cols;
        
    for (size_t i = 0; i < rows; i++)
    {
        matr->data[i] = malloc(cols * sizeof(double));
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

    double **matr_buf = calloc(rows, sizeof(double*));
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
    double *row_buf;
    for (size_t i = 0; i < rows_min; i++)
    {
        row_buf = malloc(cols * sizeof(double));
        if (!row_buf)
        {
            for (size_t i = 0; i < rows; i++)
                free(matr_buf[i]);
            free(matr_buf);
            return EXIT_FAILURE;
        }
        memmove(row_buf, a->data[i], cols_min * sizeof(double));
        matr_buf[i] = row_buf;
    }

    // если нужно добавить строки
    if (rows_min < rows)
        for (size_t i = a->rows; i < rows; i++)
        {
            matr_buf[i] = malloc(cols * sizeof(double));
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


int cmp_double(const double a, const double b)
{
    const double eps = 1e-8;
    if (fabs(a - b) < eps)
        return 0;
    if (a - b > 0)
        return 1;   
    return -1;
}


int matrix_fread(FILE *f, matrix_t *a)
{
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (fscanf(f, "%lf", &a->data[i][j]) != 1)
                return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int matrix_read(matrix_t *a)
{
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (scanf("%lf", &a->data[i][j]) != 1)
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
        if (scanf("%zu%zu", &i, &j) != 2 || !cmp_double(a->data[i][j], 0.0))
            return EXIT_FAILURE;
        printf("Enter elem %zu: ", k);
        if (scanf("%lf", &a->data[i][j]) != 1)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void shuffle(double *arr, size_t nmemb)
{
    srand(time(NULL));

    for (size_t i = 0; i < nmemb; i++)
    {
        size_t j = rand() % (nmemb);

        double tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

int matrix_fill_random(matrix_t *a, const int percents)
{
    double *buf = malloc(a->rows * a->cols * sizeof(double));
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
            fprintf(f, "%.6lf ", a->data[i][j]);
        fprintf(f, "\n");
    }
}

void matrix_write(const matrix_t *a)
{
    for (size_t i = 0; i < a->rows; i++)
    {
        for (size_t j = 0; j < a->cols; j++)
            printf("%.6lf ", a->data[i][j]);
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
    double min = a->data[0][0];
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

int matrix_sum(const matrix_t *a, const matrix_t *b, matrix_t *sum)
{
    if (a->rows != b->rows || a->cols != b->cols)
        return EXIT_FAILURE;

    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            sum->data[i][j] = a->data[i][j] + b->data[i][j];
    return EXIT_SUCCESS;
}

double matrix_mul_row_on_col(const matrix_t *a, const matrix_t *b, const size_t row, const size_t col)
{
    assert(row < a->rows || col < b->cols || a->cols == b->rows);

    double sum = 0.0;

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
            a->data[i][j] = 0.0;

    for (size_t i = 0; i < a->rows; i++)
        a->data[i][i] = 1.0;
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


int matrix_minor(const matrix_t *src, matrix_t *dst, const size_t del_row, const size_t del_col)
{
    if (src->rows != src->cols || src->rows < 2 || dst->rows != src->rows - 1 || dst->cols != src->cols - 1)
        return EXIT_FAILURE;

    for (size_t i = 0; i < del_row; i++)
    {
        for (size_t j = 0; j < del_col; j++)
            dst->data[i][j] = src->data[i][j];
        for (size_t j = del_col + 1; j < src->cols; j++)
            dst->data[i][j - 1] = src->data[i][j];
    }

    for (size_t i = del_row + 1; i < src->rows; i++)
    {
        for (size_t j = 0; j < del_col; j++)
            dst->data[i - 1][j] = src->data[i][j];
        for (size_t j = del_col + 1; j < src->cols; j++)
            dst->data[i - 1][j - 1] = src->data[i][j];
    }
    return EXIT_SUCCESS;       
}

int matrix_det(const matrix_t *a, double *det_matr)
{
    if (a->rows != a->cols)
        return EXIT_FAILURE;

    if (a->rows == 1)
    {
        *det_matr = a->data[0][0];
        return EXIT_SUCCESS;
    }
         

    if (a->rows == 2)
    {
        *det_matr = a->data[0][0] * a->data[1][1] - a->data[0][1] * a->data[1][0];
        return EXIT_SUCCESS;
    }

    int sign = 1;
    *det_matr = 0.0;
    for (size_t i = 0; i < a->cols; i++)
    {
        double det_minor;
        matrix_t minor;
        matrix_create(a->rows - 1, a->cols - 1, &minor);
        matrix_minor(a, &minor, 0, i);
        matrix_det(&minor, &det_minor);
        matrix_free(&minor);
        *det_matr += a->data[0][i] * det_minor * sign;       
        sign = -sign;
    }

    return EXIT_SUCCESS;
}

bool matrix_equal(const matrix_t *a, const matrix_t *b)
{
    if (a->rows != b->rows || a->cols != b->cols)
        return false;

    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (cmp_double(a->data[i][j], b->data[i][j]))
                return false;
    return true;
}


