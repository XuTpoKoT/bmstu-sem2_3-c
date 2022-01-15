#include "product.h"

#include <string.h>

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    
    if (argc == 4 && strcmp(argv[1], "sb") == 0)
    {   
        FILE *fsrc = fopen(argv[2], "rb");
        if (fsrc == NULL)
            return NO_FILE;
        FILE *fdst = fopen(argv[3], "wb+");
        if (fdst == NULL)
        {
            fclose(fsrc);
            return NO_FILE;     
        }
        if (copy_products(fsrc, fdst))
        {
            fclose(fsrc);
            fclose(fdst);
            return COPY_ERROR;
        }
        if (sort_products_by_price(fdst))
        {
            fclose(fsrc);
            fclose(fdst);
            return SORT_ERROR;
        }
        fclose(fsrc);
        fclose(fdst);
    }
    else if (argc == 4 && strcmp(argv[1], "fb") == 0)
    {
        FILE *f = fopen(argv[2], "rb");
        if (f == NULL)
            return NO_FILE;
        if (find_products(f, argv[3]))
        {
            fclose(f);
            return FIND_ERROR;
        }
        fclose(f);
    }
    else if (argc == 3 && strcmp(argv[1], "ab") == 0)
    {
        product_t product = { 0 };
        if (scan_product(&product))
            return SCAN_ERROR;
        FILE *f = fopen(argv[2], "rb+");
        if (f == NULL)
        {
            f = fopen(argv[2], "wb+");
            if (f == NULL)
                return NO_FILE;
        }
        if (insert(f, &product))
        {
            fclose(f);
            return INSERT_ERROR;
        }
        fclose(f);
    }
    else if (argc == 4 && strcmp(argv[1], "t_to_b") == 0)
    {
        FILE *fsrc = fopen(argv[2], "r");
        if (fsrc == NULL)
            return NO_FILE;
        FILE *fdst = fopen(argv[3], "wb");
        if (fdst == NULL)
        {
            fclose(fsrc);
            return NO_FILE;
        }
        if (txt_to_bin(fsrc, fdst))
        {
            fclose(fsrc);
            fclose(fdst);
            return TXT_TO_BIN_ERROR;
        }
        fclose(fsrc);
        fclose(fdst);
    }
    else if (argc == 4 && strcmp(argv[1], "b_to_t") == 0)
    {
        FILE *fsrc = fopen(argv[2], "rb");
        if (fsrc == NULL)
            return NO_FILE;
        FILE *fdst = fopen(argv[3], "w");
        if (fdst == NULL)
        {
            fclose(fsrc);
            return NO_FILE;
        }
        if (bin_to_txt(fsrc, fdst))
        {
            fclose(fsrc);
            fclose(fdst);
            return BIN_TO_TXT_ERROR;
        }
        fclose(fsrc);
        fclose(fdst);
    }
    else
        return WRONG_ARGS;
        
    return EXIT_SUCCESS;
}
