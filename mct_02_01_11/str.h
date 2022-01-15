#ifndef STR_H
#define STR_H

#include <stdio.h>

#define MAX_STR_LEN 257

typedef char str_t[MAX_STR_LEN];

int input_str(FILE *f, str_t str);
int del_simbols(char src[], char dst[], char simbols[]);
int is_polindrome(char str[]);

#endif
