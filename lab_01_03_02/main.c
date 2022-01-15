#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    setbuf(stdout, NULL);

    double r1, r2, r3;
    printf("Input r_first, r_second and r_third: \n");
    scanf("%lf%lf%lf", &r1, &r2, &r3);

    double r;
    r = 1.0 / (1.0 / r1 + 1.0 / r2 + 1.0 / r3);

    printf("R = %.6lf", r);

    return EXIT_SUCCESS;
}
