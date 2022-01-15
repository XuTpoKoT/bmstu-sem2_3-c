#include "matr.h"

int matr_init(size_t rows, size_t cols, matr_t *matr)
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
            matr_free(matr);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

void matr_free(matr_t *a)
{
    if (!a || !a->data)
        return;

    for (size_t i = 0; i < a->rows; i++)
        free(a->data[i]);
    free(a->data);

    a->rows = 0;
    a->cols = 0;
}

int matr_scan(matr_t *a)
{
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (scanf("%d", &a->data[i][j]) != 1)
                return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void matr_print(matr_t *a)
{
    for (size_t i = 0; i < a->rows; i++)
    {
        for (size_t j = 0; j < a->cols; j++)
            printf("%d ", a->data[i][j]);
        printf("\n");
    }
}

int matr_copy(matr_t *dst, const matr_t *src)
{
    if (src->rows != dst->rows || src->cols != dst->cols)
        return EXIT_FAILURE;

    for (size_t i = 0; i < src->rows; i++)
        for (size_t j = 0; j < src->cols; j++)
            dst->data[i][j] = src->data[i][j];
    
    return EXIT_SUCCESS;
}

int matr_swap_cols(matr_t *a, size_t c1, size_t c2)
{
    if (a->cols <= c1 || a->cols <= c2)
        return EXIT_FAILURE;
    
    if (c1 == c2)
        return EXIT_SUCCESS;

    for (size_t i = 0; i < a->rows; i++)
    {
        int tmp =  a->data[i][c1];
        a->data[i][c1] = a->data[i][c2];
        a->data[i][c2] = tmp;
    }      
    
    return EXIT_SUCCESS;
}

int matr_col_with_min(matr_t *a)
{
    int min = a->data[0][0];
    size_t col = 0;

    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (a->data[i][j] < min)
            {
                min = a->data[i][j];
                col = j;
            }   
    
    return col;
}

int matr_col_with_max(matr_t *a)
{
    int max = a->data[0][0];
    size_t col = 0;

    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (a->data[i][j] > max)
            {
                max = a->data[i][j];
                col = j;
            }   
    
    return col;
}
