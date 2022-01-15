#include "matr_arr.h"

int matr_arr_init(size_t nmemb, matr_t **matr_arr)
{
    if (nmemb == 0)
        return EXIT_FAILURE;

    matr_arr= calloc(nmemb, sizeof(matr_t));
    if (!matr_arr)
        return EXIT_FAILURE;
      
    return EXIT_SUCCESS;
}
