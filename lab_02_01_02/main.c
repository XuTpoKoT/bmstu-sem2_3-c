#include <stdio.h>
#include <stdlib.h>

#define NMAX 1024
#define MYMAX 10

#define ERROR_INVALID_LEN 1
#define ERROR_INVALID_NUMBER 2
#define ERROR_NOT_ENOUGH_NUMBERS 3
#define ERROR_NO_NEGATIVE_ELEMENTS 4

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

double avg_neg(const int *restrict arr, size_t len)
{
    double avg_neg = 0.0;
    int count_neg = 0;
    for (size_t i = 0; i < len; i++)
        if (arr[i] < 0)
        {
            count_neg++;
            avg_neg += arr[i];
        }

    if (count_neg == 0)
        return 1.0;
    return avg_neg / count_neg;
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

    double avg = avg_neg(arr, len);
    if (avg > 0)
    {
        printf("There are no negative elements in array.\n");
        return ERROR_NO_NEGATIVE_ELEMENTS;
    }

    printf("Average of negative elements = %.6lf", avg);

    return EXIT_SUCCESS;
}
