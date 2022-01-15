#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int fib(int n)
{
    if (n == 0)
        return 0;

    int a = 0, b = 1, tmp;
    for (int i = 1; i < n; i++)
    {
        if (b > INT_MAX - a)
            return -1;
        tmp = a + b;
        a = b;
        b = tmp;
    }
    return b;
}

int main(void)
{
    setbuf(stdout, NULL);

    int n;
    printf("Input n: \n");
    if (scanf("%d", &n) != 1 || n < 0)
    {
        printf("Wrong input.\n");
        return EXIT_FAILURE;
    }

    int value = fib(n);

    if (value == -1)
    {
        printf("Overflow.\n");
        return EXIT_FAILURE;
    }
    printf("Answer - %d\n", value);

    return EXIT_SUCCESS;
}