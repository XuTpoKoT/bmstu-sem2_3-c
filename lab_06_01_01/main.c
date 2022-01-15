#include "films.h"

#define MIN_ARGS 3
#define MAX_ARGS 4

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    film_t films[MAX_FILMS];
    size_t count_films = 0;
    
    if (argc > MAX_ARGS || argc < MIN_ARGS)
        return WRONG_ARG_COUNT;
    
    if (wrong_field(argv[2]))
        return WRONG_FIELD;
    
    if (argc == MAX_ARGS && wrong_key(argv[2], argv[3]))
        return WRONG_KEY;
    
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
        return OPEN_FILE_ERROR;
    
    if (fscan_sorted(f, films, &count_films, argv[2]))
    {
        fclose(f);
        return READ_ERROR;
    }
       
    if (argc == MIN_ARGS)
        fprint_films(stdout, films, count_films);
    else if (find_film(films, count_films, argv[2], argv[3]))
        printf("Not found\n");
    
    fclose(f);
               
    return EXIT_SUCCESS;
}
