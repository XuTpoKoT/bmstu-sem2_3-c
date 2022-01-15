#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NMAX 128
#define MYMAX 10

#define ERROR_INVALID_ROWS 1
#define ERROR_INVALID_COLS 2
#define ERROR_INVALID_NUMBER 3
#define ERROR_NOT_ENOUGH_NUMBERS 4
#define ERROR_NO_NUMBERS_ENDS_5 5

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

int max_num_ends_5(int (*restrict matr)[NMAX], size_t size)
{
    int max = INT_MIN;
    for (size_t i = 1; i < size; i++)
        for (size_t j = size - i; j < size; j++)
            if (matr[i][j] > max && abs(matr[i][j]) % 10 == 5)
                max = matr[i][j];
    return max;
}

int main(void)
{
    setbuf(stdout, NULL);
    int matr[NMAX][NMAX];
    size_t rows, cols;

    printf("Input number of rows: ");
    if (scanf("%zu", &rows) != 1 || rows == 0 || rows > MYMAX)
    {
        printf("ERROR: Invalid number of rows!\n");
        return ERROR_INVALID_ROWS;
    }
    printf("Input number of columns: ");
    if (scanf("%zu", &cols) != 1 || cols == 0 || cols > MYMAX || cols != rows)
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

    int max_num = max_num_ends_5(matr, rows);
    
    if (max_num == INT_MIN)
    {
        printf("There are no numbers ends with five under side diagonal");
        return ERROR_NO_NUMBERS_ENDS_5;
    }
    
    printf("Answer: %d", max_num);

    return EXIT_SUCCESS;
}
