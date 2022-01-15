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

int same_digit(int num)
{
    num = abs(num);
    int last_digit = num % 10;
    while (num >= 10)
        num /= 10;
    return last_digit == num;
}

size_t copy_same_digit(const int *restrict arr_src, size_t len, int *restrict arr_dst)
{
    size_t len_dst = 0;
    for (size_t i = 0; i < len; i++)
        if (same_digit(arr_src[i]))
        {
            len_dst++;
            arr_dst[len_dst - 1] = arr_src[i];
        }
    return len_dst;
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

    int arr2[NMAX];
    size_t len2 = copy_same_digit(arr, len, arr2);
    if (len2 == 0)
    {
        printf("New array is empty.\n");
        return ERROR_EMPTY_ARRAY;
    }

    printf("New array: \n");
    output(arr2, len2);

    return EXIT_SUCCESS;
}