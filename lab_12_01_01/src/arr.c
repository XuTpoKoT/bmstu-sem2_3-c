#include "arr.h"

#include <string.h>

size_t cnt_elems(FILE *f)
{
    long pos = ftell(f);
    if (pos < 0)
        return 0;
    if (fseek(f, 0L, SEEK_SET))
        return 0;

    size_t count_elems = 0;
    int num;
    while (fscanf(f, "%d", &num) == 1)
        ++count_elems;

    if (!feof(f))
    {
        fseek(f, pos, SEEK_SET);
        return 0;
    }
        
    if (fseek(f, pos, SEEK_SET))
        return 0;
    	
    return count_elems;
}

int read_arr(FILE *f, int *pb, int *pe)
{
    int *pcur;
    for (pcur = pb; pcur != pe && fscanf(f, "%d", pcur) == 1; ++pcur);

    return pcur != pe;
}

int write_arr(FILE *f, const int *pb, const int *pe)
{
    int *pcur;
    for (pcur = (int*)pb; pcur != (int*)pe && fprintf(f, "%d ", *pcur); ++pcur);

    return pcur != pe;
}

size_t last_neg_index(const int *pb, const int *pe)
{
    int *pcur;
    for (pcur = (int*)pe - 1; pcur != (int*)pb; --pcur)
        if (*pcur < 0)
            return pcur - pb;

    if (*pb < 0)
        return 0;

    return pe - pb;
}

int key(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst)
{
    if (pb_src == NULL || pe_src == NULL || pb_src >= pe_src || pb_dst == NULL || pe_dst == NULL || pb_dst >= pe_dst)
        return EXIT_FAILURE;

    for (; pb_dst != pe_dst;)
        *pb_dst++ = *pb_src++;

    return EXIT_SUCCESS;
}

int compare_int(const void *p, const void *q)
{
    const int *a = p;
    const int *b = q;
    return *a - *b;
}

int compare_double(const void *p, const void *q)
{
    const double *a = p;
    const double *b = q;
    if (*a > *b)
        return 1;
    if (*a < *b)
        return -1;
    return 0;
}

void swap(char *a, char *b, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        char tmp = *(a + i);
        *(a + i) = *(b + i);
        *(b + i) = tmp;
    }  
}

void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*))
{
    if (base == NULL || nmemb == 0)
        return;

    size_t left = 0, right = nmemb - 1;
    size_t control = left;
    char *arr = (char*)base;

    while (right > left)
    {
        for (size_t i = left; i < right; ++i)
            if (compar(arr + i * size, arr + (i + 1) * size) > 0)
            {
                swap(arr + i * size, arr + (i + 1) * size, size);
                control = i;
            }
        right = control;
        
        for (size_t i = right; i > left; --i)
            if (compar(arr + i * size, arr + (i - 1) * size) < 0)
            {
                swap(arr + i * size, arr + (i - 1) * size, size);
                control = i;
            }
        left = control;      
    }
}
