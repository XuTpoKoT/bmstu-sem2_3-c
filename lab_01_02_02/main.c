#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    double ax, ay;
    double bx, by;
    double cx, cy;

    printf("Input ax and ay: \n");
    scanf("%lf%lf", &ax, &ay);
    printf("Input bx and by: \n");
    scanf("%lf%lf", &bx, &by);
    printf("Input cx and cy: \n");
    scanf("%lf%lf", &cx, &cy);

    double a, b, c;
    a = sqrt((bx - cx) * (bx - cx) + (by - cy) * (by - cy));
    b = sqrt((ax - cx) * (ax - cx) + (ay - cy) * (ay - cy));
    c = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));

    printf("Perimeter is %.6lf", a + b + c);

    return EXIT_SUCCESS;
}
