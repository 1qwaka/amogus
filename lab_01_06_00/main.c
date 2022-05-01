#include <stdio.h>
#include <math.h>

#define ERR_IN 1
#define ERR_DATA 2
#define FLOAT_ERR 1e-6

double cross_product(double x1, double y1, double x2, double y2, double x3, double y3);

short triangle_type(double ax, double ay, double bx, double by, double cx, double cy);

double length(double ax, double ay, double bx, double by);

int main(void)
{
    double ax = 0, ay = 0, bx = 0, by = 0, cx = 0, cy = 0;
    short rc = 0;
    int exit_code = 0;

    rc = scanf("%lf%lf%lf%lf%lf%lf", &ax, &ay, &bx, &by, &cx, &cy);
    if (rc != 6)
    {
        exit_code = ERR_IN;
    }
    else if (fabs(cross_product(ax, ay, bx, by, cx, cy)) < FLOAT_ERR)
    {
        exit_code = ERR_DATA;
    }
    else
    {
        short result = triangle_type(ax, ay, bx, by, cx, cy);
        printf("%d", result);
    }

    return exit_code;
}

double cross_product(double x1, double y1, double x2, double y2, double x3, double y3)
{
    return (x3 - x1) * (y2 - y1) - (y3 - y1) * (x2 - x1);
}

short triangle_type(double ax, double ay, double bx, double by, double cx, double cy)
{
    double tmp = 0;
    double side_a = 0, side_b = 0, side_c = 0;
    short result = 0;

    side_a = length(bx, by, cx, cy);
    side_b = length(ax, ay, cx, cy);
    side_c = length(ax, ay, bx, by);

    if (side_c > side_b)
    {
        tmp = side_b;
        side_b = side_c;
        side_c = tmp;
    }
    if (side_b > side_a)
    {
        tmp = side_a;
        side_a = side_b;
        side_b = tmp;
    }

    tmp = side_b * side_b + side_c * side_c;
    // тупоугольный по умолчанию
    result = 2;

    if (fabs(tmp - side_a * side_a) < FLOAT_ERR)
        result = 1;
    else if (tmp > side_a * side_a)
        result = 0;

    return result;
}

double length(double ax, double ay, double bx, double by)
{
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}