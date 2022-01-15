#include "products.h"

#include <string.h>
#include <stdlib.h>

int file_size(FILE *f, long *count_products)
{
    long pos = ftell(f);
    if (pos < 0)
        return EXIT_FAILURE;
    if (fseek(f, 0L, SEEK_END))
        return EXIT_FAILURE;
    long size = ftell(f);
    if (size < 0)
        return EXIT_FAILURE;

    *count_products = size / sizeof(product_t);
    if (*count_products * sizeof(product_t) != (size_t)size)
        return EXIT_FAILURE;

    return fseek(f, pos, SEEK_SET);
}

int get_product_by_pos(FILE *f, long pos, product_t *product)
{
    long cur_pos = ftell(f);
    if (cur_pos < 0)
        return EXIT_FAILURE;
    if (fseek(f, pos * sizeof(product_t), SEEK_SET))
        return EXIT_FAILURE;
    if (fread(product, sizeof(product_t), 1, f) != 1)
        return EXIT_FAILURE;
    return fseek(f, cur_pos, SEEK_SET);
}

int put_product_by_pos(FILE *f, long pos, const product_t *product)
{
    long cur_pos = ftell(f);
    if (cur_pos < 0)
        return EXIT_FAILURE;
    if (fseek(f, pos * sizeof(product_t), SEEK_SET))
        return EXIT_FAILURE;
    if (fwrite(product, sizeof(product_t), 1, f) != 1)
        return EXIT_FAILURE;
    return fseek(f, cur_pos, SEEK_SET);
}

int count_avg_mass(FILE *f, double *avg)
{
    long count_products;
    if (file_size(f, &count_products))
    {
        return EXIT_FAILURE;
    }
    
    product_t product;
    *avg = 0.0;
    for (long i= 0; i < count_products; i++)
    {
        if (get_product_by_pos(f, i, &product))
            return EXIT_FAILURE;
        *avg += product.mass;
    }
    *avg /= count_products;

    return EXIT_SUCCESS;
}

int del_products_lower_val(FILE *f, double val)
{
    long count_products;
    product_t del_product = { .name = "0000", .mass = 0};
    if (file_size(f, &count_products))
        return EXIT_FAILURE;

    long i;
    for (i= 0; i < count_products; i++)
    {
        product_t product1, product2;
        if (get_product_by_pos(f, i, &product1))
            return EXIT_FAILURE;
        if (product1.mass < val)
        {
            for (long j = i; j < count_products - 1; j++)
            {
                if (get_product_by_pos(f, j + 1, &product2))
                    return EXIT_FAILURE;
                if (put_product_by_pos(f, j, &product2))
                    return EXIT_FAILURE;
            }
            i--;
            count_products--;
        }
    }

    return put_product_by_pos(f, i, &del_product);
}
