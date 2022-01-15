#include "arr.h"
#include "error_codes.h"

#include <string.h>

#define MIN_ARGS 3
#define MAX_ARGS 4

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    size_t count_elems = 0;
    
    if (argc > MAX_ARGS || argc < MIN_ARGS)
        return WRONG_ARG_COUNT;
    
    if (argc == 4 && strcmp(argv[3], "f"))
        return WRONG_KEY;
    
    FILE *fsrc = fopen(argv[1], "r");
    if (fsrc == NULL)
        return OPEN_FILE_ERROR;
    
    
    if ((count_elems = cnt_elems(fsrc)) == 0)
    {
        fclose(fsrc);
        return EXIT_FAILURE;
    }
       
    int *pb_src = malloc(count_elems * sizeof(int));
    if (pb_src == NULL)
    {
        fclose(fsrc);
        return EXIT_FAILURE;
    }
    int *pe_src = pb_src + count_elems;

    if (read_arr(fsrc, pb_src, pe_src))
    {
        free(pb_src);
        fclose(fsrc);
        return EXIT_FAILURE;
    }

    int *pb_dst = NULL, *pe_dst;
    if (argc == 4 && key(pb_src, pe_src, &pb_dst, &pe_dst))
    {
        free(pb_src);
        fclose(fsrc);
        return EXIT_FAILURE;
    }

    if (pb_dst == NULL)
    {
        pb_dst = pb_src;
        pe_dst = pe_src;
    }
    else
        free(pb_src);

    mysort(pb_dst, pe_dst - pb_dst, sizeof(int), compare_int);

    FILE *fdst = fopen(argv[2], "w");
    if (fdst == NULL)
    {
        free(pb_dst);
        fclose(fsrc);
        return OPEN_FILE_ERROR;
    }

    if (write_arr(fdst, pb_dst, pe_dst))
    {
        free(pb_dst);
        fclose(fsrc);
        fclose(fdst);
        return EXIT_FAILURE;
    }
    
    free(pb_dst);
    fclose(fsrc);
    fclose(fdst);
               
    return EXIT_SUCCESS;
}
