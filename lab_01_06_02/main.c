#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const double eps = 1e-8;

double square(double a, double b, double c)
{
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

int main(void)
{
    setbuf(stdout, NULL);

    double ax, ay;
    double bx, by;
    double cx, cy;

    printf("Input ax and ay: \n");
    if (scanf("%lf%lf", &ax, &ay) != 2)
    {
        printf("Wrong input");
        return EXIT_FAILURE;
    }
    printf("Input bx and by: \n");
    if (scanf("%lf%lf", &bx, &by) != 2 || ((fabs(ax - bx) < eps) &&
        (fabs(ay - by) < eps)))
    {
        printf("Wrong input");
        return EXIT_FAILURE;
    }
    printf("Input cx and cy: \n");
    if (scanf("%lf%lf", &cx, &cy) != 2 || ((fabs(ax - cx) < eps) &&
        (fabs(ay - cy) < eps)) || ((fabs(bx - cx) < eps) &&
        (fabs(by - cy) < eps)))
    {
        printf("Wrong input");
        return EXIT_FAILURE;
    }

    double a, b, c; // стороны треугольника
    a = sqrt((bx - cx) * (bx - cx) + (by - cy) * (by - cy));
    b = sqrt((ax - cx) * (ax - cx) + (ay - cy) * (ay - cy));
    c = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));

    if (fabs(a + b - c) <= eps || fabs(a + c - b) <= eps ||
        fabs(b + c - a) <= eps)
    {
        printf("Triangle does not exist.\n");
        return EXIT_FAILURE;
    }

    double mx, my;
    printf("Input coordinats of point: \n");
    if (scanf("%lf%lf", &mx, &my) != 2)
    {
        printf("Wrong input");
        return EXIT_FAILURE;
    }

    double ma = sqrt((mx - ax) * (mx - ax) + (my - ay) * (my - ay));
    double mb = sqrt((mx - bx) * (mx - bx) + (my - by) * (my - by));
    double mc = sqrt((mx - cx) * (mx - cx) + (my - cy) * (my - cy));

    if (fabs(square(c, ma, mb)) < eps || fabs(square(b, ma, mc)) < eps
        || fabs(square(a, mb, mc)) < eps)
        printf("1");
    else if (fabs(square(c, ma, mb) + square(b, ma, mc) + square(a, mb, mc) -
        square(a, b, c)) < eps)
        printf("0");
    else
        printf("2");

    return EXIT_SUCCESS;
}