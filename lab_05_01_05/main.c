#include "sequence.h"

#include <stdlib.h>

int main(void)
{
    setbuf(stdout, NULL);
    int max_count_equal = 0;
    
    if (process(stdin, &max_count_equal))
        return NO_NUMBERS;
    
    printf("%d", max_count_equal);
    
    return EXIT_SUCCESS;
}
