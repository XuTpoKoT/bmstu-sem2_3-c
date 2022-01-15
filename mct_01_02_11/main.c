#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>

#define NMAX 1024

int input(int *restrict arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
        if (scanf("%d", &arr[i]) != 1)
            return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}

void output(const int *restrict arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%d ", arr[i]);
}

int is_square(int x)
{
    int i = 1;
    while (x > 0)
    {
        x -= i;
        i += 2;
    }
    
    return x == 0;
}

void move_square(int *restrict arr, size_t n, int *restrict arr_sq, size_t *ptr_sq,
    int *restrict arr_not_sq, size_t *ptr_not_sq)
{
    for (size_t i = 0; i < n; i++)
        if (is_square(arr[i]))
        {
            (*ptr_sq)++;
            arr_sq[(*ptr_sq) - 1] = arr[i];
        }
        else
        {
            (*ptr_not_sq)++;
            arr_not_sq[(*ptr_not_sq) - 1] = arr[i];
        }
}

int main(void)
{
    setbuf(stdout, NULL);
    size_t n;
    size_t len_sq = 0;
    size_t len_not_sq = 0;
    int arr[NMAX];
    int arr_sq[NMAX];
    int arr_not_sq[NMAX];
    size_t *ptr_sq = &len_sq;
    size_t *ptr_not_sq = &len_not_sq;
    
    printf("Input n: ");
    if (scanf("%zu", &n) != 1 || n == 0 || n > NMAX)
    {   
        printf("Wrong input!");
        return EXIT_FAILURE;
    }
    int rc = input(arr, n);
    if (rc == EXIT_FAILURE)
    {   
        printf("Wrong input!");
        return rc;
    }
    
    move_square(arr, n, arr_sq, ptr_sq, arr_not_sq, ptr_not_sq);
    
    printf("A: \n");
    output(arr_sq, len_sq);
    printf("\n");
    printf("B: \n");
    output(arr_not_sq, len_not_sq);
    
    return EXIT_SUCCESS;
}