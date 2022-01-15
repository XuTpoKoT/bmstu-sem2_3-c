#ifndef ARR_H
#define ARR_H

#include <stdio.h>
#include <stdlib.h>

size_t cnt_elems(FILE *f);
int read_arr(FILE *f, const int *pb, const int *pe);
int write_arr(FILE *f, const int *pb, const int *pe);
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
int compare_int(const void *p, const void *q);
int compare_double(const void *p, const void *q);
void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

#endif
