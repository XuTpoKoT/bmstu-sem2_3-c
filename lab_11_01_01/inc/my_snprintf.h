#ifndef MY_SNPRINTF_H
#define MY_SNPRINTF_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int my_snprintf(char *restrict buf, size_t num, const char *restrict format, ...);

#endif