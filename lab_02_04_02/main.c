#include <stdio.h>
#include <stdlib.h>

#define NMAX 1024
#define MYMAX 10

#define ERROR_EMPTY_ARRAY 1
#define ERROR_OVERFLOW 100

size_t input_end_attribute(int *restrict arr, size_t len_max)
{
    size_t len = 0;
    int elem;
    while (scanf("%d", &elem) == 1 && len < len_max + 1)
    {
        len++;
        if (len < len_max + 1)
            arr[len - 1] = elem;
    }

    return len;
}

void output(const int *restrict arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf("%d ", arr[i]);
}

void selection_sort(int *restrict arr, size_t len)
{
    for (size_t pos = 0; pos < len - 1; pos++)
    {
        size_t min_ind = pos;
        for (size_t i = pos + 1; i < len; i++)
            if (arr[i] < arr[min_ind])
                min_ind = i;
        int tmp = arr[pos];
        arr[pos] = arr[min_ind];
        arr[min_ind] = tmp;
    }
}

int main(void)
{
    setbuf(stdout, NULL);
    int arr[NMAX];

    printf("Input elements: ");
    size_t len = input_end_attribute(arr, MYMAX);

    if (len == 0)
    {
        printf("Array is empty.\n");
        return ERROR_EMPTY_ARRAY;
    }
    int rc = EXIT_SUCCESS;
    if (len == MYMAX + 1)
    {
        len--;
        rc = ERROR_OVERFLOW;
    }

    selection_sort(arr, len);

    printf("Sorted array: \n");
    output(arr, len);

    return rc;
}