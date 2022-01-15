#include "short_string.h"

#include <stdio.h>

int main(void)
{
    setbuf(stdout, NULL);
    const char delims[] = ".:,;-!? ";
    short_string_t s1, s2;
    words_t w;
    size_t count_words;
    int rc;

    if ((rc = input(s1)))
        return rc;

    if ((rc = split(s1, w, &count_words, delims)))
        return rc;

    if ((rc = joinr(w, count_words, s2)))
        return rc;

    printf("Result: %s\n", s2);

    return EXIT_SUCCESS;
}
