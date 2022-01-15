#include <ctype.h>
#include <string.h>

#include "date.h"

#define COUNT_MONTHS 12
#define COUNT_MONTHS_30 4

void to_lower(char str[])
{
    for (size_t i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

int is_leap(int year)
{
    if (year % 400 == 0)
        return 1;
    if (year % 100 == 0)
        return 0;
    return year % 4 == 0;
}

int day_wrong(char day_s[], char month[], int year, words_t months_30)
{
    for (size_t i = 0; day_s[i]; i++)
        if (!isdigit(day_s[i]))
            return 1;
        
    int day = atoi(day_s);

    if (day > 31 || day == 0)
        return 1;
    if (strcmp(month, "february") == 0)
        if (day > 29 || (!is_leap(year) && day == 29))
            return 1;
    for (int i = 0; i < COUNT_MONTHS_30; i++)
        if (strcmp(month, (char *)months_30[i]) == 0 && day > 30)
            return 1;
    return 0;
}

int month_wrong(char month[], words_t months)
{
    size_t len = strlen(month);
    if (len < MIN_MONTH_LEN - 1 || len > MAX_MONTH_LEN - 1)
        return 1;
    to_lower(month);
    for (size_t i = 0; i < len; i++)
        if (!isalpha(month[i]))
            return 1;
    for (size_t i = 0; i < COUNT_MONTHS; i++)
        if (strcmp(month, (char *)months[i]) == 0)
            return 0;
    return 1;
}

int year_wrong(char year_s[], int *year)
{
    for (size_t i = 0; year_s[i]; i++)
        if (!isdigit(year_s[i]))
            return 1;

    return (*year = atoi(year_s)) > 9999;
}

int date_correct(char day[], char month[], char year_s[])
{
    words_t months = { "january", "february", "march",
        "april", "may", "june", "july", "august",
        "september", "october", "november", "december" };
    words_t months_30 = { "april", "june", "september", "november" };
    int year;
    if (month_wrong(month, months) || year_wrong(year_s, &year) || day_wrong(day, month, year, months_30))
        return 0;
    return 1;
}
