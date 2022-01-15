#include <string.h>
#include <stdlib.h>

#include "str.h"

int input_str(FILE *f, str_t str)
{   
    char buf[MAX_STR_LEN + 1];
    if (!fgets(buf, MAX_STR_LEN + 1, f))
        return EXIT_FAILURE;
    
    size_t len = strlen(buf);
    if (buf[len - 1] == '\n')
        buf[--len] = '\0';

    if (len == 0)
        return EXIT_FAILURE;
    if (len >= MAX_STR_LEN)
        return EXIT_FAILURE;
    
    strcpy(str, buf);
    
    return EXIT_SUCCESS;
}

int del_simbols(char src[], char dst[], char simbols[])
{
    size_t len_src = strlen(src);
    size_t len_dst = 0;
    for (size_t i = 0; i < len_src; i++)
    {
        if (strchr(simbols, src[i]) == NULL)
            dst[len_dst++] = src[i];
    }
        
    dst[len_dst] = '\0';
        
    return len_dst;
}

int is_polindrome(char str[])
{
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++)
        if (str[i] != str[len - 1 - i])
            return 0;
    return 1;
}
