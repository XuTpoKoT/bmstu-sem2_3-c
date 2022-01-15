#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

#include "arr.h"
#include "err.h"

#define MIN_ARGS 3
#define MAX_ARGS 4

typedef size_t (*fn_cnt_elems_t)(FILE *);
typedef int (*fn_read_arr_t)(FILE *, int *, int *);
typedef int (*fn_write_arr_t)(FILE *, const int *, const int *);
typedef size_t (*fn_last_neg_index_t)(const int *, const int *);
typedef int (*fn_key_t)(const int *, const int *, int *, int *);
typedef int (*fn_compare_int_t)(const void *, const void *);
typedef void (*fn_mysort_t)(void *, size_t, size_t, int (*)(const void*, const void*));

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    size_t count_elems = 0;

    // загрузка функций из библиотеки
    void* hlib;
    fn_cnt_elems_t cnt_elems;
    fn_read_arr_t read_arr;
    fn_write_arr_t write_arr;
    fn_last_neg_index_t last_neg_index;
    fn_key_t key;
    fn_compare_int_t compare_int;
    fn_mysort_t mysort;

    hlib = dlopen("libarr.so", RTLD_NOW);
    if (!hlib)
        return ERR_ARR_NOT_FOUND_LIB;

    cnt_elems = (fn_cnt_elems_t) dlsym(hlib, "cnt_elems");
    if (!cnt_elems)
    {
        dlclose(hlib);
        return ERR_ARR_NOT_FOUND_FUNC_CNT_ELEMS;
    }

    read_arr = (fn_read_arr_t) dlsym(hlib, "read_arr");
    if (!read_arr)
    {
        dlclose(hlib);
        return ERR_ARR_NOT_FOUND_FUNC_READ_ARR;
    }

    write_arr = (fn_write_arr_t) dlsym(hlib, "write_arr");
    if (!write_arr)
    {
        dlclose(hlib);
        return ERR_ARR_NOT_FOUND_FUNC_WRITE_ARR;
    }

    last_neg_index = (fn_last_neg_index_t) dlsym(hlib, "last_neg_index");
    if (!last_neg_index)
    {
        dlclose(hlib);
        return ERR_ARR_NOT_FOUND_FUNC_LAST_NEG_INDEX;
    }

    key = (fn_key_t) dlsym(hlib, "key");
    if (!key)
    {
        dlclose(hlib);
        return ERR_ARR_NOT_FOUND_FUNC_KEY;
    }

    compare_int = (fn_compare_int_t) dlsym(hlib, "compare_int");
    if (!compare_int)
    {
        dlclose(hlib);
        return ERR_ARR_NOT_FOUND_FUNC_COMPARE_INT;
    }

    mysort = (fn_mysort_t) dlsym(hlib, "mysort");
    if (!mysort)
    {
        dlclose(hlib);
        return ERR_ARR_NOT_FOUND_FUNC_MYSORT;
    }

    
    if (argc > MAX_ARGS || argc < MIN_ARGS)
    {
        dlclose(hlib);
        return ERR_WRONG_ARG_COUNT;
    }
    
    if (argc == 4 && strcmp(argv[3], "f"))
    {
        dlclose(hlib);
        return ERR_WRONG_KEY;
    }
    
    FILE *fsrc = fopen(argv[1], "r");
    if (fsrc == NULL)
    {
        dlclose(hlib);
        return ERR_OPEN_FILE;
    }
      
    if ((count_elems = cnt_elems(fsrc)) == 0)
    {
        dlclose(hlib);
        fclose(fsrc);
        return EXIT_FAILURE;
    }
       
    int *pb_src = malloc(count_elems * sizeof(int));
    if (pb_src == NULL)
    {
        dlclose(hlib);
        fclose(fsrc);
        return ERR_MALLOC;
    }

    int *pe_src = pb_src + count_elems;

    if (read_arr(fsrc, pb_src, pe_src))
    {
        dlclose(hlib);
        fclose(fsrc);
        free(pb_src);
        return ERR_ARR_READ;
    }
    fclose(fsrc);

    int *pb_dst = NULL, *pe_dst;

    if (argc == 4)
    {
        size_t new_count_elems = last_neg_index(pb_src, pe_src);
        if (new_count_elems == 0)
        {
            dlclose(hlib);
            free(pb_src);
            return ERR_ARR_FILTER;
        }

        pb_dst = malloc(sizeof(int) * new_count_elems);
        if (!pb_dst)
        {
            dlclose(hlib);
            free(pb_src);
            return ERR_MALLOC;
        }
        pe_dst = pb_dst + new_count_elems;

        if (key(pb_src, pe_src, pb_dst, pe_dst))
        {
            dlclose(hlib);
            free(pb_src);
            return ERR_ARR_FILTER;
        }

        free(pb_src);
    }

    if (pb_dst == NULL)
    {
        pb_dst = pb_src;
        pe_dst = pe_src;
    }

    mysort(pb_dst, pe_dst - pb_dst, sizeof(int), compare_int);

    FILE *fdst = fopen(argv[2], "w");
    if (fdst == NULL)
    {
        dlclose(hlib);
        free(pb_dst);
        return ERR_OPEN_FILE;
    }

    if (write_arr(fdst, pb_dst, pe_dst))
    {
        dlclose(hlib);
        free(pb_dst);        
        fclose(fdst);
        return ERR_ARR_WRITE;
    }
    
    free(pb_dst);
    fclose(fdst);
    dlclose(hlib);
               
    return EXIT_SUCCESS;
}
