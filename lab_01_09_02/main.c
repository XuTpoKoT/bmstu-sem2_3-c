#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    setbuf(stdout, NULL);

    double x = 0;
    double g = 0;
    int n = 0;
    int rc = 0;

    printf("Input values: \n");
    while ((rc = scanf("%lf", &x)) == 1 && x > 0)
    {
        n++;
        g += sqrt(n + x);
    }

    if (rc != 1)
    {
        printf("Wrong input");
        return EXIT_FAILURE;
    }

    if (n == 0)
    {
        printf("The sequence is empty");
        return EXIT_FAILURE;
    }

    g /= n;

    printf("g = %.6lf", g);

    return EXIT_SUCCESS;
}
