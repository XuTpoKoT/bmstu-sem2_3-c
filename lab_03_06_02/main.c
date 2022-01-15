#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>

#define NMAX 128
#define MYMAX 10

#define ERROR_INVALID_ROWS 1
#define ERROR_INVALID_COLS 2

void form_matr(int (*restrict matr)[NMAX], size_t rows, size_t cols)
{
    int dif = rows * 2 - 1;
    for (size_t i = 0; i < rows; i++)
    {
        matr[i][0] = rows * cols - rows + 1 + i;
        for (size_t j = 1; j < cols; j++)
            if (j % 2 == 1)
                matr[i][j] = matr[i][j - 1] - dif + 2 * (rows - 1 - i);
            else 
                matr[i][j] = matr[i][j - 1] - dif + 2 * i;
    }
}

void output(int (*restrict matr)[NMAX], size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
            printf("%d ", matr[i][j]);
        printf("\n");
    }
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
    if (scanf("%zu", &cols) != 1 || cols == 0 || cols > MYMAX)
    {
        printf("ERROR: Invalid number of columns!\n");
        return ERROR_INVALID_COLS;
    }
    
    form_matr(matr, rows, cols);

    printf("Matrix:\n");
    output(matr, rows, cols);

    return EXIT_SUCCESS;
}
