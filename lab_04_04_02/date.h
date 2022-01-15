#ifndef _DATE_H_
#define _DATE_H_

#include "short_string.h"

#define MAX_MONTH_LEN 10
#define MIN_MONTH_LEN 4

void to_lower(char str[]);
int is_leap(int year);
int day_wrong(char day_s[], char month[], int year, words_t months_30);
int month_wrong(char month[], words_t months);
int year_wrong(char year_s[], int *year);
int date_correct(char day[], char month[], char year_s[]);
    
#endif
