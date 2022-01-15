#ifndef MYSTRING_H
#define MYSTRING_H

#include <stdio.h>
#include <stdlib.h>

#define MYSTRING_LEN 128

int fscan_str(char str[], size_t n, FILE *f);
size_t ll2str(char *str, long long num, unsigned base);
size_t ull2str(char *str, unsigned long long num, unsigned base);

#endif