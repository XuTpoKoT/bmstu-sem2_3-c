#include <string.h>

#include "films.h"

#define BASE 10

const char *fields[] = { "title", "name", "year" };

size_t cnt_films(FILE *f)
{
    long pos = ftell(f);
    if (pos < 0L)
        return 0;
    if (fseek(f, 0L, SEEK_SET))
        return 0;

    size_t count_films = 0;
    film_t film;
    while (!film_fread(f, &film))
    {
        ++count_films;
        film_free(&film);
    }

    if (!feof(f))
    {
        fseek(f, pos, SEEK_SET);
        return 0;
    }

    if (fseek(f, pos, SEEK_SET))
        return 0;
    	
    return count_films;
}

int wrong_field(const char *field)
{ 
    for (size_t i = 0; i < count_fields; ++i)
        if (!strcmp(field, fields[i]))
            return 0;
    return 1;
}

int wrong_key(const char *field, const char *key)
{ 
    if (!strcmp(field, fields[title]) || !strcmp(field, fields[name]))
        return 0;

    if (!strcmp(field, fields[year]))
    {
        int year = strtol(key, NULL, BASE);
        return year <= 0;
    }
    return 1;
}


int films_init(films_t *films, size_t nmemb)
{
    films->nmemb = 0;

    if (nmemb == 0)
        return EXIT_SUCCESS;

    films->data = malloc(sizeof(film_t) * nmemb);
    if (!films->data)
        return EXIT_FAILURE;

    for (size_t i = 0; i < nmemb; i++)
    {
        films->data[i].title = NULL;
        films->data[i].name = NULL;
    }
          
    return EXIT_SUCCESS;
}

void films_free(films_t *films)
{
    for (size_t i = 0; i < films->nmemb; i++)
        film_free(&films->data[i]);
    free(films->data);
}


int films_fread(FILE *f, films_t *films)
{
    film_t buf;
    while (!film_fread(f, &buf))
    {
        if (film_copy(&films->data[films->nmemb], &buf))
        {
            films_free(films);
            return EXIT_FAILURE;
        }
            
        films->nmemb++;
    }
    
    if (!feof(f))
        return EXIT_FAILURE;
    
    return !films->nmemb;
}

void films_fwrite(FILE *f, const films_t *films)
{
    for (size_t i = 0; i < films->nmemb; i++)
        film_fwrite(f, films->data + i);
}


int films_insert_sorted(const film_t *film, films_t *films, const char *field)
{
    if (wrong_field(field))
        return EXIT_FAILURE;
    
    size_t field_ind, i = films->nmemb;
    for (field_ind = 0; field_ind < count_fields && strcmp(field, fields[field_ind]); ++field_ind);        
    
    switch (field_ind)
    {
        case title:
            while (i > 0 && strcmp(films->data[i - 1].title, film->title) > 0)
            {
                if (film_copy(&films->data[i], &films->data[i - 1]))
                    return EXIT_FAILURE;
                --i;
            }
            break;
        case name:
            while (i > 0 && strcmp(films->data[i - 1].name, film->name) > 0)
            {
                if (film_copy(&films->data[i], &films->data[i - 1]))
                    return EXIT_FAILURE;
                --i;
            }
            break;
        case year:
            while (i > 0 && films->data[i - 1].year > film->year)
            {
                if (film_copy(&films->data[i], &films->data[i - 1]))
                    return EXIT_FAILURE;
                --i;
            }
            break;
    }

    if (film_copy(&films->data[i], film))
        return EXIT_FAILURE;

    films->nmemb++;

    return EXIT_SUCCESS;
}

int films_fread_sorted(FILE *f, films_t *films, const char *field)
{
    film_t buf;
    while (!film_fread(f, &buf))
    {
        if (films_insert_sorted(&buf, films, field))
        {
            films_free(films);
            film_free(&buf);
            return EXIT_FAILURE;
        }
        film_free(&buf);
    }
    
    if (!feof(f))
        return EXIT_FAILURE;
    
    return !films->nmemb;
}


int film_cmp_fields(const film_t *film, const char *field, const char *key)
{
    size_t i;
    for (i = 0; i < count_fields && strcmp(field, fields[i]); ++i);
    
    switch (i)
    {
        case title:
            return strcmp(film->title, key);
        case name:
            return strcmp(film->name, key);
        case year:
            return film->year - strtol(key, NULL, BASE);
    }
    return EXIT_SUCCESS;
}

int films_find_film(const films_t *films, const char *field, const char *key)
{
    size_t l = 0, r = films->nmemb;
    while (l + 1 < r)
    {
        size_t mid = (l + r) / 2;
        if (film_cmp_fields(films->data + mid, field, key) > 0)
            r = mid;
        else
            l = mid;
        if (film_cmp_fields(films->data + l, field, key) == 0)
        {
            film_fwrite(stdout, films->data + l);
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}

bool films_equal(const films_t *a, const films_t *b)
{
    if (a->nmemb != b->nmemb)
        return false;
    
    for (size_t i = 0; i < a->nmemb; i++)
        if (!film_equal(&a->data[i], &b->data[i]))
            return false;

    return true;
}
