#ifndef FILMS_H
#define FILMS_H

#include <stdio.h>
#include <stdlib.h>

#define WRONG_ARG_COUNT 1
#define WRONG_FIELD 2
#define WRONG_KEY 3
#define OPEN_FILE_ERROR 4
#define READ_ERROR 5
#define FIND_ERROR 6

#define MAX_STR_LEN 27

#define LEN_TITLE 26
#define LEN_NAME 26

#define MAX_FILMS 15

typedef struct
{
    char title[LEN_TITLE];
    char name[LEN_NAME];
    int year;
} film_t;

enum fields
{
    title,
    name,
    year,
    count_fields
};


int fscan_film(FILE *f, film_t *film);
int fscan_films(FILE *f, film_t films[], size_t *count_films);
void fprint_film(FILE *f, const film_t *film);
void fprint_films(FILE *f, const film_t *films, const size_t count_films);
int insert_sorted(const film_t *film, film_t *films, size_t count_films, const char *field);
int fscan_sorted(FILE *f, film_t films[], size_t *count_films, const char *field);
int wrong_field(const char *field);
int wrong_key(const char *field, const char *key);
void copy_film(film_t *restrict dst, const film_t *restrict src);
int sort_films_by_field(film_t films[], const size_t count_films, const char *field);
int find_film(const film_t films[], const size_t count_films, const char *field, const char *key);

#endif
