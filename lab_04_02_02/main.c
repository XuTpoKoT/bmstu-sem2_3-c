#include "short_string.h"

#include <stdio.h>
#include <string.h>

int main(void)
{
    setbuf(stdout, NULL);
    const char delims[] = ".:,;-!? ";
    short_string_t s1, s2;
    words_t w1, w2;
    size_t count_words1, count_words2;
    int rc;

    if ((rc = input(s1)))
        return rc;

    if ((rc = input(s2)))
        return rc;

    if ((rc = split(s1, w1, &count_words1, delims)))
        return rc;

    if ((rc = split(s2, w2, &count_words2, delims)))
        return rc;

    printf("Result: \n");

    for (size_t i = 0; i < count_words1; i++)
    {
        int same = 0;
        for (size_t j = 0; j < i && !same; j++)
            if (strcmp(w1[i], w1[j]) == 0)
                same = 1;
        if (!same)
        {
            int answer = 0;
            for (size_t j = 0; j < count_words2 && answer == 0; j++)
                if (strcmp(w1[i], w2[j]) == 0)
                    answer = 1;
            if (answer == 1)
                printf("%s yes\n", w1[i]);
            else
                printf("%s no\n", w1[i]);
        }
    }

    return EXIT_SUCCESS;
}
