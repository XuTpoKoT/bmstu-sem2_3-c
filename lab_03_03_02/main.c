#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>

#define NMAX 128
#define MYMAX 10

#define ERROR_INVALID_ROWS 1
#define ERROR_INVALID_COLS 2
#define ERROR_INVALID_NUMBER 3
#define ERROR_NOT_ENOUGH_NUMBERS 4

int input(int (*restrict matr)[NMAX], size_t rows, size_t cols)
{
    int rc;
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if ((rc = scanf("%d", &matr[i][j])) != 1)
            {
                if (rc == EOF)
                    return ERROR_NOT_ENOUGH_NUMBERS;
                return ERROR_INVALID_NUMBER;
            }

    return EXIT_SUCCESS;
}

void output_matr(int (*restrict matr)[NMAX], size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
            printf("%d ", matr[i][j]);
        printf("\n");
    }
}

void output_arr(const int *restrict arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf("%d ", arr[i]);
}

void form_arr_multi(int (*restrict matr)[NMAX], size_t rows, size_t cols,
int *restrict arr)
{
    for (size_t i = 0; i < rows; i++)
    {
        int product = 1;
        for (size_t j = 0; j < cols; j++)
            product *= matr[i][j];
        arr[i] = product;
    }
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void selection_sort(int (*restrict matr)[NMAX], size_t rows, size_t cols,
int *restrict arr)
{
    for (size_t pos = 0; pos < rows; pos++)
    {
        size_t min_ind = pos;
        for (size_t i = pos + 1; i < rows; i++)
            if (arr[i] < arr[min_ind])
                min_ind = i;
        swap(arr + pos, arr + min_ind);
        for (size_t i = 0; i < cols; i++)
            swap(*(matr + pos) + i, *(matr + min_ind) + i);
    }
}

int main(void)
{
    setbuf(stdout, NULL);
    int matr[NMAX][NMAX];
    int arr_multi[NMAX];
    size_t rows, cols;

    printf("Input number of rows: ");
    if (scanf("%zu", &rows) != 1 || rows == 0 || rows > MYMAX)
    {
        printf("ERROR: Invalid number of rows!\n");
        return ERROR_INVALID_ROWS;
    }
    printf("Input number of columns: ");
    if (scanf("%zu", &cols) != 1 || cols == 0 || cols > MYMAX)
    {
        printf("ERROR: Invalid number of columns!\n");
        return ERROR_INVALID_COLS;
    }
    printf("Input elements:\n");
    int rc = input(matr, rows, cols);
    if (rc == ERROR_NOT_ENOUGH_NUMBERS)
    {
        printf("ERROR: NOT ENOUGH NUMBERS!");
        return rc;
    }
    if (rc == ERROR_INVALID_NUMBER)
    {
        printf("ERROR: INVALID NUMBER!");
        return rc;
    }

    form_arr_multi(matr, rows, cols, arr_multi);

    selection_sort(matr, rows, cols, arr_multi);

    printf("New matrix:\n");
    output_matr(matr, rows, cols);

    return EXIT_SUCCESS;
}
