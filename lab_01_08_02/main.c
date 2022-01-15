#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>

#define DIGITS (CHAR_BIT * sizeof(uint32_t))

uint32_t bin_shift(uint32_t a, int n)
{
    return (a << n) | (a >> (DIGITS - n));
}

void print_bin(uint32_t a)
{
    uint32_t mask = 0x80000000;
    printf("Result: ");
    while (mask > 0)
    {
        printf("%d", (a & mask) != 0);
        mask >>= 1;
    }
    printf("\n");
}

int main(void)
{
    setbuf(stdout, NULL);
    uint32_t a;
    int n;

    printf("Input a: \n");
    if (scanf("%" SCNu32 "", &a) != 1)
    {
        printf("Error: wrong input.");
        return EXIT_FAILURE;
    }
    printf("Input n: \n");
    if (scanf("%d", &n) != 1 || n < 0)
    {
        printf("Error: wrong input.");
        return EXIT_FAILURE;
    }

    n %= DIGITS;
    a = bin_shift(a, n);

    print_bin(a);

    return EXIT_SUCCESS;
}