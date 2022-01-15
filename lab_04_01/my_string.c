#include "my_string.h"

char *my_strpbrk(const char *s1, const char *s2)
{
    for (size_t i = 0; s1[i] != '\0'; i++)
        for (size_t j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                return (char *)s1 + i;
    return NULL;
}

size_t my_strspn(const char *s1, const char *s2)
{
    int search;
    size_t i;
    for (i = 0; s1[i] != '\0'; i++)
    {
        search = 1;
        for (size_t j = 0; s2[j] != '\0' && search; j++)
            if (s1[i] == s2[j])
                search = 0;     
        if (search == 1)
            return i;
    }
    return i;
}

size_t my_strcspn(const char *s1, const char *s2)
{
    size_t i;
    for (i = 0; s1[i] != '\0'; i++)
        for (size_t j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                return i;       
    return i;
}

char *my_strchr(const char *s, int c)
{
    size_t i;
    for (i = 0; s[i] != '\0'; i++)
        if (s[i] == c)
            return (char *)(s + i);
    if (c == '\0')
        return (char *)(s + i);
    return NULL;
}

char *my_strrchr(const char *s, int c)
{
    size_t i;
    char *last_c = NULL;
    for (i = 0; s[i] != '\0'; i++)
        if (s[i] == c)
            last_c = (char *)(s + i);
    if (c == '\0')
        return (char *)(s + i);
    return last_c;
}
