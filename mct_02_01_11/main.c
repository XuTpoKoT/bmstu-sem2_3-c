#include <stdlib.h>

#include "str.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    str_t str1, str2;
    
    if (argc != 3)
        return EXIT_FAILURE;
    
    FILE *f = fopen(argv[1], "r");
    
    if (f == NULL)
        return EXIT_FAILURE;
    
    while (!input_str(f, str1))
    {
        size_t len_dst = del_simbols(str1, str2, argv[2]);
        if (len_dst != 0 && is_polindrome(str2))
            printf("%s\n", str1);
    }
    
    if (!feof(f))
    {
        fclose(f);
        return EXIT_FAILURE;
    }
    
    fclose(f);
        
    return EXIT_SUCCESS;
}
