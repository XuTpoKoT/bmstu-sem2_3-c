#include <stdio.h>
#include <stdlib.h>

#define NMAX 1024
#define MYMAX 10

#define ERROR_INVALID_LEN 1
#define ERROR_INVALID_NUMBER 2
#define ERROR_NOT_ENOUGH_NUMBERS 3
#define ERROR_EMPTY_ARRAY 4

int input(int *restrict arr, size_t len)
{
    int rc;
    for (size_t i = 0; i < len; i++)
        if ((rc = scanf("%d", &arr[i])) != 1)
        {
            if (rc == EOF)
                return ERROR_NOT_ENOUGH_NUMBERS;
            return ERROR_INVALID_NUMBER;
        }
    return EXIT_SUCCESS;
}

void output(const int *restrict arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf("%d ", arr[i]);
}

int is_square(int num)
{
    if (num < 0)
        return 0;

    for (int i = 1; num > 0; i += 2)
        num -= i;

    return num == 0;
}

size_t delete_square_elements(int *restrict arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
        if (is_square(arr[i]))
        {
            for (size_t j = i; j < len - 1; j++)
                arr[j] = arr[j + 1];
            len--;
            i--;
        }
    return len;
}

int main(void)
{
    setbuf(stdout, NULL);
    int arr[NMAX];
    size_t len;

    printf("Input length of array: ");
    if (scanf("%zu", &len) != 1 || len == 0 || len > MYMAX)
    {
        printf("ERROR: Invalid lenght!\n");
        return ERROR_INVALID_LEN;
    }

    printf("Input elements: ");
    int rc = input(arr, len);
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


    len = delete_square_elements(arr, len);
    if (len == 0)
    {
        printf("New array is empty.\n");
        return ERROR_EMPTY_ARRAY;
    }

    printf("New array: \n");
    output(arr, len);

    return EXIT_SUCCESS;
}