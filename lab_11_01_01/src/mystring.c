#include <string.h>

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

size_t ll2str(char *str, long long num, unsigned base)
{
    char alf[] = "0123456789abcdef";
    size_t simbols = 0;
    long long sign = 1;
    if (num < 0)
        sign = -1;

    if (num == 0)
    {
        str[0] = '0';
        simbols++;
    }
    
    while (num != 0)
    {
        str[simbols++] = alf[num % base * sign];
        num /= base;
    }   

    for (size_t i = 0; i < simbols / 2; i++)
    {
        char buf = str[i];
        str[i] = str[simbols - i - 1];
        str[simbols - i - 1] = buf; 
    }

    if (sign < 0)
    {
        for (size_t i = simbols; i > 0; i--)
            str[i] = str[i - 1];
        str[0] = '-';
        simbols++;
    }

    str[simbols] = '\0';

    return simbols;
}

size_t ull2str(char *str, unsigned long long num, unsigned base)
{
    char alf[] = "0123456789abcdef";
    size_t simbols = 0;

    if (num == 0)
    {
        str[0] = '0';
        simbols++;
    }
    
    while (num != 0)
    {
        str[simbols++] = alf[num % base];
        num /= base;
    }   

    for (size_t i = 0; i < simbols / 2; i++)
    {
        char buf = str[i];
        str[i] = str[simbols - i - 1];
        str[simbols - i - 1] = buf; 
    }

    str[simbols] = '\0';

    return simbols;
}
