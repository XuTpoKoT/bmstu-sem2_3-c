#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>

#define NMAX 128
#define MYMAX 10

#define ERROR_INVALID_ROWS 1
#define ERROR_INVALID_COLS 2
#define ERROR_INVALID_NUMBER 3
#define ERROR_NOT_ENOUGH_NUMBERS 4
#define ERROR_NO_PRIME_NUMBERS 5

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

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int is_prime(int num)
{
    if (num == 2 || num == 3)
        return 1;
    if (num <= 1 || num % 2 == 0 || num % 3 == 0)
        return 0;
    for (int i = 5; i <= num / i; i += 2)
        if (num % i == 0)
            return 0;
    return 1;
}

size_t form_arr_prime_nums(int (*restrict matr)[NMAX], size_t rows, size_t cols,
int *restrict arr_prime, int *restrict arr_index)
{
    size_t len = 0;
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if (is_prime(matr[i][j]))
            {
                len++;
                arr_prime[len - 1] = matr[i][j];
                arr_index[len - 1] = i * cols + j;
            }
    return len;
}

void reverse(int *restrict arr, size_t len)
{
    for (size_t i = 0; i < len / 2; i++)
        swap(arr + i, arr + len - 1 - i);
}

void replace_nums(int (*restrict matr)[NMAX], size_t cols,
int *restrict arr_prime, size_t len, int *restrict arr_index)
{
    for (size_t i = 0; i < len; i++)
        matr[arr_index[i] / cols][arr_index[i] % cols] = arr_prime[i];
}

int main(void)
{
    setbuf(stdout, NULL);
    int matr[NMAX][NMAX];
    int arr_prime[NMAX];
    int arr_index[NMAX];
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

    size_t len = form_arr_prime_nums(matr, rows, cols, arr_prime, arr_index);
    
    if (len == 0)
    {
        printf("There are no prime numbers in matrix.");
        return ERROR_NO_PRIME_NUMBERS;
    }
    
    reverse(arr_prime, len);
    
    replace_nums(matr, cols, arr_prime, len, arr_index);

    printf("New matrix:\n");
    output_matr(matr, rows, cols);

    return EXIT_SUCCESS;
}
