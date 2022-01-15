#include "sequence.h"

#include <stdlib.h>

int process(FILE *f, int *max_count_equal)
{
    *max_count_equal = 1;
    int count_equal = 1;
    int num, num2;
    
    if (fscanf(f, "%d", &num) == 1)
    {
        while (fscanf(f, "%d", &num2) == 1)
        {
            if (num == num2)
                count_equal++;
            else
                count_equal = 1;
            if (*max_count_equal < count_equal)
                *max_count_equal = count_equal;
            num = num2;
        }

        return EXIT_SUCCESS;
    }

    return NO_NUMBERS;
}


