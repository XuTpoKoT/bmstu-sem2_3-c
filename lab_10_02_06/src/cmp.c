#include "cmp.h"

int cmp_int(const void *p, const void *q)
{
    const int *a = p;
    const int *b = q;
    return *a - *b;
}

int cmp_double(const void *p, const void *q)
{
    const double *a = p;
    const double *b = q;
    if (*a > *b)
        return 1;
    if (*a < *b)
        return -1;
    return 0;
}
