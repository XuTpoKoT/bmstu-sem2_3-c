#ifndef FILMS_H
#define FILMS_H

#include <stdio.h>
#include <stdlib.h>

#include "film.h"

typedef struct
{
    size_t nmemb;
    film_t *data;
} films_t;

enum fields
{
    title,
    name,
    year,
    count_fields
};

size_t cnt_films(FILE *f);

int films_malloc(films_t *films, size_t nmemb);
void films_free(films_t *films);

int films_fread(FILE *f, films_t *films);
void films_fwrite(FILE *f, const films_t *films);

int films_insert_sorted(const film_t *film, films_t *films, const char *field);
int films_fread_sorted(FILE *f, films_t *films, const char *field);

int wrong_field(const char *field);
int wrong_key(const char *field, const char *key);

int films_find_film(const films_t *films, const char *field, const char *key);

bool films_equal(const films_t *a, const films_t *b);

#endif
