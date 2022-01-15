#include <string.h>
#include <assert.h>

#include "matr.h"

int matr_malloc(size_t rows, size_t cols, matr_t *matr)
{
    if (rows == 0 || cols == 0)
        return EXIT_FAILURE;

    matr->data = calloc(rows, sizeof(data_t*));
    if (!matr->data)
        return EXIT_FAILURE;

    matr->rows = rows;
    matr->cols = cols;
        
    for (size_t i = 0; i < rows; i++)
    {
        matr->data[i] = malloc(cols * sizeof(data_t));
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

void matr_free_two(matr_t *a, matr_t *b)
{
    matr_free(a);
    matr_free(b);
}

int matr_resize(matr_t *a, size_t rows, size_t cols)
{
    if (rows == 0 || cols == 0)
        return EXIT_FAILURE;

    data_t **matr_buf = calloc(rows, sizeof(data_t*));
    if (!matr_buf)
        return EXIT_FAILURE;

    size_t rows_min, cols_min;
    rows_min = a->rows;
    if (rows < a->rows)
        rows_min = rows;
        
    cols_min = a->cols;
    if (cols < a->cols)
        cols_min = cols;

    // копируем в буфер
    data_t *row_buf;
    for (size_t i = 0; i < rows_min; i++)
    {
        row_buf = malloc(cols * sizeof(data_t));
        if (!row_buf)
        {
            for (size_t i = 0; i < rows; i++)
                free(matr_buf[i]);
            free(matr_buf);
            return EXIT_FAILURE;
        }
        memmove(row_buf, a->data[i], cols_min * sizeof(data_t));
        matr_buf[i] = row_buf;
    }

    // если нужно добавить строки
    if (rows_min < rows)
        for (size_t i = a->rows; i < rows; i++)
        {
            matr_buf[i] = malloc(cols * sizeof(data_t));
            if (!matr_buf[i])
            {
                for (size_t i = 0; i < rows; i++)
                    free(matr_buf[i]);
                free(matr_buf);
                return EXIT_FAILURE;
            }
        }     
    
    matr_free(a);
    a->data = matr_buf;
    a->rows = rows;
    a->cols = cols;

    return EXIT_SUCCESS;
}


int matr_fscan(FILE *f, matr_t *a)
{
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (fscanf(f, "%d", &a->data[i][j]) != 1)
                return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int matr_scan(matr_t *a)
{
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (scanf("%d", &a->data[i][j]) != 1)
                return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void matr_fprint(FILE *f, matr_t *a)
{
    for (size_t i = 0; i < a->rows; i++)
    {
        for (size_t j = 0; j < a->cols; j++)
            fprintf(f, "%d ", a->data[i][j]);
        fprintf(f, "\n");
    }
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
        data_t tmp = a->data[i][c1];
        a->data[i][c1] = a->data[i][c2];
        a->data[i][c2] = tmp;
    }      
    
    return EXIT_SUCCESS;
}


size_t matr_col_with_min(matr_t *a, int (*comparator)(const void*, const void*))
{
    data_t min = a->data[0][0];
    size_t col = 0;

    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (comparator(&a->data[i][j], &min) < 0)
            {
                min = a->data[i][j];
                col = j;
            }   
    
    return col;
}

size_t matr_col_with_max(matr_t *a, int (*comparator)(const void*, const void*))
{
    data_t max = a->data[0][0];
    size_t col = 0;

    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (comparator(&a->data[i][j], &max) > 0)
            {
                max = a->data[i][j];
                col = j;
            }   
    
    return col;
}


int matr_sum(const matr_t *a, const matr_t *b, matr_t *sum)
{
    if (a->rows != b->rows || a->cols != b->cols)
        return EXIT_FAILURE;

    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            sum->data[i][j] = a->data[i][j] + b->data[i][j];
    return EXIT_SUCCESS;
}

static data_t matr_mul_row_on_col(const matr_t *a, const matr_t *b, size_t row, size_t col)
{
    assert(row < a->rows || col < b->cols || a->cols == b->rows);

    data_t sum = 0.0;

    for (size_t i = 0; i < a->cols; i++)
        sum += a->data[row][i] * b->data[i][col];

    return sum;
}

int matr_mul(const matr_t *a, const matr_t *b, matr_t *mul)
{
    if (a->cols != b->rows || mul->rows != a->rows || mul->cols != b->cols)
        return EXIT_FAILURE;
    
    for (size_t i = 0; i < mul->rows; i++)
        for (size_t j = 0; j < mul->cols; j++)
            mul->data[i][j] = matr_mul_row_on_col(a, b, i, j);

    return EXIT_SUCCESS;
}

int matr_make_identity(matr_t *a)
{
    if (a->rows != a->cols)
        return EXIT_FAILURE;

    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            a->data[i][j] = 0;

    for (size_t i = 0; i < a->rows; i++)
        a->data[i][i] = 1;

    return EXIT_SUCCESS;
}

int matr_pow(matr_t *a, unsigned int pow)
{
    if (a->rows != a->cols)
        return EXIT_FAILURE;

    if (pow == 0)
    {
        matr_make_identity(a);
        return EXIT_SUCCESS;
    }
    
    matr_t old_a, buf;
    if (matr_malloc(a->rows, a->cols, &buf))
        return EXIT_FAILURE;

    if (matr_malloc(a->rows, a->cols, &old_a))
    {
        matr_free(&buf);
        return EXIT_FAILURE;
    }

    matr_copy(&old_a, a);
    
    for (unsigned int i = 1; i < pow; i++)
    {
        if (matr_mul(a, &old_a, &buf))
        {
            matr_free_two(&buf, &old_a);
            return EXIT_FAILURE;
        }
        matr_copy(a, &buf);
    }

    matr_free_two(&buf, &old_a);

    return EXIT_SUCCESS;
}

int matr_minor(const matr_t *src, matr_t *dst, size_t del_row, size_t del_col)
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

int matr_det(const matr_t *a, data_t *det_matr)
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
        data_t det_minor;
        matr_t minor;
        matr_malloc(a->rows - 1, a->cols - 1, &minor);
        matr_minor(a, &minor, 0, i);
        matr_det(&minor, &det_minor);
        matr_free(&minor);
        *det_matr += a->data[0][i] * det_minor * sign;       
        sign = -sign;
    }

    return EXIT_SUCCESS;
}


size_t matr_cnt_nonzero(const matr_t *a, int (*comparator)(const void*, const void*))
{
    const int zero = 0;
    size_t cnt = 0;
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (comparator(&a->data[i][j], &zero))
                cnt++;
    return cnt;
}


bool matr_equal(const matr_t *a, const matr_t *b, int (*comparator)(const void*, const void*))
{
    if (a->rows != b->rows || a->cols != b->cols)
        return false;

    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            if (comparator(&a->data[i][j], &b->data[i][j]))
                return false;
    return true;
}


