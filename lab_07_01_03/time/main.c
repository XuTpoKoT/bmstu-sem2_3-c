#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/time.h>

#include "error_codes.h"
#include "arr.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    size_t count_elems;
    struct timeval tv_start, tv_stop;
    int64_t elapsed_time;	
	
    if (argc != 2)
        return WRONG_ARG_COUNT;
    
    FILE *fsrc = fopen(argv[1], "r");
    if (fsrc == NULL)
        return OPEN_FILE_ERROR;
       
    if ((count_elems = cnt_elems(fsrc)) == 0)
    {
        fclose(fsrc);
        return EXIT_FAILURE;
    }
       
    int *pb = malloc(count_elems * sizeof(int));
    if (pb == NULL)
    {
        fclose(fsrc);
        return EXIT_FAILURE;
    }

    int *pe = pb + count_elems;

    if (read_arr(fsrc, pb, pe))
    {
        free(pb);
        fclose(fsrc);
        return EXIT_FAILURE;
    }
    
    gettimeofday(&tv_start, NULL);
    mysort(pb, pe - pb, sizeof(int), compare_int);
    gettimeofday(&tv_stop, NULL);
    elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
        (tv_stop.tv_usec - tv_start.tv_usec);
    printf("%"PRId64"\n", elapsed_time);
	
    free(pb);

    return EXIT_SUCCESS;
}
