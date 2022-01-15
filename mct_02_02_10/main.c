#include "students.h"

#include <stdlib.h>

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    const char beg[] = "Ivanov";
    const char end[] = "Petrov";
    
    if (argc != 2)
        return EXIT_FAILURE;
    
    FILE *f = fopen(argv[1], "rb+");
    
    if (f == NULL)
        return EXIT_FAILURE;
    
    if (del_students_between(f, beg, end))
    {
        fclose(f);
        return EXIT_FAILURE;
    }

    fclose(f);  
        
    return EXIT_SUCCESS;
}
