#ifndef _STR_H_
#define _STR_H_

#include <stdio.h>

#define MAX_STR_LEN 65

typedef char str_t[MAX_STR_LEN];

int input(FILE *f, str_t str);
int del_simbols(char src[], char dst[], char simbols[]);
int is_polindrome(char str[]);

#endif
