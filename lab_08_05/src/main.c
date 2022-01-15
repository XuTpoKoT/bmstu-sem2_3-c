#include "matrix.h"

#include <string.h>

int main(void)
{
    long long buf_rows, buf_cols;
    size_t n, m;
    matrix_t a;
    size_t p, q;
    matrix_t b;

    // чтение 1-й матрицы
    if (scanf("%lld%lld", &buf_rows, &buf_cols) != 2 || buf_rows <= 0 || buf_cols <= 0)
        return ERR_READ;
    n = buf_rows;
    m = buf_cols;

    if (matrix_create(n, m, &a))
        return ERR_MALLOC;

    if (matrix_read(&a))
    {
        matrix_free(&a);
        return ERR_READ;
    }
    
    // чтение 2-й матрицы
    if (scanf("%lld%lld", &buf_rows, &buf_cols) != 2 || buf_rows <= 0 || buf_cols <= 0)
    {
        matrix_free(&a);
        return ERR_READ;
    }
    p = buf_rows;
    q = buf_cols;

    if (matrix_create(p, q, &b))
    {
        matrix_free(&a);
        return ERR_MALLOC;
    }

    if (matrix_read(&b))
    {
        matrix_free_all(&a, &b);
        return ERR_READ;
    }

    // приведение матриц к одному размеру
    matrix_trunc_to_square(&a);
    matrix_trunc_to_square(&b);

    if (matrix_make_sym_size(&a, &b))
    {
        matrix_free_all(&a, &b);
        return ERR_READ;
    }

    // возведение в степень и умножение
    int x, y;
    if (scanf("%d%d", &x, &y) != 2 || x < 0 || y < 0)
    {
        matrix_free_all(&a, &b);
        return ERR_READ;
    }

    if (matrix_pow(&a, x))
    {
        matrix_free_all(&a, &b);
        return ERR_MUL;
    }

    if (matrix_pow(&b, y))
    {
        matrix_free_all(&a, &b);
        return ERR_MUL;
    }

    matrix_t mul;
    if (matrix_create(a.rows, b.cols, &mul))
    {
        matrix_free_all(&a, &b);
        return ERR_MALLOC;
    }
    if (matrix_mul(&a, &b, &mul))
    {
        matrix_free(&mul);
        matrix_free_all(&a, &b);
        return ERR_MUL;
    }

    // вывод результата
    matrix_write(&mul);
    
    matrix_free(&mul);
    matrix_free_all(&a, &b);

    return EXIT_SUCCESS;
}

