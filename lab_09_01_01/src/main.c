#include <stdio.h>
#include <stdlib.h>

#include "films.h"
#include "err.h"

#define MIN_ARGS 3
#define MAX_ARGS 4

int main(int argc, char **argv)
{
    films_t films;
    size_t count_films;
    
    if (argc > MAX_ARGS || argc < MIN_ARGS)
        return EXIT_FAILURE;
    
    if (wrong_field(argv[2]))
        return ERR_WRONG_FIELD;
    
    if (argc == MAX_ARGS && wrong_key(argv[2], argv[3]))
        return EXIT_FAILURE;
    
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
        return EXIT_FAILURE;
    
    count_films = cnt_films(f);
    if (!count_films)
    {
        fclose(f);
        return EXIT_FAILURE;
    }

    if (films_init(&films, count_films))
    {
        fclose(f);
        return EXIT_FAILURE;
    }

    if (films_fread_sorted(f, &films, argv[2]))
    {
        fclose(f);
        return EXIT_FAILURE;
    }
       
    if (argc == MIN_ARGS)
        films_fwrite(stdout, &films);
    else if (films_find_film(&films, argv[2], argv[3]))
        printf("Not found\n");
    
    films_free(&films);
    fclose(f);    
               
    return EXIT_SUCCESS;
}
