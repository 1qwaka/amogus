#include <stdio.h>
#include <math.h>

double triangle_perimeter(double ax, double ay, double bx, double by, double cx, double cy);

double length(double ax, double ay, double bx, double by);

int main(void)
{
    double ax, ay, bx, by, cx, cy;
    double p;
    scanf("%lf%lf%lf%lf%lf%lf", &ax, &ay, &bx, &by, &cx, &cy);

    p = triangle_perimeter(ax, ay, bx, by, cx, cy);

    printf("%.6lf", p);
    return 0;
}

double triangle_perimeter(double ax, double ay, double bx, double by, double cx, double cy)
{
    return length(ax, ay, bx, by) +
        length(ax, ay, cx, cy) +
        length(cx, cy, bx, by);
}

double length(double ax, double ay, double bx, double by)
{
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}
