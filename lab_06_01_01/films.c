#include "films.h"

#include <string.h>

#define BASE 10

const char *fields[] = { "title", "name", "year" };

int fscan_str(char str[], size_t n, FILE *f)
{
    if (n >= MAX_STR_LEN)
        return EXIT_FAILURE;
    char buf[MAX_STR_LEN];
    if (!fgets(buf, n + 1, f))
        return EXIT_FAILURE;

    size_t len = strlen(buf);
    if (buf[len - 1] == '\n')
        buf[--len] = '\0';

    //пустая строка
    if (len == 0)
        return EXIT_FAILURE;
    //переполнение
    if (len >= n)
        return EXIT_FAILURE;

    strcpy(str, buf);

    return EXIT_SUCCESS;
}

int fscan_film(FILE *f, film_t *film)
{
    if (fscan_str(film->title, LEN_TITLE, f))
        return EXIT_FAILURE;
    if (fscan_str(film->name, LEN_NAME, f))
        return EXIT_FAILURE;
    if (!fscanf(f, "%d", &film->year) || film->year <= 0)
        return EXIT_FAILURE;
    fscanf(f, "\n");

    return EXIT_SUCCESS;
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
    if (!strcmp(field, fields[title]))
        return strlen(key) > LEN_TITLE;
    if (!strcmp(field, fields[name]))
        return strlen(key) > LEN_NAME;
    if (!strcmp(field, fields[year]))
    {
        int year = strtol(key, NULL, BASE);
        return year <= 0;
    }
    return 1;
}

int fscan_films(FILE *f, film_t films[], size_t *count_films)
{
    size_t i = 0;
    film_t buf;
    while (!fscan_film(f, &buf) && i <= MAX_FILMS)
    {
        if (i < MAX_FILMS)
            copy_film(films + i, &buf);
        ++i;
    }
    
    if (!feof(f) || i > MAX_FILMS)
        return EXIT_FAILURE;
    
    *count_films = i;
    
    return !i;
}

void fprint_film(FILE *f, const film_t *film)
{
    fprintf(f, "%s\n", film->title);
    fprintf(f, "%s\n", film->name);
    fprintf(f, "%d\n", film->year);
}

void fprint_films(FILE *f, const film_t *films, const size_t count_films)
{
    for (size_t i = 0; i < count_films; ++i)
        fprint_film(f, films + i);
}

int insert_sorted(const film_t *film, film_t *films, size_t count_films, const char *field)
{
    if (wrong_field(field))
        return EXIT_FAILURE;
    
    size_t field_ind, i = count_films;
    for (field_ind = 0; field_ind < count_fields && strcmp(field, fields[field_ind]); ++field_ind);        
    
    switch (field_ind)
    {
        case title:
            while (i > 0 && strcmp(films[i - 1].title, film->title) > 0)
            {
                copy_film(films + i, films + i - 1);
                --i;
            }
            break;
        case name:
            while (i > 0 && strcmp(films[i - 1].name, film->name) > 0)
            {
                copy_film(films + i, films + i - 1);
                --i;
            }
            break;
        case year:
            while (i > 0 && films[i - 1].year > film->year)
            {
                copy_film(films + i, films + i - 1);
                --i;
            }
            break;
    }
    copy_film(films + i, film);

    return EXIT_SUCCESS;
}

int fscan_sorted(FILE *f, film_t films[], size_t *count_films, const char *field)
{
    size_t i = 0;
    film_t buf;
    while (!fscan_film(f, &buf) && i <= MAX_FILMS)
    {
        if (i < MAX_FILMS)
            insert_sorted(&buf, films, i, field);
        ++i;
    }
    
    if (!feof(f) || i > MAX_FILMS)
        return EXIT_FAILURE;
    
    *count_films = i;
    
    return !i;
}

void copy_film(film_t *restrict dst, const film_t *restrict src)
{
    strcpy(dst->title, src->title);
    strcpy(dst->name, src->name);
    dst->year = src->year;
}

int sort_films_by_field(film_t films[], const size_t count_films, const char *field)
{
    if (wrong_field(field))
        return EXIT_FAILURE;
    
    size_t field_ind;
    for (field_ind = 0; field_ind < count_fields && strcmp(field, fields[field_ind]); ++field_ind);        
    
    for (size_t top = 1; top < count_films; ++top)
    {
        film_t top_el = films[top];
        size_t i = top;
        switch (field_ind)
        {
            case title:
                while (i > 0 && strcmp(films[i - 1].title, top_el.title) > 0)
                {
                    copy_film(films + i, films + i - 1);
                    --i;
                }
                break;
            case name:
                while (i > 0 && strcmp(films[i - 1].name, top_el.name) > 0)
                {
                    copy_film(films + i, films + i - 1);
                    --i;
                }
                break;
            case year:
                while (i > 0 && films[i - 1].year > top_el.year)
                {
                    copy_film(films + i, films + i - 1);
                    --i;
                }
                break;
        }
        copy_film(films + i, &top_el);
    }

    return EXIT_SUCCESS;
}

int cmp_fields(const film_t *film, const char *field, const char *key)
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

int find_film(const film_t films[], const size_t count_films, const char *field, const char *key)
{
    size_t l = 0, r = count_films;
    while (l + 1 < r)
    {
        size_t mid = (l + r) / 2;
        if (cmp_fields(films + mid, field, key) > 0)
            r = mid;
        else
            l = mid;
        if (cmp_fields(films + l, field, key) == 0)
        {
            fprint_film(stdout, films + l);
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}


