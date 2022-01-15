#include "product.h"

#include <string.h>

#define MAX_STR_LEN 32

int file_size(FILE *f, size_t *count_products)
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

int fscan_str(char str[], size_t n, FILE *f)
{
    if (n >= MAX_STR_LEN)
        return EXIT_FAILURE;
    char buf[MAX_STR_LEN];
    if (!fgets(buf, n + 1, f))
        return EMPTY_STRING;

    size_t len = strlen(buf);
    if (buf[len - 1] == '\n')
        buf[--len] = '\0';

    if (len == 0)
        return EMPTY_STRING;
    if (len >= n)
        return TOO_LONG_STRING;

    strncpy(str, buf, n);

    return EXIT_SUCCESS;
}

int fscan_product(FILE *f, product_t *product)
{
    if (fscan_str(product->name, LEN_NAME, f))
        return EXIT_FAILURE;
    if (fscan_str(product->producer, LEN_PRODUCER, f))
        return EXIT_FAILURE;
    if (!fscanf(f, "%"SCNu32"", &product->price))
        return EXIT_FAILURE;
    if (!fscanf(f, "%"SCNu32"", &product->count))
        return EXIT_FAILURE;
    fscanf(f, "\n");

    return EXIT_SUCCESS;
}

int scan_product(product_t *product)
{
    if (fscan_str(product->name, LEN_NAME, stdin))
        return EXIT_FAILURE;
    if (fscan_str(product->producer, LEN_PRODUCER, stdin))
        return EXIT_FAILURE;
    if (!scanf("%"SCNu32"", &product->price))
        return EXIT_FAILURE;
    if (!scanf("%"SCNu32"", &product->count))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void fprint_product(FILE *f, const product_t *product)
{
    fprintf(f, "%s\n", product->name);
    fprintf(f, "%s\n", product->producer);
    fprintf(f, "%"PRIu32"\n", product->price);
    fprintf(f, "%"PRIu32"\n", product->count);
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

int copy_products(FILE *restrict fsrc, FILE *restrict fdst)
{
    product_t product = { 0 };
    size_t count_products = 0;
    if (file_size(fsrc, &count_products))
        return EXIT_FAILURE;

    for (size_t i = 0; i < count_products; i++)
    {
        if (get_product_by_pos(fsrc, i, &product))
            return EXIT_FAILURE;
        if (put_product_by_pos(fdst, i, &product))
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int is_greater(const product_t *product1, const product_t *product2)
{
    return product1->price > product2->price || (
        product1->price == product2->price && product1->count > product2->count);
}

int sort_products_by_price(FILE *f)
{
    product_t product1 = { 0 }, product2 = { 0 };
    int end = 0;
    size_t count_products = 0;
    if (file_size(f, &count_products))
        return EXIT_FAILURE;

    for (size_t i = 0; i < count_products - 1 && !end; i++)
    {
        end = 1;
        for (size_t j = 0; j < count_products - 1 - i; j++)
        {
            if (get_product_by_pos(f, j, &product1))
                return EXIT_FAILURE;
            if (get_product_by_pos(f, j + 1, &product2))
                return EXIT_FAILURE;
            if (is_greater(&product2, &product1))
            {
                end = 0;
                if (put_product_by_pos(f, j, &product2))
                    return EXIT_FAILURE;
                if (put_product_by_pos(f, j + 1, &product1))
                    return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}

int find_products(FILE *f, char sub_str[])
{
    size_t len_sb = strlen(sub_str);
    if (len_sb == 0)
        return EXIT_FAILURE;
    product_t product = { 0 };
    size_t count_products = 0;
    if (file_size(f, &count_products))
        return EXIT_FAILURE;

    int rc = EXIT_FAILURE;
    for (size_t i = 0; i < count_products; i++)
    {
        if (get_product_by_pos(f, i, &product))
            return EXIT_FAILURE;
        size_t len_name = strlen(product.name);
        if (len_name >= len_sb)
        {
            size_t len_dif = len_name - len_sb;
            if (!strcmp(product.name + len_dif, sub_str))
            {
                rc = EXIT_SUCCESS;
                fprint_product(stdout, &product);
            }
        }
    }

    return rc;
}

int insert(FILE *f, const product_t *product)
{
    product_t cur_product = { 0 };
    size_t count_products = 0;
    if (file_size(f, &count_products))
        return EXIT_FAILURE;
    if (count_products == 0)
        return put_product_by_pos(f, 0, product);

    size_t i;
    for (i = count_products - 1; i > 0; i--)
    {
        if (get_product_by_pos(f, i, &cur_product))
            return EXIT_FAILURE;
        if (is_greater(&cur_product, product))
            return put_product_by_pos(f, i + 1, product);
        else if (put_product_by_pos(f, i + 1, &cur_product))
            return EXIT_FAILURE;
    }
    if (get_product_by_pos(f, i, &cur_product))
        return EXIT_FAILURE;
    if (is_greater(&cur_product, product))
        return put_product_by_pos(f, i + 1, product);
    else
    {
        if (put_product_by_pos(f, i + 1, &cur_product))
            return EXIT_FAILURE;
        return put_product_by_pos(f, i, product);
    }

    return EXIT_SUCCESS;
}

int txt_to_bin(FILE *fsrc, FILE *fdst)
{
    product_t product = { 0 };
    for (size_t i = 0; !fscan_product(fsrc, &product); i++)
        if (put_product_by_pos(fdst, i, &product))
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int bin_to_txt(FILE *fsrc, FILE *fdst)
{
    product_t product = { 0 };
    size_t count_products = 0;
    if (file_size(fsrc, &count_products))
        return EXIT_FAILURE;

    for (size_t i = 0; i < count_products; i++)
    {
        if (get_product_by_pos(fsrc, i, &product))
            return EXIT_FAILURE;
        fprint_product(fdst, &product);
    }

    return EXIT_SUCCESS;
}
