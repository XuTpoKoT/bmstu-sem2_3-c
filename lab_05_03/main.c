/*
  Выбранный целочисленный тип - int
  Алгоритм сортировки - пузырёк с флагом
  Направление упорядочивания - по возрастанию
*/

#include "binfile.h"

#include <string.h>

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    FILE *f;
    
    if (argc < 3 || argc > 4)
        return WRONG_ARGS;
    
    if (argc == 4 && !strcmp(argv[1], "c"))
    {
        int number = atoi(argv[2]);
        if (number <= 0)
            return WRONG_NUMBER;
        f = fopen(argv[3], "wb");
        if (fill_with_int(f, number))
        {
            fclose(f);
            return FILL_ERROR;
        }
        fclose(f);
    }
    else if (argc == 3 && !strcmp(argv[1], "p"))
    {
        f = fopen(argv[2], "rb");
        if (f == NULL)
            return NO_FILE;
        if (print(f))
        {
            fclose(f);
            return PRINT_ERROR;
        }
        fclose(f);
    }
    else if (argc == 3 && !strcmp(argv[1], "s"))
    {
        f = fopen(argv[2], "rb+");
        if (f == NULL)
            return NO_FILE;
        if (bubble_sort(f))
        {
            fclose(f);
            return SORT_ERROR;
        }
        fclose(f);
    }
    else if (argc == 4 && strcmp(argv[1], "t_to_b") == 0)
    {
        FILE *fsrc = fopen(argv[2], "r");
        if (fsrc == NULL)
            return NO_FILE;
        FILE *fdst = fopen(argv[3], "wb");
        if (fdst == NULL)
        {
            fclose(fsrc);
            return NO_FILE;
        }
        if (txt_to_bin(fsrc, fdst))
        {
            fclose(fsrc);
            fclose(fdst);
            return TXT_TO_BIN_ERROR;
        }
        fclose(fsrc);
        fclose(fdst);
    }
    else if (argc == 4 && strcmp(argv[1], "b_to_t") == 0)
    {
        FILE *fsrc = fopen(argv[2], "rb");
        if (fsrc == NULL)
            return NO_FILE;
        FILE *fdst = fopen(argv[3], "w");
        if (fdst == NULL)
        {
            fclose(fsrc);
            return NO_FILE;
        }
        if (bin_to_txt(fsrc, fdst))
        {
            fclose(fsrc);
            fclose(fdst);
            return BIN_TO_TXT_ERROR;
        }
        fclose(fsrc);
        fclose(fdst);
    }
    else
        return WRONG_ARGS;
        
    return EXIT_SUCCESS;
}
