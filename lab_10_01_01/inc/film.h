#ifndef FILM_H
#define FILM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    char *title;
    char *name;
    int year;
} film_t;

int film_fread(FILE *f, film_t *film);
void film_fwrite(FILE *f, const void *data);
void film_free(film_t *film);

int film_copy(film_t *restrict dst, const film_t *restrict src);

bool film_equal(const film_t *restrict a, const film_t *restrict b);

int film_cmp_names(const void *a, const void *b);
int film_cmp_title(const void *a, const void *b);
int film_cmp_years(const void *a, const void *b);

#endif