#include "short_string.h"
#include "date.h"

#include <stdio.h>

int main(void)
{
    setbuf(stdout, NULL);
    const char delims[] = { ' ', '\t', '\r', '\v', '\f' };
    short_string_t s = "";
    words_t w;
    size_t count_words;
    int rc;

    if ((rc = input(s)) == TOO_LONG_STRING)
        return rc;


    split(s, w, &count_words, delims);

    if (count_words == 3 && date_correct(w[0], w[1], w[2]))
        printf("YES");
    else
        printf("NO");

    return EXIT_SUCCESS;
}
