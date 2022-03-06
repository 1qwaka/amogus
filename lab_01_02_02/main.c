#include <stdio.h>
#include <math.h>

double triangle_perimeter(double ax, double ay, double bx, double by, double cx, double cy);

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
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by)) +
        sqrt((ax - cx) * (ax - cx) + (ay - cy) * (ay - cy)) +
        sqrt((cx - bx) * (cx - bx) + (cy - by) * (cy - by));
}
