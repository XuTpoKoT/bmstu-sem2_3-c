#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <stdio.h>
#include <inttypes.h>

#define MAX_NAME_LEN 126

#pragma pack(push, 1)
typedef struct
{
    char name[MAX_NAME_LEN];
    int32_t mass;
} product_t;
#pragma pack(pop)

int file_size(FILE *f, long *count_products);
int get_product_by_pos(FILE *f, long pos, product_t *product);
int put_product_by_pos(FILE *f, long pos, const product_t *product);
int count_avg_mass(FILE *f, double *avg);
int del_products_lower_val(FILE *f, double val);

#endif
