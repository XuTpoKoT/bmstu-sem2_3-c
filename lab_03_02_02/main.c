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

int digit_sum_odd(int num)
{
    num = abs(num);
    int sum = 0;
    for (; num > 0; num /= 10)
        sum += num % 10;
    return sum % 2 == 1;
}

size_t form_matr(int (*restrict src)[NMAX], size_t rows, size_t cols,
int (*restrict dst)[NMAX])
{
    size_t rows_dst = 0;
    for (size_t i = 0; i < rows; i++)
    {
        int count_odd = 0;
        for (size_t j = 0; j < cols && count_odd < 2; j++)
            if (digit_sum_odd(src[i][j]))
                count_odd++;
        if (count_odd == 2)
        {
            rows_dst++;
            for (size_t j = 0; j < cols; j++)
                dst[i + rows_dst - 1][j] = -1;
        }
        for (size_t j = 0; j < cols; j++)
            dst[i + rows_dst][j] = src[i][j];
    }   
    return rows_dst + rows;
}

int main(void)
{
    setbuf(stdout, NULL);
    int src[NMAX][NMAX];
    int dst[NMAX][NMAX];
    size_t rows, cols;
    size_t rows_dst;

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
    int rc = input(src, rows, cols);
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
    
    rows_dst = form_matr(src, rows, cols, dst);
    
    printf("New matrix:\n");
    output_matr(dst, rows_dst, cols);
    
    return EXIT_SUCCESS;
}
