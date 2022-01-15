#include "textfile.h"

#include <stdlib.h>
#include <math.h>

#define EPS 1e-8

int find_extrems(FILE *f, double *max, double *min)
{
    double num;
    
    if (fscanf(f, "%lf", &num) == 1)
    {
        *max = num;
        *min = num;
        while (fscanf(f, "%lf", &num) == 1)
        {
            if (num > *max)
                *max = num;
            if (num < *min)
                *min = num;
        }

        return EXIT_SUCCESS;
    }

    return NOT_ENOUCH_NUMBERS;
}

int avg_between(FILE *f, double num1, double num2, double *avg)
{
    double num;
    double sum = 0.0;
    int count_between = 0;
    int is_between = 0;
    
    while (fscanf(f, "%lf", &num) == 1)
    {
        if (is_between && (fabs(num - num1) < EPS || fabs(num - num2) < EPS))
            break;
        if (is_between)
        {
            sum += num;
            count_between++;
        }
        if (fabs(num - num1) < EPS || fabs(num - num2) < EPS)
            is_between = 1;
    }
    
    if (count_between == 0)
        return NOT_ENOUCH_NUMBERS;
    
    *avg = sum / count_between;

    return EXIT_SUCCESS;
}
