#include <stdio.h>
#include <stdlib.h>

#include "matr_arr.h"

int main(void)
{
    size_t n, rows, cols;
    matr_t *arr;

    if (scanf("%zu", &n) != 1 || n == 0)
        return EXIT_FAILURE;

    if (matr_arr_init(n * 2, &arr))
        return EXIT_FAILURE;

    for (size_t i = 0; i < 2 * n; i += 2)
    {
        if (scanf("%zu%zu", &rows, &cols) != 2)
        {
            for (size_t j = 0; j < i; j += 2)
                matr_free(&arr[j]);
            free(arr);
            return EXIT_FAILURE;
        }
        if (matr_init(rows, cols, &arr[i]))
        {
            for (size_t j = 0; j < i; j += 2)
                matr_free(&arr[j]);
            free(arr);
            return EXIT_FAILURE;
        }
        if (matr_scan(&arr[i]))
        {
            for (size_t j = 0; j <= i; j += 2)
                matr_free(&arr[j]);
            free(arr);
            return EXIT_FAILURE;
        }
        //matr_print(&arr[i + 1]);
    }

    for (size_t i = 0; i < 2 * n; i += 2)
    {
        matr_copy(&arr[i + 1], &arr[i]);
        //matr_print(&arr[i + 1]);
        size_t col_min = matr_col_with_min(&arr[i + 1]);
        size_t col_max = matr_col_with_max(&arr[i + 1]);
        matr_swap_cols(&arr[i + 1], col_min, col_max);
    }

    for (size_t i = 0; i < n * 2; i++)
        matr_print(&arr[i]);

    for (size_t i = 0; i < n * 2; i++)
        matr_free(&arr[i]);
    free(arr);

    return EXIT_SUCCESS;
}
