#include "binfile.h"

#include <time.h>

int file_size(FILE *f, size_t *count_numbers)
{
    long pos = ftell(f);
    if (pos < 0)
        return EXIT_FAILURE;
    if (fseek(f, 0L, SEEK_END))
        return EXIT_FAILURE;
    long size = ftell(f);
    if (size < 0)
        return EXIT_FAILURE;

    *count_numbers = size / sizeof(int);
    if (*count_numbers * sizeof(int) != (size_t)size)
        return EXIT_FAILURE;

    return fseek(f, pos, SEEK_SET);
}

int get_number_by_pos(FILE *f, long pos, int *num)
{
    long cur_pos = ftell(f);
    if (cur_pos < 0)
        return EXIT_FAILURE;
    if (fseek(f, pos * sizeof(int), SEEK_SET))
        return EXIT_FAILURE;
    if (fread(num, sizeof(int), 1, f) != 1)
        return EXIT_FAILURE;
    return fseek(f, cur_pos, SEEK_SET);
}

int put_number_by_pos(FILE *f, long pos, int *num)
{
    long cur_pos = ftell(f);
    if (cur_pos < 0)
        return EXIT_FAILURE;
    if (fseek(f, pos * sizeof(int), SEEK_SET))
        return EXIT_FAILURE;
    if (fwrite(num, sizeof(int), 1, f) != 1)
        return EXIT_FAILURE;
    return fseek(f, cur_pos, SEEK_SET);
}

int rand_int(const int min, const int max)
{
    return rand() % (max - min + 1) + min;
}

int fill_with_int(FILE *f, size_t numbers)
{
    srand(time(NULL));
    for (size_t i = 0; i < numbers; i++)
    {
        int x = rand_int(-100, 100);
        if (put_number_by_pos(f, i, &x))
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int print(FILE *f)
{
    size_t count_numbers;
    int num;
    if (file_size(f, &count_numbers))
        return EXIT_FAILURE;
    
    for (size_t i = 0; i < count_numbers; i++)
    {
        if (get_number_by_pos(f, i, &num))
            return EXIT_FAILURE;
        printf("%d ", num);
    }
    
    return EXIT_SUCCESS;
}

int bubble_sort(FILE *f)
{
    size_t count_numbers;
    int num1, num2;
    int end = 0;
    if (file_size(f, &count_numbers))
        return EXIT_FAILURE;
    
    for (size_t i = 0; i < count_numbers - 1 && !end; i++)
    {
        end = 1;
        for (size_t j = 0; j < count_numbers - 1 - i; j++)
        {
            if (get_number_by_pos(f, j, &num1) || get_number_by_pos(f, j + 1, &num2))
                return EXIT_FAILURE;
            if (num1 > num2)
            {
                int tmp = num1;
                if (put_number_by_pos(f, j, &num2) || put_number_by_pos(f, j + 1, &tmp))
                    return EXIT_FAILURE;
                end = 0;
            }
        }       
    }
    
    return EXIT_SUCCESS;
}

int txt_to_bin(FILE *fsrc, FILE *fdst)
{
    int num;
    for (size_t i = 0; fscanf(fsrc, "%d", &num) == 1; i++)
        if (put_number_by_pos(fdst, i, &num))
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int bin_to_txt(FILE *fsrc, FILE *fdst)
{
    int num;
    size_t count_numbers;
    if (file_size(fsrc, &count_numbers))
        return EXIT_FAILURE;

    for (size_t i = 0; i < count_numbers; i++)
    {
        if (get_number_by_pos(fsrc, i, &num))
            return EXIT_FAILURE;
        fprintf(fdst, "%d ", num);
    }

    return EXIT_SUCCESS;
}
