#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define WRONG_ARGS 53
#define EMPTY_STRING 1
#define TOO_LONG_STRING 2
#define NO_FILE 3
#define COPY_ERROR 4
#define SORT_ERROR 5
#define FIND_ERROR 6
#define SCAN_ERROR 7
#define INSERT_ERROR 8
#define TXT_TO_BIN_ERROR 9
#define BIN_TO_TXT_ERROR 10

#define LEN_NAME 31
#define LEN_PRODUCER 16

typedef struct
{
    char name[LEN_NAME];
    char producer[LEN_PRODUCER];
    uint32_t price;
    uint32_t count;
} product_t;

int file_size(FILE *f, size_t *count_products);
int fscan_str(char str[], size_t n, FILE *f);
int fscan_product(FILE *f, product_t *product);
int scan_product(product_t *product);
void fprint_product(FILE *f, const product_t *product);
int get_product_by_pos(FILE *f, long pos, product_t *product);
int put_product_by_pos(FILE *f, long pos, const product_t *product);
int copy_products(FILE *restrict fsrc, FILE *restrict fdst);
int is_greater(const product_t *product1, const product_t *product2);
int sort_products_by_price(FILE *f);
int find_products(FILE *f, char sub_str[]);
int insert(FILE *f, const product_t *product);
int txt_to_bin(FILE *fsrc, FILE *fdst);
int bin_to_txt(FILE *fsrc, FILE *fdst);

#endif
