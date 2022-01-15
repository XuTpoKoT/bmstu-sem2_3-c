#include "products.h"

#include <stdlib.h>

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    
    if (argc != 2)
        return EXIT_FAILURE;
    
    FILE *f = fopen(argv[1], "rb+");
    
    if (f == NULL)
    {
        return EXIT_FAILURE;
    }
    
    double avg;
    if (count_avg_mass(f, &avg))
    {
        fclose(f);
        return EXIT_FAILURE;
    }
    
    if (del_products_lower_val(f, avg))
    {
        fclose(f);
        return EXIT_FAILURE;
    }

    fclose(f);  
        
    return EXIT_SUCCESS;
}
