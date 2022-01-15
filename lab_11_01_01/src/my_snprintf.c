#include <stdio.h>

#include "my_snprintf.h"
#include "mystring.h"

int my_snprintf(char *restrict str, size_t n, const char *restrict format, ...)
{
    va_list args;
    va_start(args, format);
    char buf[MYSTRING_LEN];
    size_t buf_len = 0;

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
                case '%':
                    buf[buf_len++] = '%';
                    break;
                case 'c':
                    buf[buf_len++] = va_arg(args, int);
                    break;
                case 's':
                    {
                        char *s = va_arg(args, char*);
                        while (*s)
                            buf[buf_len++] = *s++;
                        break;
                    }                   
                case 'd':
                case 'i':
                    {
                        char s[MYSTRING_LEN];
                        size_t simbols = ll2str(s, va_arg(args, int), 10);
                        for (size_t i = 0; i < simbols; i++)
                            buf[buf_len++] = s[i];
                        break;
                    }
                case 'o':
                    {
                        char s[MYSTRING_LEN];
                        unsigned arg = va_arg(args, unsigned int);
                        size_t simbols = ull2str(s, arg, 8);
                        for (size_t i = 0; i < simbols; i++)
                            buf[buf_len++] = s[i];
                        break;
                    }
                case 'x':
                    {
                        char s[MYSTRING_LEN];
                        unsigned arg = va_arg(args, unsigned int);
                        size_t simbols = ull2str(s, arg, 16);
                        for (size_t i = 0; i < simbols; i++)
                            buf[buf_len++] = s[i];
                        break;
                    }
                case 'h':
                    {
                        format++;
                        switch (*format)
                        {
                            case 'd':
                            case 'i':
                                {
                                    char s[MYSTRING_LEN];
                                    short arg = va_arg(args, int);
                                    size_t simbols = ll2str(s, arg, 10);
                                    for (size_t i = 0; i < simbols; i++)
                                        buf[buf_len++] = s[i];
                                    break;
                                }
                            case 'o':
                                {
                                    char s[MYSTRING_LEN];
                                    unsigned short arg = va_arg(args, unsigned int);
                                    size_t simbols = ull2str(s, arg, 8);
                                    for (size_t i = 0; i < simbols; i++)
                                        buf[buf_len++] = s[i];
                                    break;
                                }
                            case 'x':
                                {
                                    char s[MYSTRING_LEN];
                                    unsigned short arg = va_arg(args, unsigned int);
                                    size_t simbols = ull2str(s, arg, 16);
                                    for (size_t i = 0; i < simbols; i++)
                                        buf[buf_len++] = s[i];
                                    break;
                                }
                            default:
                                return buf_len;
                        }
                        break;
                    }
                case 'l':
                    {
                        format++;
                        switch (*format)
                        {
                            case 'd':
                            case 'i':
                                {
                                    char s[MYSTRING_LEN];
                                    long arg = va_arg(args, long);
                                    size_t simbols = ll2str(s, arg, 10);
                                    for (size_t i = 0; i < simbols; i++)
                                        buf[buf_len++] = s[i];
                                    break;
                                }
                            case 'o':
                                {
                                    char s[MYSTRING_LEN];
                                    unsigned long arg = va_arg(args, unsigned long);
                                    size_t simbols = ull2str(s, arg, 8);
                                    for (size_t i = 0; i < simbols; i++)
                                        buf[buf_len++] = s[i];
                                    break;
                                }
                            case 'x':
                                {
                                    char s[MYSTRING_LEN];
                                    unsigned long arg = va_arg(args, unsigned long);
                                    size_t simbols = ull2str(s, arg, 16);
                                    for (size_t i = 0; i < simbols; i++)
                                        buf[buf_len++] = s[i];
                                    break;
                                }
                            default:
                                return buf_len;
                        }
                        break;
                    }
                default:
                    return buf_len;
            }
            format++;
        }
        else
            buf[buf_len++] = *format++; 
    }

    buf[buf_len] = '\0';
    va_end(args);

    if (!str)
        return buf_len;

    
    if (n != 0)
    {
        size_t i;
        for (i = 0; i < buf_len && i < n - 1; i++)
            str[i] = buf[i];
        str[i] = '\0';
    }

    return buf_len;
}



