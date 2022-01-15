#ifndef _SHORT_STRING_H_
#define _SHORT_STRING_H_

#include <stdlib.h>

#define EMPTY_STRING 1
#define TOO_LONG_STRING 2

#define MAX_STRING_LEN 257
#define MAX_WORDS 128

typedef char short_string_t[MAX_STRING_LEN];
typedef short_string_t words_t[MAX_WORDS];

int input(short_string_t str);
int split(short_string_t str, words_t words, size_t *restrict count_words, const char *restrict delims);

#endif
