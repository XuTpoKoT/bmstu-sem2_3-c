#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PREСISION 1e-8

double func(double x, double eps)
{
    double s = 0.0;
    double cur = x / 2.0;
    int i = 0;
    while (fabs(cur) >= eps)
    {
        s += cur;
        i++;
        cur *= -x * x * x * (i + 1) / (i * (i + 2));
    }   
    return s;
}   

int main(void)
{
    setbuf(stdout, NULL);
    double x;
    double eps;
    
    printf("Input x: ");
    if (scanf("%lf", &x) != 1 || fabs(x) < PREСISION)
    {   
        printf("Wrong input!");
        return EXIT_FAILURE;
    }
    printf("Input eps: ");
    if (scanf("%lf", &eps) != 1 || eps <= 0)
    {   
        printf("Wrong input!");
        return EXIT_FAILURE;
    }
    
    double f = -exp(-x * x * x) * (1.0 + x) * (1.0 - x + x * x) / pow(x, 5.0);
    double s = func(x, eps);
    
    printf("f = %e\n", f);
    printf("s = %g", s);
    
    return EXIT_SUCCESS;
}