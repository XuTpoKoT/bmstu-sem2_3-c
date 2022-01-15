#include "textfile.h"

#include <stdlib.h>

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    double min, max;
    double avg;
    
    if (argc != 2)
        return NO_FILE;
    
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
        return NO_FILE;
    
    if (find_extrems(f, &max, &min))
        return NOT_ENOUCH_NUMBERS;
    
    fseek(f, 0, SEEK_SET);
    int rc = avg_between(f, min, max, &avg);
    fclose(f);
    
    if (rc)
        return NOT_ENOUCH_NUMBERS;
    
    printf("%.6lf", avg);
    
    return EXIT_SUCCESS;
}
