#include <stdlib.h>

#include "mystring.h"

int fscan_str(char str[], size_t n, FILE *f)
{
    if (n >= MYSTRING_LEN + 1)
        return EXIT_FAILURE;
    char buf[MYSTRING_LEN + 1];
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