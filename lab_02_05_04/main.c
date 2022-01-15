#include <stdio.h>
#include <stdlib.h>

#define NMAX 1024
#define MYMAX 10

#define ERROR_INVALID_LEN 1
#define ERROR_INVALID_NUMBER 2
#define ERROR_NOT_ENOUGH_NUMBERS 3

int input(int *p_b, int *p_e)
{
    int rc;
    while (p_b < p_e)
        if ((rc = scanf("%d", p_b)) != 1)
        {
            if (rc == EOF)
                return ERROR_NOT_ENOUGH_NUMBERS;
            return ERROR_INVALID_NUMBER;
        }
        else
            p_b++;
    return EXIT_SUCCESS;
}

void output(int *p_b, int *p_e)
{
    for (int *p_cur = p_b; p_cur < p_e; p_cur++)
        printf("%d ", *p_cur);
}

int count_unique(int *p_b, int *p_e)
{
    int count = 0;
    for (int *p_cur = p_b; p_cur < p_e; p_cur++)
    {
        int flag = 1;
        for (int *p_tmp = p_b; p_tmp < p_cur && flag == 1; p_tmp++)
            if (*p_tmp == *p_cur)
                flag = 0;
        count += flag;
    }

    return count;
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
    int rc = input(arr, arr + len);
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

    printf("Count of unique elements = %d", count_unique(arr, arr + len));

    return EXIT_SUCCESS;
}