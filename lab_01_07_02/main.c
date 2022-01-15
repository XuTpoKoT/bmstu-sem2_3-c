#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAXITER 1000

double func(double x, double eps)
{
    double s = x;
    double current = x;
    int i = 2;
    while (current >= eps && i < MAXITER)
    {
        i += 2;
        current *= x * x * (i - 3) * (i - 3) / ((i - 2) * (i - 1));
        s += current;
    }
    return s;
}

int main(void)
{
    setbuf(stdout, NULL);

    double x;
    printf("Input x: \n");
    if (scanf("%lf", &x) != 1 || fabs(x) > 1)
    {
        printf("Wrong input");
        return EXIT_FAILURE;
    }
    double eps;
    printf("Input eps: \n");
    if (scanf("%lf", &eps) != 1 || eps <= 0 || eps > 1)
    {
        printf("Wrong input");
        return EXIT_FAILURE;
    }

    double f = asin(x);
    double s = func(x, eps);

    double abs_mistake = fabs(f - s);
    double compare_mistake = abs_mistake / fabs(f);

    printf("f - %.6lf\n", f);
    printf("s - %.6lf\n", s);
    printf("Absolute mistake - %.6lf\n", abs_mistake);
    printf("Comparetive mistake - %.6lf\n", compare_mistake);

    return EXIT_SUCCESS;
}