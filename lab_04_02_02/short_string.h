#ifndef _SHORT_STRING_H_
#define _SHORT_STRING_H_

#include <stdlib.h>

#define EMPTY_STRING 1
#define TOO_LONG_STRING 2
#define TOO_LONG_WORD 3
#define NO_WORDS 4

#define MAX_STRING_LEN 257
#define MAX_WORD_LEN 17
#if MAX_WORD_LEN > MAX_STRING_LEN
#error WORD_LEN > STRING_LEN
#endif
#define MAX_WORDS 128

typedef char short_string_t[MAX_STRING_LEN];
typedef char word_t[MAX_WORD_LEN];
typedef word_t words_t[MAX_WORDS];

int input(short_string_t str);
int split(short_string_t str, words_t words, size_t *restrict count_words, const char *restrict delims);

#endif
