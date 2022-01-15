#ifndef _TEXTFILE_H_
#define _TEXTFILE_H_

#include <stdio.h>

#define NO_FILE 1
#define NOT_ENOUCH_NUMBERS 2

int find_extrems(FILE *f, double *max, double *min);
int avg_between(FILE *f, double num1, double num2, double *avg);

#endif