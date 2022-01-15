#include <string.h>

#include "arr.h"
#include "err.h"

#define MIN_ARGS 3
#define MAX_ARGS 4

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    size_t count_elems = 0;
    
    if (argc > MAX_ARGS || argc < MIN_ARGS)
        return ERR_WRONG_ARG_COUNT;
    
    if (argc == 4 && strcmp(argv[3], "f"))
        return ERR_WRONG_KEY;
    
    FILE *fsrc = fopen(argv[1], "r");
    if (fsrc == NULL)
        return ERR_OPEN_FILE;
      
    if ((count_elems = cnt_elems(fsrc)) == 0)
    {
        fclose(fsrc);
        return EXIT_FAILURE;
    }
       
    int *pb_src = malloc(count_elems * sizeof(int));
    if (pb_src == NULL)
    {
        fclose(fsrc);
        return ERR_MALLOC;
    }

    int *pe_src = pb_src + count_elems;

    if (read_arr(fsrc, pb_src, pe_src))
    {
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
            free(pb_src);
            return ERR_ARR_FILTER;
        }

        pb_dst = malloc(sizeof(int) * new_count_elems);
        if (!pb_dst)
        {
            free(pb_src);
            return ERR_MALLOC;
        }
        pe_dst = pb_dst + new_count_elems;

        if (key(pb_src, pe_src, pb_dst, pe_dst))
        {
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
        free(pb_dst);
        return ERR_OPEN_FILE;
    }

    if (write_arr(fdst, pb_dst, pe_dst))
    {
        free(pb_dst);        
        fclose(fdst);
        return ERR_ARR_WRITE;
    }
    
    free(pb_dst);
    fclose(fdst);
               
    return EXIT_SUCCESS;
}
