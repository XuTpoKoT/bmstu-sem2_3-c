#ifndef ARR_H
#define ARR_H

#include <stdio.h>
#include <stdlib.h>

#define ERR_ARR_FILTER 201
#define ERR_ARR_READ   202
#define ERR_ARR_WRITE  203

#define ERR_ARR_NOT_FOUND_LIB  209
#define ERR_ARR_NOT_FOUND_FUNC_CNT_ELEMS  210
#define ERR_ARR_NOT_FOUND_FUNC_READ_ARR  211
#define ERR_ARR_NOT_FOUND_FUNC_WRITE_ARR  212
#define ERR_ARR_NOT_FOUND_FUNC_LAST_NEG_INDEX  213
#define ERR_ARR_NOT_FOUND_FUNC_KEY  214
#define ERR_ARR_NOT_FOUND_FUNC_COMPARE_INT  215
#define ERR_ARR_NOT_FOUND_FUNC_COMPARE_DOUBLE  216
#define ERR_ARR_NOT_FOUND_FUNC_MYSORT  217

size_t cnt_elems(FILE *f);
int read_arr(FILE *f, int *pb, int *pe);
int write_arr(FILE *f, const int *pb, const int *pe);
size_t last_neg_index(const int *pb, const int *pe);
int key(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst);
int compare_int(const void *p, const void *q);
int compare_double(const void *p, const void *q);
void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

#endif
