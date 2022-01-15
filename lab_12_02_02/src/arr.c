#include "arr.h"

void arr_fill_with_fib(int *arr, size_t nmemb)
{
    int a = 1, b = 1;
    for (size_t i = 0; i < nmemb; i++)
    {
        arr[i] = a;
        a = b;
        b = a + arr[i];
    }
}

int arr_contains(int *arr, size_t nmemb, int elem)
{
    for (size_t i = 0; i < nmemb; i++)
        if (arr[i] == elem)
            return 1;
    return 0;
}

void arr_move_first_occurrance(int *dst, size_t *dst_memb, int *src, size_t src_memb)
{
    if (*dst_memb == 0)
    {
        int *tmp_arr = malloc(src_memb * sizeof(int));
        for (size_t i = 0; i < src_memb; i++)
            if (!arr_contains(tmp_arr, *dst_memb, src[i]))
                tmp_arr[(*dst_memb)++] = src[i];
        free(tmp_arr);
    } 
    else
    {
        *dst_memb = 0;
        for (size_t i = 0; i < src_memb; i++)
            if (!arr_contains(dst, *dst_memb, src[i]))
                dst[(*dst_memb)++] = src[i];
    }
}

