#define _GNU_SOURCE

#include <string.h>

#include "film.h"

int fscan_str(char **str, FILE *f)
{
    size_t len = 0;
    if (getline(str, &len, f) <= 0)
    {
        free(*str);
        return EXIT_FAILURE;
    }      

    len = strlen(*str);
    if ((*str)[len - 1] == '\n')
        (*str)[--len] = '\0';

    //пустая строка
    if (len == 0)
    {
        free(*str);
        return EXIT_FAILURE;
    }
        
    return EXIT_SUCCESS;
}


void film_free(film_t *film)
{
    if (film == NULL)
        return;

    free(film->title);
    free(film->name);
}


int film_fread(FILE *f, film_t *film)
{
    film->title = NULL;
    film->name = NULL;

    if (fscan_str(&film->title, f))
        return EXIT_FAILURE;
        
    if (fscan_str(&film->name, f))
    {
        free(film->title);
        return EXIT_FAILURE;
    }
        
    if (!fscanf(f, "%d", &film->year) || film->year <= 0)
    {
        free(film->title);
        free(film->name);
        return EXIT_FAILURE;
    }
        
    fscanf(f, "\n");

    return EXIT_SUCCESS;
}

void film_fwrite(FILE *f, const film_t *film)
{
    fprintf(f, "%s\n", film->title);
    fprintf(f, "%s\n", film->name);
    fprintf(f, "%d\n", film->year);
}


int film_copy(film_t *restrict dst, const film_t *restrict src)
{
    char *title_tmp = strdup(src->title);

    if (title_tmp)
    {
        char *name_tmp = strdup(src->name);
        if (name_tmp)
        {
            free(dst->title);
            free(dst->name);
            dst->title = title_tmp;
            dst->name = name_tmp;
            dst->year = src->year;
            return EXIT_SUCCESS;
        }
        else
            free(title_tmp);
    }

    return EXIT_FAILURE;
}


bool film_equal(const film_t *restrict a, const film_t *restrict b)
{
    return !strcmp(a->title, b->title) && !strcmp(a->name, b->name) && a->year == b->year;
}
